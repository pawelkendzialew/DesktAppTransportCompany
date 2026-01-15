#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "userservice.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill all the gaps");
        return;
    }

    UserService userService;
    User* user = userService.authenticate(login, password);

    if (user != nullptr) {
        emit loginSuccess(user->getRole(), user->getId());
        delete user;
        this->close();
    } else {
        QMessageBox::warning(this, "Log in Error", "Uncorrect login or password");
    }
}
