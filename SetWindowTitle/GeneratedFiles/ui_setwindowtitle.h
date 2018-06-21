/********************************************************************************
** Form generated from reading UI file 'setwindowtitle.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETWINDOWTITLE_H
#define UI_SETWINDOWTITLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetWindowTitleClass
{
public:
    QWidget *centralWidget;
    QPushButton *RunButton;
    QLineEdit *OriginEdit;
    QLineEdit *TargetEdit;
    QListView *OriginlistView;
    QFrame *line;
    QPushButton *FindButton;
    QPushButton *HoldButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SetWindowTitleClass)
    {
        if (SetWindowTitleClass->objectName().isEmpty())
            SetWindowTitleClass->setObjectName(QStringLiteral("SetWindowTitleClass"));
        SetWindowTitleClass->resize(600, 400);
        centralWidget = new QWidget(SetWindowTitleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        RunButton = new QPushButton(centralWidget);
        RunButton->setObjectName(QStringLiteral("RunButton"));
        RunButton->setGeometry(QRect(370, 300, 75, 23));
        OriginEdit = new QLineEdit(centralWidget);
        OriginEdit->setObjectName(QStringLiteral("OriginEdit"));
        OriginEdit->setGeometry(QRect(60, 10, 241, 20));
        TargetEdit = new QLineEdit(centralWidget);
        TargetEdit->setObjectName(QStringLiteral("TargetEdit"));
        TargetEdit->setGeometry(QRect(70, 300, 241, 20));
        OriginlistView = new QListView(centralWidget);
        OriginlistView->setObjectName(QStringLiteral("OriginlistView"));
        OriginlistView->setGeometry(QRect(60, 40, 471, 192));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 260, 571, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        FindButton = new QPushButton(centralWidget);
        FindButton->setObjectName(QStringLiteral("FindButton"));
        FindButton->setGeometry(QRect(370, 10, 75, 23));
        HoldButton = new QPushButton(centralWidget);
        HoldButton->setObjectName(QStringLiteral("HoldButton"));
        HoldButton->setGeometry(QRect(470, 300, 75, 23));
        SetWindowTitleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SetWindowTitleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        SetWindowTitleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SetWindowTitleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SetWindowTitleClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SetWindowTitleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SetWindowTitleClass->setStatusBar(statusBar);

        retranslateUi(SetWindowTitleClass);
        QObject::connect(RunButton, SIGNAL(clicked(bool)), SetWindowTitleClass, SLOT(OnRunButtonClicked(bool)));

        QMetaObject::connectSlotsByName(SetWindowTitleClass);
    } // setupUi

    void retranslateUi(QMainWindow *SetWindowTitleClass)
    {
        SetWindowTitleClass->setWindowTitle(QApplication::translate("SetWindowTitleClass", "SetWindowTitle", 0));
        RunButton->setText(QApplication::translate("SetWindowTitleClass", "RunButton", 0));
        FindButton->setText(QApplication::translate("SetWindowTitleClass", "FindButton", 0));
        HoldButton->setText(QApplication::translate("SetWindowTitleClass", "HoldName", 0));
    } // retranslateUi

};

namespace Ui {
    class SetWindowTitleClass: public Ui_SetWindowTitleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETWINDOWTITLE_H
