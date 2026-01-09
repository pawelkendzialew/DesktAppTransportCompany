#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QSqlQuery>
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
        QMessageBox::warning(this, "Błąd", "Uzupełnij wszystkie pola");
        return;
    }

    QSqlQuery query;
    query.prepare(
        "SELECT Id, Role FROM Users WHERE Login = :login AND Password = :password"
        );
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int userId = query.value("Id").toInt();
        QString role = query.value("Role").toString();

        emit loginSuccess(role, userId);
        this->close();

    } else {
        QMessageBox::warning(
            this,
            "Błąd logowania",
            "Nieprawidłowy login lub hasło"
            );
    }
}
