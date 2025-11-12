/********************************************************************************
** Form generated from reading UI file 'target_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIC_TARGET_BOX_H
#define UIC_TARGET_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_Address;
    QLineEdit *lineEdit_Address;
    QLabel *label_Port;
    QSpinBox *spinBox_Port;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(180, 128);
        Form->setMinimumSize(QSize(180, 128));
        QFont font;
        font.setPointSize(10);
        Form->setFont(font);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName("verticalLayout");
        label_Address = new QLabel(Form);
        label_Address->setObjectName("label_Address");

        verticalLayout->addWidget(label_Address);

        lineEdit_Address = new QLineEdit(Form);
        lineEdit_Address->setObjectName("lineEdit_Address");

        verticalLayout->addWidget(lineEdit_Address);

        label_Port = new QLabel(Form);
        label_Port->setObjectName("label_Port");

        verticalLayout->addWidget(label_Port);

        spinBox_Port = new QSpinBox(Form);
        spinBox_Port->setObjectName("spinBox_Port");
        spinBox_Port->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        spinBox_Port->setMaximum(65535);

        verticalLayout->addWidget(spinBox_Port);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_Address->setText(QCoreApplication::translate("Form", "\347\233\256\346\240\207\345\234\260\345\235\200", nullptr));
        label_Port->setText(QCoreApplication::translate("Form", "\347\233\256\346\240\207\347\253\257\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIC_TARGET_BOX_H
