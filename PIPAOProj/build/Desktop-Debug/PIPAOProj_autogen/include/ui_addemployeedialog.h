/********************************************************************************
** Form generated from reading UI file 'addemployeedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEMPLOYEEDIALOG_H
#define UI_ADDEMPLOYEEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddEmployeeDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *loginEdit;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QPushButton *saveButton;

    void setupUi(QDialog *AddEmployeeDialog)
    {
        if (AddEmployeeDialog->objectName().isEmpty())
            AddEmployeeDialog->setObjectName("AddEmployeeDialog");
        AddEmployeeDialog->resize(158, 139);
        layoutWidget = new QWidget(AddEmployeeDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 0, 135, 126));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        loginEdit = new QLineEdit(layoutWidget);
        loginEdit->setObjectName("loginEdit");

        verticalLayout->addWidget(loginEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        passwordEdit = new QLineEdit(layoutWidget);
        passwordEdit->setObjectName("passwordEdit");

        verticalLayout->addWidget(passwordEdit);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName("saveButton");

        verticalLayout->addWidget(saveButton);


        retranslateUi(AddEmployeeDialog);

        QMetaObject::connectSlotsByName(AddEmployeeDialog);
    } // setupUi

    void retranslateUi(QDialog *AddEmployeeDialog)
    {
        AddEmployeeDialog->setWindowTitle(QCoreApplication::translate("AddEmployeeDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddEmployeeDialog", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("AddEmployeeDialog", "Password", nullptr));
        saveButton->setText(QCoreApplication::translate("AddEmployeeDialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddEmployeeDialog: public Ui_AddEmployeeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEMPLOYEEDIALOG_H
