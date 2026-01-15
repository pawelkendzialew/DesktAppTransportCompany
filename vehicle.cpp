#include "vehicle.h"

Vehicle::Vehicle()
    : m_id(-1)
{
}

Vehicle::Vehicle(int id, const QString& brand, const QString& model,
                 const QString& plate, const QString& status)
    : m_id(id)
    , m_brand(brand)
    , m_model(model)
    , m_plate(plate)
    , m_status(status)
{
}
