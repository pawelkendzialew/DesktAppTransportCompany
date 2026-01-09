#include "addvehicledialog.h"
#include "ui_addvehicledialog.h"

#include <QSqlQuery>
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
    QSqlQuery query;
    query.prepare(
        "INSERT INTO Vehicles (Brand, Model, Plate, Status) "
        "VALUES (:b, :m, :p, :s)"
        );
    query.bindValue(":b", ui->brandEdit->text());
    query.bindValue(":m", ui->modelEdit->text());
    query.bindValue(":p", ui->plateEdit->text());
    query.bindValue(":s", ui->statusCombo->currentText());

    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Unable to add vehicle");
        return;
    }

    accept();
}
