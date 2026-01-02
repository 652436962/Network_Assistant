/********************************************************************************
** Form generated from reading UI file 'ALineWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ALINEWIDGET_H
#define ALINEWIDGET_H

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
    QLineEdit *commentEdit;
    QLineEdit *instructionEdit;
    QPushButton *sendButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(300, 32);
        Form->setMinimumSize(QSize(50, 32));
        Form->setMaximumSize(QSize(300, 100));
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        commentEdit = new QLineEdit(Form);
        commentEdit->setObjectName("commentEdit");

        horizontalLayout->addWidget(commentEdit);

        instructionEdit = new QLineEdit(Form);
        instructionEdit->setObjectName("instructionEdit");

        horizontalLayout->addWidget(instructionEdit);

        sendButton = new QPushButton(Form);
        sendButton->setObjectName("sendButton");
        sendButton->setMinimumSize(QSize(16, 16));
        sendButton->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(sendButton);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        sendButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ALINEWIDGET_H
