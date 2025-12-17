#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include "addvehicledialog.h"
#include "addemployeedialog.h"
#include "addorderdialog.h"

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

    ui->ordersTable->setModel(ordersModel);
    ui->ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRole(const QString& role)
{
    if (role == "MANAGER") {
        setWindowTitle("Panel Kierownika");

        ui->tabWidget->setTabVisible(0, true);  // Pracownicy
        ui->tabWidget->setTabVisible(1, true);  // Samochody
        ui->tabWidget->setTabVisible(2, true);  // Zlecenia
        ui->tabWidget->setTabVisible(3, false); // Moje zlecenie
    }
    else {
        setWindowTitle("Panel Pracownika");

        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1, false);
        ui->tabWidget->setTabVisible(2, false);
        ui->tabWidget->setTabVisible(3, true);
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
    }
}
