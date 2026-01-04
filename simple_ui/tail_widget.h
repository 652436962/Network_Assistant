/********************************************************************************
** Form generated from reading UI file 'tail_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TAIL_WIDGET_H
#define TAIL_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Remove;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(374, 32);
        Form->setMinimumSize(QSize(128, 32));
        Form->setMaximumSize(QSize(512, 48));
        QFont font;
        font.setPointSize(10);
        Form->setFont(font);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(209, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Add = new QPushButton(Form);
        pushButton_Add->setObjectName("pushButton_Add");

        horizontalLayout->addWidget(pushButton_Add);

        pushButton_Remove = new QPushButton(Form);
        pushButton_Remove->setObjectName("pushButton_Remove");

        horizontalLayout->addWidget(pushButton_Remove);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("Form", "\346\267\273\345\212\240\344\270\200\350\241\214", nullptr));
        pushButton_Remove->setText(QCoreApplication::translate("Form", "\347\247\273\351\231\244\344\270\200\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TAIL_WIDGET_H
