/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QListWidget *randList;
    QGroupBox *groupBox_2;
    QListWidget *bubbleList;
    QGroupBox *groupBox_3;
    QListWidget *quickList;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(642, 409);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        randList = new QListWidget(groupBox);
        randList->setObjectName(QStringLiteral("randList"));
        randList->setGeometry(QRect(10, 30, 181, 321));

        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        bubbleList = new QListWidget(groupBox_2);
        bubbleList->setObjectName(QStringLiteral("bubbleList"));
        bubbleList->setGeometry(QRect(10, 30, 181, 331));

        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        quickList = new QListWidget(groupBox_3);
        quickList->setObjectName(QStringLiteral("quickList"));
        quickList->setGeometry(QRect(10, 30, 181, 321));

        horizontalLayout->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Widget", "GroupBox", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Widget", "GroupBox", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Widget", "GroupBox", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
