#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addvehicledialog.h"
#include "addemployeedialog.h"
#include "addorderdialog.h"
#include "userservice.h"
#include "vehicleservice.h"
#include "orderservice.h"
#include <QDialog>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vehiclesModel = new QSqlTableModel(this);
    vehiclesModel->setTable("Vehicles");
    vehiclesModel->select();
    ui->vehiclesTable->setModel(vehiclesModel);
    ui->vehiclesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    employeesModel = new QSqlTableModel(this);
    employeesModel->setTable("Users");
    employeesModel->setFilter("Role = 'EMPLOYEE'");
    employeesModel->select();
    ui->employeesTable->setModel(employeesModel);
    ui->employeesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ordersModel = new QSqlTableModel(this);
    ordersModel->setTable("Orders");
    ordersModel->select();

    myJobsModel = new QSqlTableModel(this);
    myJobsModel->setTable("Orders");
    ui->myJobsTable->setModel(myJobsModel);
    ui->myJobsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    activeOrdersModel = new QSqlQueryModel(this);
    ui->activeOrdersTable->setModel(activeOrdersModel);

    completedOrdersModel = new QSqlQueryModel(this);
    ui->completedOrdersTable->setModel(completedOrdersModel);

    selectedOrderId = -1;
    updateOrderButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRole(const QString& role, int userId)
{
    currentUserRole = role;
    currentUserId = userId;

    if (role == "MANAGER") {
        setWindowTitle("Admin Panel");
        ui->tabWidget->setTabVisible(0, true);
        ui->tabWidget->setTabVisible(1, true);
        ui->tabWidget->setTabVisible(2, true);
        ui->tabWidget->setTabVisible(3, false);
        loadActiveOrders();
        loadCompletedOrders();
    } else {
        setWindowTitle("Employee Panel  - ID: " + QString::number(userId));
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1, false);
        ui->tabWidget->setTabVisible(2, false);
        ui->tabWidget->setTabVisible(3, true);
        loadMyJobs();
    }
}

void MainWindow::on_addEmployeeButton_clicked()
{
    AddEmployeeDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        employeesModel->select();
    }
}

void MainWindow::on_addvehicleButton_clicked()
{
    AddvehicleDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        vehiclesModel->select();
    }
}

void MainWindow::on_addOrderButton_clicked()
{
    AddOrderDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        ordersModel->select();
        if (currentUserRole == "MANAGER") {
            loadActiveOrders();
            loadCompletedOrders();
        }
    }
}

void MainWindow::on_myJobsTable_clicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        selectedOrderId = -1;
        updateOrderButtons();
        return;
    }

    QModelIndex idIndex = myJobsModel->index(index.row(), 0);
    selectedOrderId = myJobsModel->data(idIndex).toInt();
    updateOrderButtons();
}

void MainWindow::on_acceptOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    OrderService orderService;
    if (!orderService.acceptOrder(selectedOrderId)) {
        QMessageBox::warning(this, "Error", "The order cannot be accepted");
        return;
    }

    myJobsModel->select();
    updateOrderButtons();
    QMessageBox::information(this, "Success", "The order has been accepted!\n\nYou can now start working.");
}

void MainWindow::on_rejectOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation", "Are you sure you want to reject this order?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::No) return;

    OrderService orderService;
    if (!orderService.rejectOrder(selectedOrderId)) {
        QMessageBox::warning(this, "Error", "The order cannot be rejected");
        return;
    }

    myJobsModel->select();
    selectedOrderId = -1;
    updateOrderButtons();
    QMessageBox::information(this, "Success", "The order has been rejected!");
}
void MainWindow::on_startOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    orderStartTime = QDateTime::currentDateTime();

    OrderService orderService;
    if (!orderService.startOrder(selectedOrderId, orderStartTime)) {
        QMessageBox::warning(this, "Error", "Unable to start order");
        return;
    }

    myJobsModel->select();
    updateOrderButtons();

    QMessageBox::information(
        this, "Job started",
        QString("Job #%1 started o %2\n\nTime has started!")
            .arg(selectedOrderId)
            .arg(orderStartTime.toString("hh:mm:ss"))
        );
}

void MainWindow::on_completeOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    OrderService orderService;
    Order* order = orderService.getOrderById(selectedOrderId);

    if (!order) {
        QMessageBox::warning(this, "Error", "Unable to read order data");
        return;
    }

    QDateTime startTime = order->getActualStartTime();
    QDateTime endTime = QDateTime::currentDateTime();
    qint64 durationSeconds = startTime.secsTo(endTime);

    bool ok;
    QString employeeNote = QInputDialog::getMultiLineText(
        this, "Completion of the job",
        QString("The job took: %1 godz %2 min %3 sek\n\nAdd note:")
            .arg(durationSeconds / 3600)
            .arg((durationSeconds % 3600) / 60)
            .arg(durationSeconds % 60),
        "", &ok
        );

    if (!ok) {
        delete order;
        return;
    }

    if (!orderService.completeOrder(selectedOrderId, endTime, durationSeconds, employeeNote)) {
        QMessageBox::warning(this, "Error", "Unable to complete the order");
        delete order;
        return;
    }

    delete order;
    myJobsModel->select();
    selectedOrderId = -1;
    updateOrderButtons();

    QMessageBox::information(
        this, "Success",
        QString("Job ended!\nWorktime: %1h %2m %3s")
            .arg(durationSeconds / 3600)
            .arg((durationSeconds % 3600) / 60)
            .arg(durationSeconds % 60)
        );
}

void MainWindow::loadMyJobs()
{
    myJobsModel->setFilter(QString("EmployeeId = %1").arg(currentUserId));
    myJobsModel->select();
    myJobsModel->setHeaderData(0, Qt::Horizontal, "ID");
    myJobsModel->setHeaderData(1, Qt::Horizontal, "Start Date");
    myJobsModel->setHeaderData(2, Qt::Horizontal, "Manager Note");
    myJobsModel->setHeaderData(3, Qt::Horizontal, "Status");
    myJobsModel->setHeaderData(4, Qt::Horizontal, "Vehicle ID");
    myJobsModel->setHeaderData(5, Qt::Horizontal, "Employee ID");
    ui->myJobsTable->reset();
}

void MainWindow::updateOrderButtons()
{
    if (selectedOrderId == -1) {
        ui->acceptOrderButton->setEnabled(false);
        ui->rejectOrderButton->setEnabled(false);
        ui->startOrderButton->setEnabled(false);
        ui->completeOrderButton->setEnabled(false);
        ui->orderStatusLabel->setText("Select job from the list");
        return;
    }

    OrderService orderService;
    Order* order = orderService.getOrderById(selectedOrderId);

    if (!order) {
        ui->orderStatusLabel->setText("Error reading job");
        return;
    }

    QString status = order->getStatus();
    ui->orderStatusLabel->setText(
        QString("Job #%1 | Status: %2\nDate: %3\n%4")
            .arg(selectedOrderId)
            .arg(getOrderStatusText(status))
            .arg(order->getStartDate())
            .arg(order->getNote().isEmpty() ? "" : "Notes: " + order->getNote())
        );

    ui->acceptOrderButton->setEnabled(order->isNew());
    ui->rejectOrderButton->setEnabled(order->isNew());
    ui->startOrderButton->setEnabled(order->isAccepted());
    ui->completeOrderButton->setEnabled(order->isInProgress());

    delete order;
}

QString MainWindow::getOrderStatusText(const QString& status)
{
    OrderService orderService;
    return orderService.getStatusText(status);
}

void MainWindow::on_refreshActiveButton_clicked()
{
    loadActiveOrders();
}

void MainWindow::on_refreshCompleteButton_clicked()
{
    loadCompletedOrders();
}
void MainWindow::loadActiveOrders()
{
    QString queryStr =
        "SELECT "
        "o.Id AS 'ID', "
        "o.StartDate AS 'Planned Date', "
        "o.Status AS 'Status', "
        "u.Login AS 'Employee', "
        "v.Brand || ' ' || v.Model AS 'Vehicle', "
        "v.Plate AS 'Registration', "
        "o.Note AS 'Manager Notes', "
        "o.ActualStartTime AS 'Start Time' "
        "FROM Orders o "
        "LEFT JOIN Users u ON o.EmployeeId = u.Id "
        "LEFT JOIN Vehicles v ON o.VehicleId = v.Id "
        "WHERE o.Status IN ('NEW', 'ACCEPTED', 'IN_PROGRESS') "
        "ORDER BY o.StartDate DESC";

    activeOrdersModel->setQuery(queryStr);

    if (activeOrdersModel->lastError().isValid()) {
        QMessageBox::warning(this, "Error",
                             "Unable to load active orders:\n" + activeOrdersModel->lastError().text());
    }
}

void MainWindow::loadCompletedOrders()
{
    QString queryStr =
        "SELECT "
        "o.Id AS 'ID', "
        "o.StartDate AS 'Planned Date', "
        "o.Status AS 'Status', "
        "u.Login AS 'Employee', "
        "v.Brand || ' ' || v.Model AS 'Vehicle', "
        "v.Plate AS 'Registration', "
        "o.ActualStartTime AS 'Start Time', "
        "o.EndTime AS 'Ended', "
        "o.Duration AS 'Time (sec)', "
        "o.EmployeeNote AS 'Employee Note', "
        "o.Note AS 'Manager Note' "
        "FROM Orders o "
        "LEFT JOIN Users u ON o.EmployeeId = u.Id "
        "LEFT JOIN Vehicles v ON o.VehicleId = v.Id "
        "WHERE o.Status IN ('COMPLETED', 'REJECTED') "
        "ORDER BY o.EndTime DESC";

    completedOrdersModel->setQuery(queryStr);

    if (completedOrdersModel->lastError().isValid()) {
        QMessageBox::warning(this, "Error",
                             "Unable to load completed orders:\n" + completedOrdersModel->lastError().text());
        return;
    }

    int count = completedOrdersModel->rowCount();
    ui->completeStatusLabel->setText(QString("Total completed orders: %1").arg(count));
}

QString MainWindow::formatDuration(int seconds)
{
    OrderService orderService;
    return orderService.formatDuration(seconds);
}

void MainWindow::on_deleteVehicleButton_clicked()
{
    QModelIndexList selection = ui->vehiclesTable->selectionModel()->selectedRows();

    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Chose vehicle to delete");
        return;
    }

    int row = selection.first().row();
    QModelIndex idIndex = vehiclesModel->index(row, 0);
    int vehicleId = vehiclesModel->data(idIndex).toInt();

    QModelIndex plateIndex = vehiclesModel->index(row, 3);
    QString vehiclePlate = vehiclesModel->data(plateIndex).toString();

    VehicleService vehicleService;
    OrderService orderService;

    int orderCount = vehicleService.getVehicleOrderCount(vehicleId);

    if (orderCount > 0) {
        QMessageBox::StandardButton reply = QMessageBox::warning(
            this, "Warning",
            QString("Deleting a vehicle will delete all of its orders.\n\n"
                    "Are you sure you want to continue?")
                .arg(vehiclePlate).arg(orderCount),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No
            );

        if (reply == QMessageBox::No) return;

        if (!orderService.deleteOrdersByVehicle(vehicleId)) {
            QMessageBox::critical(this, "Error", "Unable to delete vehicle orders");
            return;
        }
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        QString("Are you sure you want to delete this vehicle?").arg(vehiclePlate),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No
        );

    if (reply == QMessageBox::No) return;

    if (!vehicleService.deleteVehicle(vehicleId)) {
        QMessageBox::critical(this, "Error", "Unable to delete vehicle");
        return;
    }

    QMessageBox::information(this, "Success",
                             QString("Vehicle '%1' has been deleted").arg(vehiclePlate));

    vehiclesModel->select();
    loadActiveOrders();
    loadCompletedOrders();
}

void MainWindow::on_deleteEmployeeButton_clicked()
{
    QModelIndexList selection = ui->employeesTable->selectionModel()->selectedRows();

    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Select employee to delete");
        return;
    }

    int row = selection.first().row();
    QModelIndex idIndex = employeesModel->index(row, 0);
    int employeeId = employeesModel->data(idIndex).toInt();

    QModelIndex loginIndex = employeesModel->index(row, 1);
    QString employeeLogin = employeesModel->data(loginIndex).toString();

    UserService userService;
    OrderService orderService;

    int orderCount = userService.getEmployeeOrderCount(employeeId);

    if (orderCount > 0) {
        QMessageBox::StandardButton reply = QMessageBox::warning(
            this, "Warning",
            QString("Deleting an employee will delete all of their orders.\n\n"
                    "Are you sure you want to continue?")
                .arg(employeeLogin).arg(orderCount),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No
            );

        if (reply == QMessageBox::No) return;

        if (!orderService.deleteOrdersByEmployee(employeeId)) {
            QMessageBox::critical(this, "Error", "Unable to delete employee orders");
            return;
        }
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        QString("Are you sure to delete employee '%1'?").arg(employeeLogin),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No
        );

    if (reply == QMessageBox::No) return;

    if (!userService.deleteEmployee(employeeId)) {
        QMessageBox::critical(this, "Error", "Unable to remove employee");
        return;
    }

    QMessageBox::information(this, "Success",
                             QString("Employee '%1' has been deleted").arg(employeeLogin));

    employeesModel->select();
    loadActiveOrders();
    loadCompletedOrders();
}
