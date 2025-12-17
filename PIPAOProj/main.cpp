#include "mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QApplication>

#include "databasemanager.h"
#include "loginwindow.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if (!databasemanager::connect())
        return -1;
    databasemanager::initDatabase();

    LoginWindow login;
    MainWindow mainWindow;

    QObject::connect(&login, &LoginWindow::loginSuccess,
                     [&](const QString& role)
                     {
                         mainWindow.setRole(role);
                         mainWindow.show();
                     });

    login.show();
    return a.exec();
}
