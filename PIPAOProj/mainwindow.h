#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

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
    void setRole(const QString& role);

private slots:
    void on_addEmployeeButton_clicked();

    void on_addvehicleButton_clicked();

    void on_addOrderButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *vehiclesModel;
    QSqlTableModel *employeesModel;
    QSqlTableModel *ordersModel;
};
#endif // MAINWINDOW_H
