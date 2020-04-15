/********************************************************************************
** Form generated from reading UI file 'obs_console_test.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBS_CONSOLE_TEST_H
#define UI_OBS_CONSOLE_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include "myslider.h"

QT_BEGIN_NAMESPACE

class Ui_OBS_console_TESTClass
{
public:
    MySlider *slider;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *OBS_console_TESTClass)
    {
        if (OBS_console_TESTClass->objectName().isEmpty())
            OBS_console_TESTClass->setObjectName(QStringLiteral("OBS_console_TESTClass"));
        OBS_console_TESTClass->resize(647, 400);
        slider = new MySlider(OBS_console_TESTClass);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setGeometry(QRect(20, 280, 600, 22));
        slider->setPageStep(1);
        slider->setOrientation(Qt::Horizontal);
        lineEdit = new QLineEdit(OBS_console_TESTClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 250, 100, 20));
        lineEdit_2 = new QLineEdit(OBS_console_TESTClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(20, 310, 61, 20));

        retranslateUi(OBS_console_TESTClass);

        QMetaObject::connectSlotsByName(OBS_console_TESTClass);
    } // setupUi

    void retranslateUi(QWidget *OBS_console_TESTClass)
    {
        OBS_console_TESTClass->setWindowTitle(QApplication::translate("OBS_console_TESTClass", "OBS_console_TEST", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBS_console_TESTClass: public Ui_OBS_console_TESTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBS_CONSOLE_TEST_H
