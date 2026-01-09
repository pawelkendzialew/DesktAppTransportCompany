#include "addorderdialog.h"
#include "ui_addorderdialog.h"

#include <QSqlQuery>
#include <QMessageBox>

AddOrderDialog::AddOrderDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddOrderDialog)
{
    ui->setupUi(this);

    loadEmployees();
    loadVehicles();
}

AddOrderDialog::~AddOrderDialog()
{
    delete ui;
}

void AddOrderDialog::loadEmployees()
{
    QSqlQuery q("SELECT Id, Login FROM Users WHERE Role='EMPLOYEE'");
    while (q.next()) {
        ui->employeeCombo->addItem(
            q.value("Login").toString(),
            q.value("Id")
            );
    }
}

void AddOrderDialog::loadVehicles()
{
    QSqlQuery q("SELECT Id, Plate FROM Vehicles WHERE Status='AVAILABLE'");
    while (q.next()) {
        ui->vehicleCombo->addItem(
            q.value("Plate").toString(),
            q.value("Id")
            );
    }
}

void AddOrderDialog::on_saveButton_clicked()
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO Orders "
        "(StartDate, Note, Status, VehicleId, EmployeeId) "
        "VALUES (:d, :n, 'NEW', :v, :e)"
        );

    query.bindValue(":d", ui->startDateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":n", ui->noteEdit->text());
    query.bindValue(":v", ui->vehicleCombo->currentData());
    query.bindValue(":e", ui->employeeCombo->currentData());

    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Unable to add the job");
        return;
    }

    accept();
}
