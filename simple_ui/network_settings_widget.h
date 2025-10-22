/********************************************************************************
** Form generated from reading UI file 'network_settings_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef NETWORK_SETTINGS_WIDGET_H
#define NETWORK_SETTINGS_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "led_widget.h"

QT_BEGIN_NAMESPACE

class Ui_NetworkSettingsWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_ProtocolType;
    QLabel *label_Address;
    QLineEdit *lineEdit_Address;
    QLabel *label_Port;
    QLineEdit *lineEdit_Port;
    QSpacerItem *horizontalSpacer;
    LED_Widget *led;
    QPushButton *pushButton_Start;
    QComboBox *comboBox_ProtocolType;

    void setupUi(QWidget *NetworkSettingsWidget)
    {
        if (NetworkSettingsWidget->objectName().isEmpty())
            NetworkSettingsWidget->setObjectName("NetworkSettingsWidget");
        NetworkSettingsWidget->resize(175, 200);
        NetworkSettingsWidget->setMinimumSize(QSize(175, 200));
        NetworkSettingsWidget->setMaximumSize(QSize(16777215, 200));
        QFont font;
        font.setPointSize(10);
        NetworkSettingsWidget->setFont(font);
        gridLayout = new QGridLayout(NetworkSettingsWidget);
        gridLayout->setSpacing(4);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(4, 4, 4, 4);
        label_ProtocolType = new QLabel(NetworkSettingsWidget);
        label_ProtocolType->setObjectName("label_ProtocolType");
        label_ProtocolType->setFont(font);

        gridLayout->addWidget(label_ProtocolType, 0, 0, 1, 2);

        label_Address = new QLabel(NetworkSettingsWidget);
        label_Address->setObjectName("label_Address");
        label_Address->setFont(font);

        gridLayout->addWidget(label_Address, 2, 0, 1, 1);

        lineEdit_Address = new QLineEdit(NetworkSettingsWidget);
        lineEdit_Address->setObjectName("lineEdit_Address");
        lineEdit_Address->setFont(font);

        gridLayout->addWidget(lineEdit_Address, 3, 0, 1, 3);

        label_Port = new QLabel(NetworkSettingsWidget);
        label_Port->setObjectName("label_Port");
        label_Port->setFont(font);

        gridLayout->addWidget(label_Port, 4, 0, 1, 1);

        lineEdit_Port = new QLineEdit(NetworkSettingsWidget);
        lineEdit_Port->setObjectName("lineEdit_Port");
        lineEdit_Port->setFont(font);

        gridLayout->addWidget(lineEdit_Port, 5, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(57, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 0, 1, 1);

        led = new LED_Widget(NetworkSettingsWidget);
        led->setObjectName("led");
        led->setMinimumSize(QSize(24, 24));
        led->setMaximumSize(QSize(24, 24));

        gridLayout->addWidget(led, 6, 1, 1, 1);

        pushButton_Start = new QPushButton(NetworkSettingsWidget);
        pushButton_Start->setObjectName("pushButton_Start");
        pushButton_Start->setFont(font);

        gridLayout->addWidget(pushButton_Start, 6, 2, 1, 1);

        comboBox_ProtocolType = new QComboBox(NetworkSettingsWidget);
        comboBox_ProtocolType->setObjectName("comboBox_ProtocolType");
        comboBox_ProtocolType->setFont(font);

        gridLayout->addWidget(comboBox_ProtocolType, 1, 0, 1, 3);


        retranslateUi(NetworkSettingsWidget);

        QMetaObject::connectSlotsByName(NetworkSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *NetworkSettingsWidget)
    {
        NetworkSettingsWidget->setWindowTitle(QCoreApplication::translate("NetworkSettingsWidget", "Form", nullptr));
        label_ProtocolType->setText(QCoreApplication::translate("NetworkSettingsWidget", "\345\215\217\350\256\256\347\261\273\345\236\213", nullptr));
        label_Address->setText(QCoreApplication::translate("NetworkSettingsWidget", "\345\234\260\345\235\200", nullptr));
        label_Port->setText(QCoreApplication::translate("NetworkSettingsWidget", "\347\253\257\345\217\243", nullptr));
        pushButton_Start->setText(QCoreApplication::translate("NetworkSettingsWidget", "\345\220\257\345\212\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkSettingsWidget: public Ui_NetworkSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NETWORK_SETTINGS_WIDGET_H
