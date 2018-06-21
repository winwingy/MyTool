/********************************************************************************
** Form generated from reading UI file 'dailyrem.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DAILYREM_H
#define UI_DAILYREM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DailyRemClass
{
public:
    QAction *action_open;
    QAction *action_save;
    QAction *action_confusion;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QPlainTextEdit *plainTextEdit;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *DailyRemClass)
    {
        if (DailyRemClass->objectName().isEmpty())
            DailyRemClass->setObjectName(QStringLiteral("DailyRemClass"));
        DailyRemClass->resize(600, 400);
        action_open = new QAction(DailyRemClass);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_save = new QAction(DailyRemClass);
        action_save->setObjectName(QStringLiteral("action_save"));
        action_confusion = new QAction(DailyRemClass);
        action_confusion->setObjectName(QStringLiteral("action_confusion"));
        centralWidget = new QWidget(DailyRemClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 0, 1, 1, 1);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);

        DailyRemClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DailyRemClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DailyRemClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(DailyRemClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        DailyRemClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action_open);
        menu->addAction(action_save);
        menu_2->addAction(action_confusion);

        retranslateUi(DailyRemClass);

        QMetaObject::connectSlotsByName(DailyRemClass);
    } // setupUi

    void retranslateUi(QMainWindow *DailyRemClass)
    {
        DailyRemClass->setWindowTitle(QApplication::translate("DailyRemClass", "DailyRem", 0));
        action_open->setText(QApplication::translate("DailyRemClass", "\346\211\223\345\274\200", 0));
        action_save->setText(QApplication::translate("DailyRemClass", "\344\277\235\345\255\230", 0));
        action_confusion->setText(QApplication::translate("DailyRemClass", "\346\267\267\346\226\207", 0));
        menu->setTitle(QApplication::translate("DailyRemClass", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("DailyRemClass", "\347\274\226\350\276\221", 0));
    } // retranslateUi

};

namespace Ui {
    class DailyRemClass: public Ui_DailyRemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DAILYREM_H
