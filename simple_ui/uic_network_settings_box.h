/********************************************************************************
** Form generated from reading UI file 'network_settings_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIC_NETWORK_SETTINGS_BOX_H
#define UIC_NETWORK_SETTINGS_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "auto_width_combobox.h"
#include "led_widget.h"
#include "scrollable_list_widget.h"
#include "toggle_button.h"

QT_BEGIN_NAMESPACE

class Ui_NetworkSettingsBox
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_WorkMode;
    AutoWidthCombobox *comboBox_WorkMode;
    QLabel *label_LocalAddress;
    AutoWidthCombobox *comboBox_LocalAddress;
    QLabel *label_LocalPort;
    QSpinBox *spinBox_LocalPort;
    QLabel *label_TargetAddress;
    QLineEdit *lineEdit_TargetAddress;
    QLabel *label_TargetPort;
    QSpinBox *spinBox_TargetPort;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    LED_Widget *led;
    QPushButton *button_Refersh;
    ToggleButton *button_Switch;
    ScrollableListWidget *widget_2;

    void setupUi(QWidget* NetworkSettingsBox)
    {
        NetworkSettingsBox->resize(190, 309);
        NetworkSettingsBox->setMinimumSize(QSize(128, 128));
        QFont font;
        font.setPointSize(10);
        NetworkSettingsBox->setFont(font);
        verticalLayout = new QVBoxLayout(NetworkSettingsBox);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        label_WorkMode = new QLabel(NetworkSettingsBox);
        label_WorkMode->setFont(font);

        verticalLayout->addWidget(label_WorkMode);

        comboBox_WorkMode = new AutoWidthCombobox(NetworkSettingsBox);
        comboBox_WorkMode->setFont(font);

        verticalLayout->addWidget(comboBox_WorkMode);

        label_LocalAddress = new QLabel(NetworkSettingsBox);
        label_LocalAddress->setFont(font);

        verticalLayout->addWidget(label_LocalAddress);

        comboBox_LocalAddress = new AutoWidthCombobox(NetworkSettingsBox);

        verticalLayout->addWidget(comboBox_LocalAddress);

        label_LocalPort = new QLabel(NetworkSettingsBox);
        label_LocalPort->setFont(font);

        verticalLayout->addWidget(label_LocalPort);

        spinBox_LocalPort = new QSpinBox(NetworkSettingsBox);
        spinBox_LocalPort->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        spinBox_LocalPort->setMaximum(65535);
        spinBox_LocalPort->setValue(8080);

        verticalLayout->addWidget(spinBox_LocalPort);

        label_TargetAddress = new QLabel(NetworkSettingsBox);
        label_TargetAddress->setFont(font);

        verticalLayout->addWidget(label_TargetAddress);

        lineEdit_TargetAddress = new QLineEdit(NetworkSettingsBox);
        lineEdit_TargetAddress->setFont(font);

        verticalLayout->addWidget(lineEdit_TargetAddress);

        label_TargetPort = new QLabel(NetworkSettingsBox);
        label_TargetPort->setFont(font);

        verticalLayout->addWidget(label_TargetPort);

        spinBox_TargetPort = new QSpinBox(NetworkSettingsBox);
        spinBox_TargetPort->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        spinBox_TargetPort->setMaximum(65535);
        spinBox_TargetPort->setValue(8080);

        verticalLayout->addWidget(spinBox_TargetPort);

        widget = new QWidget(NetworkSettingsBox);
        widget->setMinimumSize(QSize(0, 32));
        widget->setMaximumSize(QSize(16777215, 48));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        led = new LED_Widget(widget);
        led->setMinimumSize(QSize(24, 24));
        led->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(led);

        button_Refersh = new QPushButton(widget);
        button_Refersh->setMinimumSize(QSize(32, 0));
        button_Refersh->setFont(font);

        horizontalLayout->addWidget(button_Refersh);

        button_Switch = new ToggleButton(widget);
        button_Switch->setMinimumSize(QSize(32, 0));
        button_Switch->setFont(font);

        horizontalLayout->addWidget(button_Switch);


        verticalLayout->addWidget(widget);

        clientListWidget = new ScrollableListWidget(NetworkSettingsBox);
        clientListWidget->setMinimumSize(QSize(64, 32));

        verticalLayout->addWidget(clientListWidget);


        label_WorkMode->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        label_LocalAddress->setText(QCoreApplication::translate("NetworkSettingsBox", "\346\234\254\345\234\260\345\234\260\345\235\200", nullptr));
        label_LocalPort->setText(QCoreApplication::translate("NetworkSettingsBox", "\346\234\254\345\234\260\347\253\257\345\217\243", nullptr));
        label_TargetAddress->setText(QCoreApplication::translate("NetworkSettingsBox", "\347\233\256\346\240\207\345\234\260\345\235\200", nullptr));
        label_TargetPort->setText(QCoreApplication::translate("NetworkSettingsBox", "\347\233\256\346\240\207\347\253\257\345\217\243", nullptr));
        button_Refersh->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\210\267\346\226\260", nullptr));
        button_Switch->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\220\257\345\212\250", nullptr));
    }

};

namespace Ui {
    class NetworkSettingsBox: public Ui_NetworkSettingsBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIC_NETWORK_SETTINGS_BOX_H
