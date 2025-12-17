/********************************************************************************
** Form generated from reading UI file 'addvehicledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDVEHICLEDIALOG_H
#define UI_ADDVEHICLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddvehicleDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *brandEdit;
    QLabel *label_2;
    QLineEdit *modelEdit;
    QLabel *label_3;
    QLineEdit *plateEdit;
    QComboBox *statusCombo;
    QPushButton *saveButton;

    void setupUi(QWidget *AddvehicleDialog)
    {
        if (AddvehicleDialog->objectName().isEmpty())
            AddvehicleDialog->setObjectName("AddvehicleDialog");
        AddvehicleDialog->resize(243, 201);
        layoutWidget = new QWidget(AddvehicleDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 0, 221, 204));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        brandEdit = new QLineEdit(layoutWidget);
        brandEdit->setObjectName("brandEdit");

        verticalLayout->addWidget(brandEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        modelEdit = new QLineEdit(layoutWidget);
        modelEdit->setObjectName("modelEdit");

        verticalLayout->addWidget(modelEdit);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        plateEdit = new QLineEdit(layoutWidget);
        plateEdit->setObjectName("plateEdit");

        verticalLayout->addWidget(plateEdit);

        statusCombo = new QComboBox(layoutWidget);
        statusCombo->addItem(QString());
        statusCombo->addItem(QString());
        statusCombo->addItem(QString());
        statusCombo->setObjectName("statusCombo");

        verticalLayout->addWidget(statusCombo);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName("saveButton");

        verticalLayout->addWidget(saveButton);


        retranslateUi(AddvehicleDialog);

        statusCombo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AddvehicleDialog);
    } // setupUi

    void retranslateUi(QWidget *AddvehicleDialog)
    {
        AddvehicleDialog->setWindowTitle(QCoreApplication::translate("AddvehicleDialog", "Form", nullptr));
        label->setText(QCoreApplication::translate("AddvehicleDialog", "Brand", nullptr));
        label_2->setText(QCoreApplication::translate("AddvehicleDialog", "Model", nullptr));
        label_3->setText(QCoreApplication::translate("AddvehicleDialog", "Plates", nullptr));
        statusCombo->setItemText(0, QCoreApplication::translate("AddvehicleDialog", "AVAILABLE", nullptr));
        statusCombo->setItemText(1, QCoreApplication::translate("AddvehicleDialog", "UNAVAILABLE", nullptr));
        statusCombo->setItemText(2, QCoreApplication::translate("AddvehicleDialog", "SERVICE", nullptr));

        statusCombo->setCurrentText(QCoreApplication::translate("AddvehicleDialog", "AVAILABLE", nullptr));
        saveButton->setText(QCoreApplication::translate("AddvehicleDialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddvehicleDialog: public Ui_AddvehicleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDVEHICLEDIALOG_H
