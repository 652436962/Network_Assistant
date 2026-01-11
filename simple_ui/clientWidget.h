/********************************************************************************
** Form generated from reading UI file 'clientWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CLIENTWIDGETH_H
#define CLIENTWIDGETH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_Port;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(346, 32);
        Form->setMinimumSize(QSize(0, 32));
        Form->setMaximumSize(QSize(16777215, 48));
        QFont font;
        font.setPointSize(10);
        Form->setFont(font);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_IP = new QLineEdit(Form);
        lineEdit_IP->setObjectName("lineEdit_IP");

        horizontalLayout->addWidget(lineEdit_IP);

        lineEdit_Port = new QLineEdit(Form);
        lineEdit_Port->setObjectName("lineEdit_Port");

        horizontalLayout->addWidget(lineEdit_Port);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(32, 32));
        pushButton->setMaximumSize(QSize(48, 48));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CLIENTWIDGETH_H
