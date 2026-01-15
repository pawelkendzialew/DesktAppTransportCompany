#include "userservice.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

UserService::UserService()
{
}

User* UserService::authenticate(const QString& login, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT Id, Role FROM Users WHERE Login = :login AND Password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int id = query.value("Id").toInt();
        QString role = query.value("Role").toString();
        return new User(id, login, password, role);
    }

    return nullptr;
}

bool UserService::addEmployee(const QString& login, const QString& password)
{
    if (userExists(login)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Users (Login, Password, Role) VALUES (:l, :p, 'EMPLOYEE')");
    query.bindValue(":l", login);
    query.bindValue(":p", password);

    return query.exec();
}

bool UserService::deleteEmployee(int userId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Users WHERE Id = :id");
    query.bindValue(":id", userId);

    return query.exec();
}

QList<User*> UserService::getAllEmployees()
{
    QList<User*> employees;
    QSqlQuery query("SELECT Id, Login, Password, Role FROM Users WHERE Role='EMPLOYEE'");

    while (query.next()) {
        int id = query.value("Id").toInt();
        QString login = query.value("Login").toString();
        QString password = query.value("Password").toString();
        QString role = query.value("Role").toString();

        employees.append(new User(id, login, password, role));
    }

    return employees;
}

User* UserService::getUserById(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT Id, Login, Password, Role FROM Users WHERE Id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        int id = query.value("Id").toInt();
        QString login = query.value("Login").toString();
        QString password = query.value("Password").toString();
        QString role = query.value("Role").toString();

        return new User(id, login, password, role);
    }

    return nullptr;
}

int UserService::getEmployeeOrderCount(int employeeId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Orders WHERE EmployeeId = :id");
    query.bindValue(":id", employeeId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

bool UserService::userExists(const QString& login)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Users WHERE Login = :login");
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
