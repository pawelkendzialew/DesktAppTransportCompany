#include "addorderdialog.h"
#include "ui_addorderdialog.h"
#include "userservice.h"
#include "vehicleservice.h"
#include "orderservice.h"
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
    UserService userService;
    QList<User*> employees = userService.getAllEmployees();

    for (User* emp : employees) {
        ui->employeeCombo->addItem(emp->getLogin(), emp->getId());
        delete emp;
    }
}

void AddOrderDialog::loadVehicles()
{
    VehicleService vehicleService;
    QList<Vehicle*> vehicles = vehicleService.getAvailableVehicles();

    for (Vehicle* veh : vehicles) {
        ui->vehicleCombo->addItem(veh->getPlate(), veh->getId());
        delete veh;
    }
}

void AddOrderDialog::on_saveButton_clicked()
{
    OrderService orderService;

    if (orderService.addOrder(
            ui->startDateEdit->date().toString("yyyy-MM-dd"),
            ui->noteEdit->text(),
            ui->vehicleCombo->currentData().toInt(),
            ui->employeeCombo->currentData().toInt())) {
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Unable to add the job");
    }
}
