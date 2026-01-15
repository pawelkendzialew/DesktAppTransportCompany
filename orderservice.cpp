#include "orderservice.h"
#include <QSqlQuery>
#include <QVariant>

OrderService::OrderService()
{
}

bool OrderService::addOrder(const QString& startDate, const QString& note,
                            int vehicleId, int employeeId)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO Orders (StartDate, Note, Status, VehicleId, EmployeeId) "
        "VALUES (:d, :n, 'NEW', :v, :e)"
        );
    query.bindValue(":d", startDate);
    query.bindValue(":n", note);
    query.bindValue(":v", vehicleId);
    query.bindValue(":e", employeeId);

    return query.exec();
}

bool OrderService::deleteOrder(int orderId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Orders WHERE Id = :id");
    query.bindValue(":id", orderId);

    return query.exec();
}

bool OrderService::deleteOrdersByEmployee(int employeeId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Orders WHERE EmployeeId = :id");
    query.bindValue(":id", employeeId);

    return query.exec();
}

bool OrderService::deleteOrdersByVehicle(int vehicleId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Orders WHERE VehicleId = :id");
    query.bindValue(":id", vehicleId);

    return query.exec();
}

Order* OrderService::getOrderById(int orderId)
{
    QSqlQuery query;
    query.prepare(
        "SELECT Id, StartDate, Note, Status, VehicleId, EmployeeId, "
        "ActualStartTime, EndTime, Duration, EmployeeNote "
        "FROM Orders WHERE Id = :id"
        );
    query.bindValue(":id", orderId);

    if (query.exec() && query.next()) {
        Order* order = new Order(
            query.value("Id").toInt(),
            query.value("StartDate").toString(),
            query.value("Note").toString(),
            query.value("Status").toString(),
            query.value("VehicleId").toInt(),
            query.value("EmployeeId").toInt()
            );

        QString startTimeStr = query.value("ActualStartTime").toString();
        if (!startTimeStr.isEmpty()) {
            order->setActualStartTime(QDateTime::fromString(startTimeStr, Qt::ISODate));
        }

        QString endTimeStr = query.value("EndTime").toString();
        if (!endTimeStr.isEmpty()) {
            order->setEndTime(QDateTime::fromString(endTimeStr, Qt::ISODate));
        }

        order->setDuration(query.value("Duration").toInt());
        order->setEmployeeNote(query.value("EmployeeNote").toString());

        return order;
    }

    return nullptr;
}

QList<Order*> OrderService::getOrdersByEmployee(int employeeId)
{
    QList<Order*> orders;
    QSqlQuery query;
    query.prepare(
        "SELECT Id, StartDate, Note, Status, VehicleId, EmployeeId "
        "FROM Orders WHERE EmployeeId = :id"
        );
    query.bindValue(":id", employeeId);

    if (query.exec()) {
        while (query.next()) {
            orders.append(new Order(
                query.value("Id").toInt(),
                query.value("StartDate").toString(),
                query.value("Note").toString(),
                query.value("Status").toString(),
                query.value("VehicleId").toInt(),
                query.value("EmployeeId").toInt()
                ));
        }
    }

    return orders;
}
QList<Order*> OrderService::getActiveOrders()
{
    QList<Order*> orders;
    QSqlQuery query(
        "SELECT Id, StartDate, Note, Status, VehicleId, EmployeeId "
        "FROM Orders WHERE Status IN ('NEW', 'ACCEPTED', 'IN_PROGRESS')"
        );

    while (query.next()) {
        orders.append(new Order(
            query.value("Id").toInt(),
            query.value("StartDate").toString(),
            query.value("Note").toString(),
            query.value("Status").toString(),
            query.value("VehicleId").toInt(),
            query.value("EmployeeId").toInt()
            ));
    }

    return orders;
}

QList<Order*> OrderService::getCompletedOrders()
{
    QList<Order*> orders;
    QSqlQuery query(
        "SELECT Id, StartDate, Note, Status, VehicleId, EmployeeId, "
        "ActualStartTime, EndTime, Duration, EmployeeNote "
        "FROM Orders WHERE Status IN ('COMPLETED', 'REJECTED')"
        );

    while (query.next()) {
        Order* order = new Order(
            query.value("Id").toInt(),
            query.value("StartDate").toString(),
            query.value("Note").toString(),
            query.value("Status").toString(),
            query.value("VehicleId").toInt(),
            query.value("EmployeeId").toInt()
            );

        QString startTimeStr = query.value("ActualStartTime").toString();
        if (!startTimeStr.isEmpty()) {
            order->setActualStartTime(QDateTime::fromString(startTimeStr, Qt::ISODate));
        }

        QString endTimeStr = query.value("EndTime").toString();
        if (!endTimeStr.isEmpty()) {
            order->setEndTime(QDateTime::fromString(endTimeStr, Qt::ISODate));
        }

        order->setDuration(query.value("Duration").toInt());
        order->setEmployeeNote(query.value("EmployeeNote").toString());

        orders.append(order);
    }

    return orders;
}

bool OrderService::acceptOrder(int orderId)
{
    QSqlQuery query;
    query.prepare("UPDATE Orders SET Status = 'ACCEPTED' WHERE Id = :id");
    query.bindValue(":id", orderId);

    return query.exec();
}

bool OrderService::rejectOrder(int orderId)
{
    QSqlQuery query;
    query.prepare("UPDATE Orders SET Status = 'REJECTED' WHERE Id = :id");
    query.bindValue(":id", orderId);

    return query.exec();
}

bool OrderService::startOrder(int orderId, const QDateTime& startTime)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE Orders SET Status = 'IN_PROGRESS', ActualStartTime = :start WHERE Id = :id"
        );
    query.bindValue(":start", startTime.toString(Qt::ISODate));
    query.bindValue(":id", orderId);

    return query.exec();
}

bool OrderService::completeOrder(int orderId, const QDateTime& endTime,
                                 int duration, const QString& employeeNote)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE Orders SET Status = 'COMPLETED', EndTime = :end, "
        "Duration = :dur, EmployeeNote = :note WHERE Id = :id"
        );
    query.bindValue(":end", endTime.toString(Qt::ISODate));
    query.bindValue(":dur", duration);
    query.bindValue(":note", employeeNote);
    query.bindValue(":id", orderId);

    return query.exec();
}

QString OrderService::getStatusText(const QString& status)
{
    if (status == "NEW") return "New";
    if (status == "ACCEPTED") return "Accepted";
    if (status == "REJECTED") return "Rejected";
    if (status == "IN_PROGRESS") return "During";
    if (status == "COMPLETED") return "Done";
    return status;
}

QString OrderService::formatDuration(int seconds)
{
    if (seconds <= 0) return "---";

    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    return QString("%1h %2m %3s").arg(hours).arg(minutes).arg(secs);
}
