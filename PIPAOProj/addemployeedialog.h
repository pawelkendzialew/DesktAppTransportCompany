#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <QDialog>

namespace Ui {
class AddEmployeeDialog;
}

class AddEmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployeeDialog(QWidget *parent = nullptr);
    ~AddEmployeeDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddEmployeeDialog *ui;
};

#endif // ADDEMPLOYEEDIALOG_H
