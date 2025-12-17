#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"

#include <QSqlQuery>
#include <QMessageBox>

AddEmployeeDialog::AddEmployeeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEmployeeDialog)
{
    ui->setupUi(this);
}

AddEmployeeDialog::~AddEmployeeDialog()
{
    delete ui;
}

void AddEmployeeDialog::on_saveButton_clicked()
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO Users (Login, Password, Role) "
        "VALUES (:l, :p, 'Pracownik')"
        );
    query.bindValue(":l", ui->loginEdit->text());
    query.bindValue(":p", ui->passwordEdit->text());

    if (!query.exec()) {
        QMessageBox::warning(this, "Błąd", "Nie można dodać pracownika");
        return;
    }

    accept();
}
