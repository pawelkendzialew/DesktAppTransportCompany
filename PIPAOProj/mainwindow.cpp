#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include "addvehicledialog.h"
#include "addemployeedialog.h"
#include "addorderdialog.h"
#include <QSqlQuery>
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

    ui->ordersTable->setModel(ordersModel);
    ui->ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    myJobsModel = new QSqlTableModel(this);
    myJobsModel->setTable("Orders");
    ui->myJobsTable->setModel(myJobsModel);
    ui->myJobsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
        setWindowTitle("Panel Kierownika");

        ui->tabWidget->setTabVisible(0, true);
        ui->tabWidget->setTabVisible(1, true);
        ui->tabWidget->setTabVisible(2, true);
        ui->tabWidget->setTabVisible(3, false);
    }
    else {
        setWindowTitle("Panel Pracownika - ID: " + QString::number(userId));

        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1, false);
        ui->tabWidget->setTabVisible(2, false);
        ui->tabWidget->setTabVisible(3, true);

        // ⭐ ZAŁADUJ ZLECENIA PRACOWNIKA
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
    }
}

void MainWindow::on_myJobsTable_clicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        selectedOrderId = -1;
        updateOrderButtons();
        return;
    }

    // Pobierz ID zlecenia z pierwszej kolumny wybranego wiersza
    QModelIndex idIndex = myJobsModel->index(index.row(), 0);
    selectedOrderId = myJobsModel->data(idIndex).toInt();

    updateOrderButtons();
}


void MainWindow::on_acceptOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    QSqlQuery query;
    query.prepare("UPDATE Orders SET Status = 'ACCEPTED' WHERE Id = :id");
    query.bindValue(":id", selectedOrderId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Błąd", "Nie można przyjąć zlecenia");
        return;
    }

    // ⭐ NAJPIERW odśwież model
    myJobsModel->select();

    // ⭐ NASTĘPNIE odśwież przyciski (to ponownie pobierze status z bazy)
    updateOrderButtons();

    // ⭐ Komunikat NA KOŃCU
    QMessageBox::information(this, "Sukces", "Zlecenie zostało przyjęte!\n\nMożesz teraz rozpocząć pracę.");
}


void MainWindow::on_rejectOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Potwierdzenie",
        "Czy na pewno chcesz odrzucić to zlecenie?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::No) return;

    QSqlQuery query;
    query.prepare("UPDATE Orders SET Status = 'REJECTED' WHERE Id = :id");
    query.bindValue(":id", selectedOrderId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Błąd", "Nie można odrzucić zlecenia");
        return;
    }

    // ⭐ Odśwież model
    myJobsModel->select();

    // ⭐ Wyczyść selekcję (zlecenie odrzucone nie wymaga dalszych akcji)
    selectedOrderId = -1;
    updateOrderButtons();

    QMessageBox::information(this, "Sukces", "Zlecenie zostało odrzucone");
}


void MainWindow::on_startOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    // Zapisz czas rozpoczęcia
    orderStartTime = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare(
        "UPDATE Orders SET Status = 'IN_PROGRESS', ActualStartTime = :start WHERE Id = :id"
        );
    query.bindValue(":start", orderStartTime.toString(Qt::ISODate));
    query.bindValue(":id", selectedOrderId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Błąd", "Nie można rozpocząć zlecenia");
        return;
    }

    // ⭐ Odśwież model
    myJobsModel->select();

    // ⭐ Odśwież przyciski
    updateOrderButtons();

    QMessageBox::information(
        this,
        "Zlecenie rozpoczęte",
        QString("Zlecenie #%1 rozpoczęte o %2\n\nCzas został uruchomiony!")
            .arg(selectedOrderId)
            .arg(orderStartTime.toString("hh:mm:ss"))
        );
}


void MainWindow::on_completeOrderButton_clicked()
{
    if (selectedOrderId == -1) return;

    // Pobierz czas startu z bazy
    QSqlQuery query;
    query.prepare("SELECT ActualStartTime FROM Orders WHERE Id = :id");
    query.bindValue(":id", selectedOrderId);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Błąd", "Nie można odczytać czasu startu");
        return;
    }

    QString startTimeStr = query.value("ActualStartTime").toString();
    QDateTime startTime = QDateTime::fromString(startTimeStr, Qt::ISODate);
    QDateTime endTime = QDateTime::currentDateTime();

    // Oblicz czas trwania w sekundach
    qint64 durationSeconds = startTime.secsTo(endTime);

    // Dialog do wpisania notatki
    bool ok;
    QString employeeNote = QInputDialog::getMultiLineText(
        this,
        "Zakończenie zlecenia",
        QString("Zlecenie trwało: %1 godz %2 min %3 sek\n\nDodaj notatkę (opcjonalnie):")
            .arg(durationSeconds / 3600)
            .arg((durationSeconds % 3600) / 60)
            .arg(durationSeconds % 60),
        "",
        &ok
        );

    if (!ok) return;  // Anulowano

    // Zaktualizuj zlecenie
    query.prepare(
        "UPDATE Orders SET "
        "Status = 'COMPLETED', "
        "EndTime = :end, "
        "Duration = :dur, "
        "EmployeeNote = :note "
        "WHERE Id = :id"
        );
    query.bindValue(":end", endTime.toString(Qt::ISODate));
    query.bindValue(":dur", durationSeconds);
    query.bindValue(":note", employeeNote);
    query.bindValue(":id", selectedOrderId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Błąd", "Nie można zakończyć zlecenia");
        return;
    }

    // ⭐ Odśwież model
    myJobsModel->select();

    // ⭐ Wyczyść selekcję (zlecenie zakończone)
    selectedOrderId = -1;
    updateOrderButtons();

    QMessageBox::information(
        this,
        "Sukces",
        QString("Zlecenie zakończone!\nCzas pracy: %1h %2m %3s")
            .arg(durationSeconds / 3600)
            .arg((durationSeconds % 3600) / 60)
            .arg(durationSeconds % 60)
        );
}
void MainWindow::loadMyJobs()
{
    myJobsModel->setFilter(QString("EmployeeId = %1").arg(currentUserId));
    myJobsModel->select();

    // Ustaw nazwy kolumn (opcjonalnie - dla czytelności)
    myJobsModel->setHeaderData(0, Qt::Horizontal, "ID");
    myJobsModel->setHeaderData(1, Qt::Horizontal, "Data startu");
    myJobsModel->setHeaderData(2, Qt::Horizontal, "Notatka kierownika");
    myJobsModel->setHeaderData(3, Qt::Horizontal, "Status");
    myJobsModel->setHeaderData(4, Qt::Horizontal, "Pojazd ID");
    myJobsModel->setHeaderData(5, Qt::Horizontal, "Pracownik ID");

    // ⭐ DODAJ - wymuszenie odświeżenia widoku
    ui->myJobsTable->reset();
}
void MainWindow::updateOrderButtons()
{
    if (selectedOrderId == -1) {
        // Brak wybranego zlecenia
        ui->acceptOrderButton->setEnabled(false);
        ui->rejectOrderButton->setEnabled(false);
        ui->startOrderButton->setEnabled(false);
        ui->completeOrderButton->setEnabled(false);
        ui->orderStatusLabel->setText("Wybierz zlecenie z listy");
        return;
    }

    // Pobierz status wybranego zlecenia
    QSqlQuery query;
    query.prepare("SELECT Status, StartDate, Note FROM Orders WHERE Id = :id");
    query.bindValue(":id", selectedOrderId);

    if (!query.exec() || !query.next()) {
        ui->orderStatusLabel->setText("Błąd odczytu zlecenia");
        return;
    }

    QString status = query.value("Status").toString();
    QString startDate = query.value("StartDate").toString();
    QString note = query.value("Note").toString();

    // Wyświetl info o zleceniu
    ui->orderStatusLabel->setText(
        QString("Zlecenie #%1 | Status: %2\nData: %3\n%4")
            .arg(selectedOrderId)
            .arg(getOrderStatusText(status))
            .arg(startDate)
            .arg(note.isEmpty() ? "" : "Uwagi: " + note)
        );

    // Włącz/wyłącz przyciski w zależności od statusu
    ui->acceptOrderButton->setEnabled(status == "NEW");
    ui->rejectOrderButton->setEnabled(status == "NEW");
    ui->startOrderButton->setEnabled(status == "ACCEPTED");
    ui->completeOrderButton->setEnabled(status == "IN_PROGRESS");
}
QString MainWindow::getOrderStatusText(const QString& status)
{
    if (status == "NEW") return "Nowe";
    if (status == "ACCEPTED") return "Przyjęte";
    if (status == "REJECTED") return "Odrzucone";
    if (status == "IN_PROGRESS") return "W trakcie";
    if (status == "COMPLETED") return "Zakończone";
    return status;
}

