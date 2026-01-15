#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDateTime>

class Order
{
public:
    Order();
    Order(int id, const QString& startDate, const QString& note,
          const QString& status, int vehicleId, int employeeId);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getStartDate() const { return m_startDate; }
    void setStartDate(const QString& date) { m_startDate = date; }

    QString getNote() const { return m_note; }
    void setNote(const QString& note) { m_note = note; }

    QString getStatus() const { return m_status; }
    void setStatus(const QString& status) { m_status = status; }

    int getVehicleId() const { return m_vehicleId; }
    void setVehicleId(int id) { m_vehicleId = id; }

    int getEmployeeId() const { return m_employeeId; }
    void setEmployeeId(int id) { m_employeeId = id; }

    QDateTime getActualStartTime() const { return m_actualStartTime; }
    void setActualStartTime(const QDateTime& time) { m_actualStartTime = time; }

    QDateTime getEndTime() const { return m_endTime; }
    void setEndTime(const QDateTime& time) { m_endTime = time; }

    int getDuration() const { return m_duration; }
    void setDuration(int seconds) { m_duration = seconds; }

    QString getEmployeeNote() const { return m_employeeNote; }
    void setEmployeeNote(const QString& note) { m_employeeNote = note; }

    bool isNew() const { return m_status == "NEW"; }
    bool isAccepted() const { return m_status == "ACCEPTED"; }
    bool isRejected() const { return m_status == "REJECTED"; }
    bool isInProgress() const { return m_status == "IN_PROGRESS"; }
    bool isCompleted() const { return m_status == "COMPLETED"; }

private:
    int m_id;
    QString m_startDate;
    QString m_note;
    QString m_status;
    int m_vehicleId;
    int m_employeeId;
    QDateTime m_actualStartTime;
    QDateTime m_endTime;
    int m_duration;
    QString m_employeeNote;
};

#endif // ORDER_H
