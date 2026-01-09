#include "databasemanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

QSqlDatabase databasemanager::db;

bool databasemanager::connect()
{
    QString dbPath = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
        );

    QDir().mkpath(dbPath);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath + "/fleet.db");

    if (!db.open()) {
        qDebug() << " Base Error:" << db.lastError().text();
        return false;
    }

    return true;
}

void databasemanager::initDatabase()
{
    QSqlQuery query;

    query.exec("PRAGMA foreign_keys = ON;");

    // Tabela użytkowników
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS Users ("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Login TEXT UNIQUE NOT NULL,"
            "Password TEXT NOT NULL,"
            "Role TEXT NOT NULL"
            ")"
            )) {
    }
    // Tabela pojazdów
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS Vehicles ("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Brand TEXT NOT NULL,"
            "Model TEXT NOT NULL,"
            "Plate TEXT UNIQUE NOT NULL,"
            "Status TEXT NOT NULL"
            ")"
            )) {
    }
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS Orders ("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "StartDate TEXT NOT NULL,"              // Data planowanego startu (od kierownika)
            "Note TEXT,"                            // Notatka kierownika
            "Status TEXT NOT NULL,"                 // NEW, ACCEPTED, REJECTED, IN_PROGRESS, COMPLETED
            "VehicleId INTEGER NOT NULL,"
            "EmployeeId INTEGER NOT NULL,"
            "ActualStartTime TEXT,"                 // Kiedy pracownik wystartował zlecenie
            "EndTime TEXT,"                         // Kiedy pracownik zakończył
            "Duration INTEGER,"                     // Czas trwania w sekundach
            "EmployeeNote TEXT,"                    // Notatka pracownika po zakończeniu
            "FOREIGN KEY(VehicleId) REFERENCES Vehicles(Id),"
            "FOREIGN KEY(EmployeeId) REFERENCES Users(Id)"
            ")"
            )) {
    }

    query.exec(
        "INSERT OR IGNORE INTO Users (Login, Password, Role) VALUES "
        "('pracownik', '1234', 'EMPLOYEE'),"
        "('kierownik', 'admin', 'MANAGER')"
        );

}
