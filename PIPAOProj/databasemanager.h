#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>

class databasemanager
{
public:
    static bool connect();
    static void initDatabase();

private:
    static QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
