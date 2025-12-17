/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *Samochody;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTableView *vehiclesTable;
    QPushButton *addvehicleButton;
    QWidget *Pracownicy;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTableView *employeesTable;
    QPushButton *addEmployeeButton;
    QWidget *Zlecenia;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QTableView *ordersTable;
    QPushButton *addOrderButton;
    QWidget *MojeZlecenie;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(675, 484);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        Samochody = new QWidget();
        Samochody->setObjectName("Samochody");
        layoutWidget = new QWidget(Samochody);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 631, 371));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        vehiclesTable = new QTableView(layoutWidget);
        vehiclesTable->setObjectName("vehiclesTable");

        verticalLayout->addWidget(vehiclesTable);

        addvehicleButton = new QPushButton(layoutWidget);
        addvehicleButton->setObjectName("addvehicleButton");

        verticalLayout->addWidget(addvehicleButton);

        tabWidget->addTab(Samochody, QString());
        Pracownicy = new QWidget();
        Pracownicy->setObjectName("Pracownicy");
        layoutWidget1 = new QWidget(Pracownicy);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(5, 11, 641, 381));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        employeesTable = new QTableView(layoutWidget1);
        employeesTable->setObjectName("employeesTable");

        verticalLayout_2->addWidget(employeesTable);

        addEmployeeButton = new QPushButton(layoutWidget1);
        addEmployeeButton->setObjectName("addEmployeeButton");

        verticalLayout_2->addWidget(addEmployeeButton);

        tabWidget->addTab(Pracownicy, QString());
        Zlecenia = new QWidget();
        Zlecenia->setObjectName("Zlecenia");
        layoutWidget2 = new QWidget(Zlecenia);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(0, 10, 641, 381));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ordersTable = new QTableView(layoutWidget2);
        ordersTable->setObjectName("ordersTable");

        verticalLayout_3->addWidget(ordersTable);

        addOrderButton = new QPushButton(layoutWidget2);
        addOrderButton->setObjectName("addOrderButton");

        verticalLayout_3->addWidget(addOrderButton);

        tabWidget->addTab(Zlecenia, QString());
        MojeZlecenie = new QWidget();
        MojeZlecenie->setObjectName("MojeZlecenie");
        tabWidget->addTab(MojeZlecenie, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 675, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addvehicleButton->setText(QCoreApplication::translate("MainWindow", "Add Car", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Samochody), QCoreApplication::translate("MainWindow", "Cars", nullptr));
        addEmployeeButton->setText(QCoreApplication::translate("MainWindow", "Add Employee", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Pracownicy), QCoreApplication::translate("MainWindow", "Employees", nullptr));
        addOrderButton->setText(QCoreApplication::translate("MainWindow", "Add job", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Zlecenia), QCoreApplication::translate("MainWindow", "Jobs", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(MojeZlecenie), QCoreApplication::translate("MainWindow", "My Job", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
