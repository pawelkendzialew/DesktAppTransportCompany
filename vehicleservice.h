#ifndef VEHICLESERVICE_H
#define VEHICLESERVICE_H

#include "vehicle.h"
#include <QList>

class VehicleService
{
public:
    VehicleService();

    // CRUD operacje
    bool addVehicle(const QString& brand, const QString& model,
                    const QString& plate, const QString& status);
    bool deleteVehicle(int vehicleId);
    bool updateVehicle(const Vehicle& vehicle);

    QList<Vehicle*> getAllVehicles();
    QList<Vehicle*> getAvailableVehicles();
    Vehicle* getVehicleById(int vehicleId);

    // Pomocnicze
    int getVehicleOrderCount(int vehicleId);
    bool plateExists(const QString& plate);
};

#endif // VEHICLESERVICE_H
