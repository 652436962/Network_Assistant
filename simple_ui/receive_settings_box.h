/********************************************************************************
** Form generated from reading UI file 'receive_settings_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RECEIVE_SETTINGS_BOX_H
#define RECEIVE_SETTINGS_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReceiveSettingsBox
{
public:
    QGridLayout *gridLayout;
    QRadioButton *radioButton_Text;
    QRadioButton *radioButton_HEX;
    QCheckBox *checkBox_ReceiveStopDisplay;
    QCheckBox *checkBox_Timestamp;
    QPushButton *pushButton_Clear;
    QPushButton *pushButton_Save;

    void setupUi(QWidget *ReceiveSettingsBox)
    {
        if (ReceiveSettingsBox->objectName().isEmpty())
            ReceiveSettingsBox->setObjectName("ReceiveSettingsBox");
        ReceiveSettingsBox->resize(175, 125);
        ReceiveSettingsBox->setMinimumSize(QSize(175, 125));
        QFont font;
        font.setPointSize(10);
        ReceiveSettingsBox->setFont(font);
        ReceiveSettingsBox->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ReceiveSettingsBox);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(8, 8, 8, 8);
        radioButton_Text = new QRadioButton(ReceiveSettingsBox);
        radioButton_Text->setObjectName("radioButton_Text");
        radioButton_Text->setFont(font);
        radioButton_Text->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(radioButton_Text, 0, 0, 1, 1);

        radioButton_HEX = new QRadioButton(ReceiveSettingsBox);
        radioButton_HEX->setObjectName("radioButton_HEX");
        radioButton_HEX->setFont(font);
        radioButton_HEX->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(radioButton_HEX, 0, 1, 1, 1);

        checkBox_ReceiveStopDisplay = new QCheckBox(ReceiveSettingsBox);
        checkBox_ReceiveStopDisplay->setObjectName("checkBox_ReceiveStopDisplay");
        checkBox_ReceiveStopDisplay->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(checkBox_ReceiveStopDisplay, 1, 0, 1, 1);

        checkBox_Timestamp = new QCheckBox(ReceiveSettingsBox);
        checkBox_Timestamp->setObjectName("checkBox_Timestamp");
        checkBox_Timestamp->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(checkBox_Timestamp, 1, 1, 1, 1);

        pushButton_Clear = new QPushButton(ReceiveSettingsBox);
        pushButton_Clear->setObjectName("pushButton_Clear");
        pushButton_Clear->setFont(font);

        gridLayout->addWidget(pushButton_Clear, 2, 0, 1, 1);

        pushButton_Save = new QPushButton(ReceiveSettingsBox);
        pushButton_Save->setObjectName("pushButton_Save");
        pushButton_Save->setFont(font);

        gridLayout->addWidget(pushButton_Save, 2, 1, 1, 1);


        retranslateUi(ReceiveSettingsBox);

        QMetaObject::connectSlotsByName(ReceiveSettingsBox);
    } // setupUi

    void retranslateUi(QWidget *ReceiveSettingsBox)
    {
        ReceiveSettingsBox->setWindowTitle(QCoreApplication::translate("ReceiveSettingsBox", "Form", nullptr));
        radioButton_Text->setText(QCoreApplication::translate("ReceiveSettingsBox", "\346\226\207\346\234\254", nullptr));
        radioButton_HEX->setText(QCoreApplication::translate("ReceiveSettingsBox", "HEX", nullptr));
        checkBox_ReceiveStopDisplay->setText(QCoreApplication::translate("ReceiveSettingsBox", "\345\201\234\346\255\242\346\230\276\347\244\272", nullptr));
        checkBox_Timestamp->setText(QCoreApplication::translate("ReceiveSettingsBox", "\346\227\266\351\227\264\346\210\263", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("ReceiveSettingsBox", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("ReceiveSettingsBox", "\344\277\235\345\255\230\345\210\260\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReceiveSettingsBox: public Ui_ReceiveSettingsBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RECEIVE_SETTINGS_BOX_H
