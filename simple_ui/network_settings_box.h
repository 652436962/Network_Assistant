/********************************************************************************
** Form generated from reading UI file 'network_settings_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef NETWORK_SETTINGS_BOX_H
#define NETWORK_SETTINGS_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "led_widget.h"

QT_BEGIN_NAMESPACE

class Ui_NetworkSettingsBox
{
public:
    QGridLayout *gridLayout;
    QLabel *label_ProtocolType;
    QComboBox *comboBox_ProtocolType;
    QLabel *label_Address;
    QLineEdit *lineEdit_Address;
    QLabel *label_Port;
    QSpinBox *spinBox_Port;
    LED_Widget *led;
    QPushButton *pushButton_Other;
    QPushButton *pushButton_Switch;

    void setupUi(QWidget *NetworkSettingsBox)
    {
        if (NetworkSettingsBox->objectName().isEmpty())
            NetworkSettingsBox->setObjectName("NetworkSettingsBox");
        NetworkSettingsBox->resize(175, 180);
        NetworkSettingsBox->setMinimumSize(QSize(175, 180));
        QFont font;
        font.setPointSize(10);
        NetworkSettingsBox->setFont(font);
        gridLayout = new QGridLayout(NetworkSettingsBox);
        gridLayout->setObjectName("gridLayout");
        label_ProtocolType = new QLabel(NetworkSettingsBox);
        label_ProtocolType->setObjectName("label_ProtocolType");
        label_ProtocolType->setFont(font);

        gridLayout->addWidget(label_ProtocolType, 0, 0, 1, 2);

        comboBox_ProtocolType = new QComboBox(NetworkSettingsBox);
        comboBox_ProtocolType->setObjectName("comboBox_ProtocolType");
        comboBox_ProtocolType->setFont(font);

        gridLayout->addWidget(comboBox_ProtocolType, 1, 0, 1, 3);

        label_Address = new QLabel(NetworkSettingsBox);
        label_Address->setObjectName("label_Address");
        label_Address->setFont(font);

        gridLayout->addWidget(label_Address, 2, 0, 1, 1);

        lineEdit_Address = new QLineEdit(NetworkSettingsBox);
        lineEdit_Address->setObjectName("lineEdit_Address");
        lineEdit_Address->setFont(font);

        gridLayout->addWidget(lineEdit_Address, 3, 0, 1, 3);

        label_Port = new QLabel(NetworkSettingsBox);
        label_Port->setObjectName("label_Port");
        label_Port->setFont(font);

        gridLayout->addWidget(label_Port, 4, 0, 1, 1);

        spinBox_Port = new QSpinBox(NetworkSettingsBox);
        spinBox_Port->setObjectName("spinBox_Port");
        spinBox_Port->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        gridLayout->addWidget(spinBox_Port, 5, 0, 1, 3);

        led = new LED_Widget(NetworkSettingsBox);
        led->setObjectName("led");
        led->setMinimumSize(QSize(24, 24));
        led->setMaximumSize(QSize(24, 24));

        gridLayout->addWidget(led, 6, 0, 1, 1);

        pushButton_Other = new QPushButton(NetworkSettingsBox);
        pushButton_Other->setObjectName("pushButton_Other");
        pushButton_Other->setMinimumSize(QSize(40, 0));
        pushButton_Other->setFont(font);

        gridLayout->addWidget(pushButton_Other, 6, 1, 1, 1);

        pushButton_Switch = new QPushButton(NetworkSettingsBox);
        pushButton_Switch->setObjectName("pushButton_Switch");
        pushButton_Switch->setMinimumSize(QSize(80, 0));
        pushButton_Switch->setFont(font);

        gridLayout->addWidget(pushButton_Switch, 6, 2, 1, 1);


        retranslateUi(NetworkSettingsBox);

        QMetaObject::connectSlotsByName(NetworkSettingsBox);
    } // setupUi

    void retranslateUi(QWidget *NetworkSettingsBox)
    {
        NetworkSettingsBox->setWindowTitle(QCoreApplication::translate("NetworkSettingsBox", "Form", nullptr));
        label_ProtocolType->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\215\217\350\256\256\347\261\273\345\236\213", nullptr));
        label_Address->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\234\260\345\235\200", nullptr));
        label_Port->setText(QCoreApplication::translate("NetworkSettingsBox", "\347\253\257\345\217\243", nullptr));
        pushButton_Other->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\205\266\345\256\203", nullptr));
        pushButton_Switch->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\220\257\345\212\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkSettingsBox: public Ui_NetworkSettingsBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NETWORK_SETTINGS_BOX_H
