/********************************************************************************
** Form generated from reading UI file 'addorderdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDORDERDIALOG_H
#define UI_ADDORDERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddOrderDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *employeeCombo;
    QLabel *label_2;
    QComboBox *vehicleCombo;
    QLabel *label_4;
    QDateTimeEdit *startDateEdit;
    QLabel *label_3;
    QLineEdit *noteEdit;
    QPushButton *saveButton;

    void setupUi(QDialog *AddOrderDialog)
    {
        if (AddOrderDialog->objectName().isEmpty())
            AddOrderDialog->setObjectName("AddOrderDialog");
        AddOrderDialog->resize(208, 248);
        horizontalLayout = new QHBoxLayout(AddOrderDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(AddOrderDialog);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        employeeCombo = new QComboBox(AddOrderDialog);
        employeeCombo->setObjectName("employeeCombo");

        verticalLayout->addWidget(employeeCombo);

        label_2 = new QLabel(AddOrderDialog);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        vehicleCombo = new QComboBox(AddOrderDialog);
        vehicleCombo->setObjectName("vehicleCombo");

        verticalLayout->addWidget(vehicleCombo);

        label_4 = new QLabel(AddOrderDialog);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        startDateEdit = new QDateTimeEdit(AddOrderDialog);
        startDateEdit->setObjectName("startDateEdit");
        startDateEdit->setCalendarPopup(true);

        verticalLayout->addWidget(startDateEdit);

        label_3 = new QLabel(AddOrderDialog);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        noteEdit = new QLineEdit(AddOrderDialog);
        noteEdit->setObjectName("noteEdit");

        verticalLayout->addWidget(noteEdit);

        saveButton = new QPushButton(AddOrderDialog);
        saveButton->setObjectName("saveButton");

        verticalLayout->addWidget(saveButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(AddOrderDialog);

        QMetaObject::connectSlotsByName(AddOrderDialog);
    } // setupUi

    void retranslateUi(QDialog *AddOrderDialog)
    {
        AddOrderDialog->setWindowTitle(QCoreApplication::translate("AddOrderDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddOrderDialog", "Employee", nullptr));
        label_2->setText(QCoreApplication::translate("AddOrderDialog", "Car", nullptr));
        label_4->setText(QCoreApplication::translate("AddOrderDialog", "Date", nullptr));
        label_3->setText(QCoreApplication::translate("AddOrderDialog", "Notes", nullptr));
        saveButton->setText(QCoreApplication::translate("AddOrderDialog", "Zapisz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddOrderDialog: public Ui_AddOrderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDORDERDIALOG_H
