/********************************************************************************
** Form generated from reading UI file 'clientesTitle.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CLIENTESTITLE_H
#define CLIENTESTITLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_00;
    QLabel *label_Title;
    QSpacerItem *horizontalSpacer_01;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_IP;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_Port;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_Disconnect;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(270, 32);
        Form->setMinimumSize(QSize(128, 32));
        Form->setMaximumSize(QSize(16777215, 64));
        QFont font;
        font.setPointSize(10);
        Form->setFont(font);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(Form);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_00 = new QSpacerItem(46, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_00);

        label_Title = new QLabel(widget_2);
        label_Title->setObjectName("label_Title");

        horizontalLayout_2->addWidget(label_Title);

        horizontalSpacer_01 = new QSpacerItem(45, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_01);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(Form);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_10 = new QSpacerItem(62, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        label_IP = new QLabel(widget);
        label_IP->setObjectName("label_IP");

        horizontalLayout->addWidget(label_IP);

        horizontalSpacer_11 = new QSpacerItem(63, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        label_Port = new QLabel(widget);
        label_Port->setObjectName("label_Port");

        horizontalLayout->addWidget(label_Port);

        horizontalSpacer_12 = new QSpacerItem(62, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);

        label_Disconnect = new QLabel(widget);
        label_Disconnect->setObjectName("label_Disconnect");

        horizontalLayout->addWidget(label_Disconnect);


        verticalLayout->addWidget(widget);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_Title->setText(QCoreApplication::translate("Form", "\350\277\236\346\216\245\345\210\260\346\234\254\346\234\215\345\212\241\345\231\250\347\232\204\346\211\200\346\234\211\345\256\242\346\210\267\347\253\257", nullptr));
        label_IP->setText(QCoreApplication::translate("Form", "IP", nullptr));
        label_Port->setText(QCoreApplication::translate("Form", "\347\253\257\345\217\243", nullptr));
        label_Disconnect->setText(QCoreApplication::translate("Form", "\346\226\255\345\274\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CLIENTESTITLE_H
