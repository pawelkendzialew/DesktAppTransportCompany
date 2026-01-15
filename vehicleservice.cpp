#include "vehicleservice.h"
#include <QSqlQuery>
#include <QVariant>

VehicleService::VehicleService()
{
}

bool VehicleService::addVehicle(const QString& brand, const QString& model,
                                const QString& plate, const QString& status)
{
    if (plateExists(plate)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Vehicles (Brand, Model, Plate, Status) VALUES (:b, :m, :p, :s)");
    query.bindValue(":b", brand);
    query.bindValue(":m", model);
    query.bindValue(":p", plate);
    query.bindValue(":s", status);

    return query.exec();
}

bool VehicleService::deleteVehicle(int vehicleId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Vehicles WHERE Id = :id");
    query.bindValue(":id", vehicleId);

    return query.exec();
}

bool VehicleService::updateVehicle(const Vehicle& vehicle)
{
    QSqlQuery query;
    query.prepare("UPDATE Vehicles SET Brand = :b, Model = :m, Plate = :p, Status = :s WHERE Id = :id");
    query.bindValue(":b", vehicle.getBrand());
    query.bindValue(":m", vehicle.getModel());
    query.bindValue(":p", vehicle.getPlate());
    query.bindValue(":s", vehicle.getStatus());
    query.bindValue(":id", vehicle.getId());

    return query.exec();
}

QList<Vehicle*> VehicleService::getAllVehicles()
{
    QList<Vehicle*> vehicles;
    QSqlQuery query("SELECT Id, Brand, Model, Plate, Status FROM Vehicles");

    while (query.next()) {
        int id = query.value("Id").toInt();
        QString brand = query.value("Brand").toString();
        QString model = query.value("Model").toString();
        QString plate = query.value("Plate").toString();
        QString status = query.value("Status").toString();

        vehicles.append(new Vehicle(id, brand, model, plate, status));
    }

    return vehicles;
}

QList<Vehicle*> VehicleService::getAvailableVehicles()
{
    QList<Vehicle*> vehicles;
    QSqlQuery query("SELECT Id, Brand, Model, Plate, Status FROM Vehicles WHERE Status='AVAILABLE'");

    while (query.next()) {
        int id = query.value("Id").toInt();
        QString brand = query.value("Brand").toString();
        QString model = query.value("Model").toString();
        QString plate = query.value("Plate").toString();
        QString status = query.value("Status").toString();

        vehicles.append(new Vehicle(id, brand, model, plate, status));
    }

    return vehicles;
}

Vehicle* VehicleService::getVehicleById(int vehicleId)
{
    QSqlQuery query;
    query.prepare("SELECT Id, Brand, Model, Plate, Status FROM Vehicles WHERE Id = :id");
    query.bindValue(":id", vehicleId);

    if (query.exec() && query.next()) {
        int id = query.value("Id").toInt();
        QString brand = query.value("Brand").toString();
        QString model = query.value("Model").toString();
        QString plate = query.value("Plate").toString();
        QString status = query.value("Status").toString();

        return new Vehicle(id, brand, model, plate, status);
    }

    return nullptr;
}

int VehicleService::getVehicleOrderCount(int vehicleId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Orders WHERE VehicleId = :id");
    query.bindValue(":id", vehicleId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

bool VehicleService::plateExists(const QString& plate)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Vehicles WHERE Plate = :plate");
    query.bindValue(":plate", plate);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
