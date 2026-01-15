#include "order.h"

Order::Order()
    : m_id(-1)
    , m_vehicleId(-1)
    , m_employeeId(-1)
    , m_duration(0)
{
}

Order::Order(int id, const QString& startDate, const QString& note,
             const QString& status, int vehicleId, int employeeId)
    : m_id(id)
    , m_startDate(startDate)
    , m_note(note)
    , m_status(status)
    , m_vehicleId(vehicleId)
    , m_employeeId(employeeId)
    , m_duration(0)
{
}
