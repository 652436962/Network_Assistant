/********************************************************************************
** Form generated from reading UI file 'send_settings_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SEND_SETTINGS_BOX_H
#define SEND_SETTINGS_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SendSettingsBox
{
public:
    QGridLayout *gridLayout;
    QLabel *label_Option;
    QComboBox *comboBox_Option;
    QRadioButton *radioButton_Text;
    QRadioButton *radioButton_HEX;
    QCheckBox *checkBox_Append;
    QComboBox *comboBox_Append;
    QCheckBox *checkBox_AutoSend;
    QSpacerItem *horizontalSpacer;
    QLabel *label_AutoSendCycle;
    QSpinBox *spinBox_AutoSendCycle;
    QLabel *label_MS;

    void setupUi(QGroupBox *SendSettingsBox)
    {
        if (SendSettingsBox->objectName().isEmpty())
            SendSettingsBox->setObjectName("SendSettingsBox");
        SendSettingsBox->resize(200, 180);
        SendSettingsBox->setMinimumSize(QSize(200, 180));
        QFont font;
        font.setPointSize(10);
        SendSettingsBox->setFont(font);
        gridLayout = new QGridLayout(SendSettingsBox);
        gridLayout->setObjectName("gridLayout");
        label_Option = new QLabel(SendSettingsBox);
        label_Option->setObjectName("label_Option");
        label_Option->setMaximumSize(QSize(150, 150));
        label_Option->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_Option, 0, 0, 1, 1);

        comboBox_Option = new QComboBox(SendSettingsBox);
        comboBox_Option->setObjectName("comboBox_Option");
        comboBox_Option->setMaximumSize(QSize(150, 24));

        gridLayout->addWidget(comboBox_Option, 0, 1, 1, 2);

        radioButton_Text = new QRadioButton(SendSettingsBox);
        radioButton_Text->setObjectName("radioButton_Text");
        radioButton_Text->setMaximumSize(QSize(150, 32));
        radioButton_Text->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        radioButton_Text->setChecked(true);

        gridLayout->addWidget(radioButton_Text, 1, 0, 1, 1);

        radioButton_HEX = new QRadioButton(SendSettingsBox);
        radioButton_HEX->setObjectName("radioButton_HEX");
        radioButton_HEX->setMaximumSize(QSize(150, 32));
        radioButton_HEX->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(radioButton_HEX, 1, 1, 1, 2);

        checkBox_Append = new QCheckBox(SendSettingsBox);
        checkBox_Append->setObjectName("checkBox_Append");
        checkBox_Append->setMaximumSize(QSize(150, 32));
        checkBox_Append->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBox_Append->setChecked(true);

        gridLayout->addWidget(checkBox_Append, 2, 0, 1, 1);

        comboBox_Append = new QComboBox(SendSettingsBox);
        comboBox_Append->addItem(QString());
        comboBox_Append->addItem(QString());
        comboBox_Append->addItem(QString());
        comboBox_Append->setObjectName("comboBox_Append");
        comboBox_Append->setMaximumSize(QSize(150, 24));

        gridLayout->addWidget(comboBox_Append, 2, 1, 1, 2);

        checkBox_AutoSend = new QCheckBox(SendSettingsBox);
        checkBox_AutoSend->setObjectName("checkBox_AutoSend");
        checkBox_AutoSend->setEnabled(true);
        checkBox_AutoSend->setMaximumSize(QSize(150, 32));
        checkBox_AutoSend->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(checkBox_AutoSend, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 1, 1, 2);

        label_AutoSendCycle = new QLabel(SendSettingsBox);
        label_AutoSendCycle->setObjectName("label_AutoSendCycle");
        label_AutoSendCycle->setEnabled(true);
        label_AutoSendCycle->setMaximumSize(QSize(16777215, 32));

        gridLayout->addWidget(label_AutoSendCycle, 4, 0, 1, 1);

        spinBox_AutoSendCycle = new QSpinBox(SendSettingsBox);
        spinBox_AutoSendCycle->setObjectName("spinBox_AutoSendCycle");
        spinBox_AutoSendCycle->setEnabled(true);
        spinBox_AutoSendCycle->setMaximumSize(QSize(16777215, 24));
        spinBox_AutoSendCycle->setMaximum(99999);
        spinBox_AutoSendCycle->setValue(500);

        gridLayout->addWidget(spinBox_AutoSendCycle, 4, 1, 1, 1);

        label_MS = new QLabel(SendSettingsBox);
        label_MS->setObjectName("label_MS");
        label_MS->setEnabled(true);
        label_MS->setMaximumSize(QSize(16777215, 32));

        gridLayout->addWidget(label_MS, 4, 2, 1, 1);


        retranslateUi(SendSettingsBox);

        QMetaObject::connectSlotsByName(SendSettingsBox);
    } // setupUi

    void retranslateUi(QGroupBox *SendSettingsBox)
    {
        SendSettingsBox->setWindowTitle(QCoreApplication::translate("SendSettingsBox", "Form", nullptr));
        label_Option->setText(QCoreApplication::translate("SendSettingsBox", "\345\217\221\351\200\201\351\200\211\351\241\271", nullptr));
        radioButton_Text->setText(QCoreApplication::translate("SendSettingsBox", "\345\217\221\351\200\201\346\226\207\346\234\254", nullptr));
        radioButton_HEX->setText(QCoreApplication::translate("SendSettingsBox", "\345\217\221\351\200\201HEX", nullptr));
        checkBox_Append->setText(QCoreApplication::translate("SendSettingsBox", "\350\207\252\345\212\250\350\277\275\345\212\240", nullptr));
        comboBox_Append->setItemText(0, QCoreApplication::translate("SendSettingsBox", "\346\215\242\350\241\214 \"\\r\\n\"", nullptr));
        comboBox_Append->setItemText(1, QCoreApplication::translate("SendSettingsBox", "\346\215\242\350\241\214 \"\\n\"", nullptr));
        comboBox_Append->setItemText(2, QCoreApplication::translate("SendSettingsBox", "\347\251\272\345\255\227\347\254\246 \"\\0\"", nullptr));

        checkBox_AutoSend->setText(QCoreApplication::translate("SendSettingsBox", "\350\207\252\345\212\250\345\217\221\351\200\201", nullptr));
        label_AutoSendCycle->setText(QCoreApplication::translate("SendSettingsBox", "\350\207\252\345\212\250\345\217\221\351\200\201\345\221\250\346\234\237", nullptr));
        label_MS->setText(QCoreApplication::translate("SendSettingsBox", "ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendSettingsBox: public Ui_SendSettingsBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SEND_SETTINGS_BOX_H
