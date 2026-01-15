#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

class Vehicle
{
public:
    Vehicle();
    Vehicle(int id, const QString& brand, const QString& model,
            const QString& plate, const QString& status);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getBrand() const { return m_brand; }
    void setBrand(const QString& brand) { m_brand = brand; }

    QString getModel() const { return m_model; }
    void setModel(const QString& model) { m_model = model; }

    QString getPlate() const { return m_plate; }
    void setPlate(const QString& plate) { m_plate = plate; }

    QString getStatus() const { return m_status; }
    void setStatus(const QString& status) { m_status = status; }

    QString getFullName() const { return m_brand + " " + m_model; }
    bool isAvailable() const { return m_status == "AVAILABLE"; }

private:
    int m_id;
    QString m_brand;
    QString m_model;
    QString m_plate;
    QString m_status;
};

#endif // VEHICLE_H
