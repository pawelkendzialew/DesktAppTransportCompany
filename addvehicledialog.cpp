#include "addvehicledialog.h"
#include "ui_addvehicledialog.h"
#include "vehicleservice.h"
#include <QMessageBox>

AddvehicleDialog::AddvehicleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddvehicleDialog)
{
    ui->setupUi(this);
}

AddvehicleDialog::~AddvehicleDialog()
{
    delete ui;
}

void AddvehicleDialog::on_saveButton_clicked()
{
    VehicleService vehicleService;

    if (vehicleService.addVehicle(
            ui->brandEdit->text(),
            ui->modelEdit->text(),
            ui->plateEdit->text(),
            ui->statusCombo->currentText())) {
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Unable to add vehicle");
    }
}
