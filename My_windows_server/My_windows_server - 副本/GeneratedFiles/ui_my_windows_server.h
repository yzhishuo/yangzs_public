/********************************************************************************
** Form generated from reading UI file 'my_windows_server.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_WINDOWS_SERVER_H
#define UI_MY_WINDOWS_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_My_windows_serverClass
{
public:
    QPushButton *btn_start;
    QPushButton *btn_new_file;

    void setupUi(QWidget *My_windows_serverClass)
    {
        if (My_windows_serverClass->objectName().isEmpty())
            My_windows_serverClass->setObjectName(QStringLiteral("My_windows_serverClass"));
        My_windows_serverClass->resize(600, 400);
        btn_start = new QPushButton(My_windows_serverClass);
        btn_start->setObjectName(QStringLiteral("btn_start"));
        btn_start->setGeometry(QRect(20, 30, 75, 31));
        btn_new_file = new QPushButton(My_windows_serverClass);
        btn_new_file->setObjectName(QStringLiteral("btn_new_file"));
        btn_new_file->setGeometry(QRect(110, 30, 75, 31));

        retranslateUi(My_windows_serverClass);

        QMetaObject::connectSlotsByName(My_windows_serverClass);
    } // setupUi

    void retranslateUi(QWidget *My_windows_serverClass)
    {
        My_windows_serverClass->setWindowTitle(QApplication::translate("My_windows_serverClass", "My_windows_server", nullptr));
        btn_start->setText(QApplication::translate("My_windows_serverClass", "\346\211\223\345\274\200\345\244\226\351\203\250", nullptr));
        btn_new_file->setText(QApplication::translate("My_windows_serverClass", "\345\210\233\345\273\272\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class My_windows_serverClass: public Ui_My_windows_serverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_WINDOWS_SERVER_H
