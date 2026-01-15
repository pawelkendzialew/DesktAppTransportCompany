#ifndef ADDVEHICLEDIALOG_H
#define ADDVEHICLEDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class AddvehicleDialog;
}

class AddvehicleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddvehicleDialog(QWidget *parent = nullptr);
    ~AddvehicleDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddvehicleDialog *ui;
};

#endif // ADDVEHICLEDIALOG_H
