#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"
#include "userservice.h"
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
    UserService userService;

    if (userService.addEmployee(ui->loginEdit->text(), ui->passwordEdit->text())) {
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Unable to add employee");
    }
}
