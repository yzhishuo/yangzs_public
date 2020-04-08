/********************************************************************************
** Form generated from reading UI file 'my_file_watch_test.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_FILE_WATCH_TEST_H
#define UI_MY_FILE_WATCH_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MY_File_watch_TestClass
{
public:
    QTextEdit *textEdit;
    QPushButton *btn_monitor;
    QPushButton *btn_insert;
    QPushButton *btn_find;
    QPushButton *btn_update;
    QPushButton *btn_delete;
    QPushButton *btn_open_filedir;
    QLineEdit *Lined_folder_path;

    void setupUi(QWidget *MY_File_watch_TestClass)
    {
        if (MY_File_watch_TestClass->objectName().isEmpty())
            MY_File_watch_TestClass->setObjectName(QStringLiteral("MY_File_watch_TestClass"));
        MY_File_watch_TestClass->resize(600, 400);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        MY_File_watch_TestClass->setFont(font);
        textEdit = new QTextEdit(MY_File_watch_TestClass);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 290, 581, 101));
        btn_monitor = new QPushButton(MY_File_watch_TestClass);
        btn_monitor->setObjectName(QStringLiteral("btn_monitor"));
        btn_monitor->setGeometry(QRect(390, 60, 91, 41));
        btn_insert = new QPushButton(MY_File_watch_TestClass);
        btn_insert->setObjectName(QStringLiteral("btn_insert"));
        btn_insert->setGeometry(QRect(510, 10, 81, 41));
        btn_find = new QPushButton(MY_File_watch_TestClass);
        btn_find->setObjectName(QStringLiteral("btn_find"));
        btn_find->setGeometry(QRect(510, 60, 81, 41));
        btn_update = new QPushButton(MY_File_watch_TestClass);
        btn_update->setObjectName(QStringLiteral("btn_update"));
        btn_update->setGeometry(QRect(510, 110, 81, 41));
        btn_delete = new QPushButton(MY_File_watch_TestClass);
        btn_delete->setObjectName(QStringLiteral("btn_delete"));
        btn_delete->setGeometry(QRect(510, 160, 81, 41));
        btn_open_filedir = new QPushButton(MY_File_watch_TestClass);
        btn_open_filedir->setObjectName(QStringLiteral("btn_open_filedir"));
        btn_open_filedir->setGeometry(QRect(390, 10, 91, 41));
        btn_open_filedir->setFont(font);
        Lined_folder_path = new QLineEdit(MY_File_watch_TestClass);
        Lined_folder_path->setObjectName(QStringLiteral("Lined_folder_path"));
        Lined_folder_path->setEnabled(false);
        Lined_folder_path->setGeometry(QRect(10, 15, 361, 30));

        retranslateUi(MY_File_watch_TestClass);

        QMetaObject::connectSlotsByName(MY_File_watch_TestClass);
    } // setupUi

    void retranslateUi(QWidget *MY_File_watch_TestClass)
    {
        MY_File_watch_TestClass->setWindowTitle(QApplication::translate("MY_File_watch_TestClass", "MY_File_watch_Test", nullptr));
        btn_monitor->setText(QApplication::translate("MY_File_watch_TestClass", "\345\274\200\345\220\257\347\233\221\346\216\247", nullptr));
        btn_insert->setText(QApplication::translate("MY_File_watch_TestClass", "\346\217\222\345\205\245", nullptr));
        btn_find->setText(QApplication::translate("MY_File_watch_TestClass", "\346\237\245\346\211\276", nullptr));
        btn_update->setText(QApplication::translate("MY_File_watch_TestClass", "\346\233\264\346\226\260", nullptr));
        btn_delete->setText(QApplication::translate("MY_File_watch_TestClass", "\345\210\240\351\231\244", nullptr));
        btn_open_filedir->setText(QApplication::translate("MY_File_watch_TestClass", "\346\211\223\345\274\200\347\233\221\346\216\247\347\233\256\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MY_File_watch_TestClass: public Ui_MY_File_watch_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_FILE_WATCH_TEST_H
