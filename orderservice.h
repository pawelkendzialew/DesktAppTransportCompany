#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include "order.h"
#include <QList>
#include <QDateTime>

class OrderService
{
public:
    OrderService();

    // CRUD operacje
    bool addOrder(const QString& startDate, const QString& note,
                  int vehicleId, int employeeId);
    bool deleteOrder(int orderId);
    bool deleteOrdersByEmployee(int employeeId);
    bool deleteOrdersByVehicle(int vehicleId);

    Order* getOrderById(int orderId);
    QList<Order*> getOrdersByEmployee(int employeeId);
    QList<Order*> getActiveOrders();
    QList<Order*> getCompletedOrders();

    // Operacje pracownika na zleceniach
    bool acceptOrder(int orderId);
    bool rejectOrder(int orderId);
    bool startOrder(int orderId, const QDateTime& startTime);
    bool completeOrder(int orderId, const QDateTime& endTime,
                       int duration, const QString& employeeNote);

    // Pomocnicze
    QString getStatusText(const QString& status);
    QString formatDuration(int seconds);
};

#endif // ORDERSERVICE_H
