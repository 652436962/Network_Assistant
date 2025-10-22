/********************************************************************************
** Form generated from reading UI file 'receive_settings_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIC_RECEIVE_SETTINGS_BOX_H
#define UIC_RECEIVE_SETTINGS_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReceiveSettingsWidget
{
public:
    QGridLayout *gridLayout;
    QComboBox *comboBox_Encoding;
    QCheckBox *checkBox_Timestamp;
    QLabel *label_Encoding;
    QCheckBox *checkBox_ReceiveStopDisplay;
    QRadioButton *radioButton_Text;
    QPushButton *pushButton_Save;
    QRadioButton *radioButton_HEX;
    QPushButton *pushButton_Clear;

    void setupUi(QWidget *ReceiveSettingsWidget)
    {
        if (ReceiveSettingsWidget->objectName().isEmpty())
            ReceiveSettingsWidget->setObjectName("ReceiveSettingsWidget");
        ReceiveSettingsWidget->resize(175, 125);
        ReceiveSettingsWidget->setMinimumSize(QSize(175, 125));
        ReceiveSettingsWidget->setMaximumSize(QSize(16777215, 125));
        QFont font;
        font.setPointSize(10);
        ReceiveSettingsWidget->setFont(font);
        ReceiveSettingsWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ReceiveSettingsWidget);
        gridLayout->setSpacing(4);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(8, 8, 8, 8);
        comboBox_Encoding = new QComboBox(ReceiveSettingsWidget);
        comboBox_Encoding->setObjectName("comboBox_Encoding");
        comboBox_Encoding->setFont(font);

        gridLayout->addWidget(comboBox_Encoding, 2, 1, 1, 1);

        checkBox_Timestamp = new QCheckBox(ReceiveSettingsWidget);
        checkBox_Timestamp->setObjectName("checkBox_Timestamp");
        checkBox_Timestamp->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(checkBox_Timestamp, 1, 1, 1, 1);

        label_Encoding = new QLabel(ReceiveSettingsWidget);
        label_Encoding->setObjectName("label_Encoding");
        label_Encoding->setFont(font);
        label_Encoding->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_Encoding, 2, 0, 1, 1);

        checkBox_ReceiveStopDisplay = new QCheckBox(ReceiveSettingsWidget);
        checkBox_ReceiveStopDisplay->setObjectName("checkBox_ReceiveStopDisplay");
        checkBox_ReceiveStopDisplay->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(checkBox_ReceiveStopDisplay, 1, 0, 1, 1);

        radioButton_Text = new QRadioButton(ReceiveSettingsWidget);
        radioButton_Text->setObjectName("radioButton_Text");
        radioButton_Text->setFont(font);
        radioButton_Text->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(radioButton_Text, 0, 0, 1, 1);

        pushButton_Save = new QPushButton(ReceiveSettingsWidget);
        pushButton_Save->setObjectName("pushButton_Save");
        pushButton_Save->setFont(font);

        gridLayout->addWidget(pushButton_Save, 3, 1, 1, 1);

        radioButton_HEX = new QRadioButton(ReceiveSettingsWidget);
        radioButton_HEX->setObjectName("radioButton_HEX");
        radioButton_HEX->setFont(font);
        radioButton_HEX->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(radioButton_HEX, 0, 1, 1, 1);

        pushButton_Clear = new QPushButton(ReceiveSettingsWidget);
        pushButton_Clear->setObjectName("pushButton_Clear");
        pushButton_Clear->setFont(font);

        gridLayout->addWidget(pushButton_Clear, 3, 0, 1, 1);


        retranslateUi(ReceiveSettingsWidget);

        QMetaObject::connectSlotsByName(ReceiveSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *ReceiveSettingsWidget)
    {
        ReceiveSettingsWidget->setWindowTitle(QCoreApplication::translate("ReceiveSettingsWidget", "Form", nullptr));
        checkBox_Timestamp->setText(QCoreApplication::translate("ReceiveSettingsWidget", "\346\227\266\351\227\264\346\210\263", nullptr));
        label_Encoding->setText(QCoreApplication::translate("ReceiveSettingsWidget", "\347\274\226\347\240\201", nullptr));
        checkBox_ReceiveStopDisplay->setText(QCoreApplication::translate("ReceiveSettingsWidget", "\345\201\234\346\255\242\346\230\276\347\244\272", nullptr));
        radioButton_Text->setText(QCoreApplication::translate("ReceiveSettingsWidget", "\346\226\207\346\234\254", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("ReceiveSettingsWidget", "\344\277\235\345\255\230\345\210\260\346\226\207\344\273\266", nullptr));
        radioButton_HEX->setText(QCoreApplication::translate("ReceiveSettingsWidget", "HEX", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("ReceiveSettingsWidget", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReceiveSettingsWidget: public Ui_ReceiveSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIC_RECEIVE_SETTINGS_BOX_H
