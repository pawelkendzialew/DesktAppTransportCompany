#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setRole(const QString& role, int userId);

private slots:
    void on_addEmployeeButton_clicked();

    void on_addvehicleButton_clicked();

    void on_addOrderButton_clicked();

    void on_myJobsTable_clicked(const QModelIndex &index);

    void on_acceptOrderButton_clicked();

    void on_rejectOrderButton_clicked();

    void on_startOrderButton_clicked();

    void on_completeOrderButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *vehiclesModel;
    QSqlTableModel *employeesModel;
    QSqlTableModel *ordersModel;

    QString currentUserRole;
    int currentUserId;

    QSqlTableModel *myJobsModel;
    int selectedOrderId;
    QDateTime orderStartTime;

    void loadMyJobs();
    void updateOrderButtons();
    QString getOrderStatusText(const QString& status);
};
#endif // MAINWINDOW_H
