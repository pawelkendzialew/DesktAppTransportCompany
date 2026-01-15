#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "user.h"
#include <QList>
#include <QString>

class UserService
{
public:
    UserService();

    // Autoryzacja
    User* authenticate(const QString& login, const QString& password);

    // CRUD operacje
    bool addEmployee(const QString& login, const QString& password);
    bool deleteEmployee(int userId);
    QList<User*> getAllEmployees();
    User* getUserById(int userId);

    // Pomocnicze
    int getEmployeeOrderCount(int employeeId);

private:
    bool userExists(const QString& login);
};

#endif // USERSERVICE_H
