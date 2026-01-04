/********************************************************************************
** Form generated from reading UI file 'title_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TILTE_WIDGET_H
#define TILTE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_Comment;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_Instruction;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_Send;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(275, 32);
        Form->setMinimumSize(QSize(128, 32));
        Form->setMaximumSize(QSize(512, 64));
        QFont font;
        font.setPointSize(12);
        Form->setFont(font);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_Comment = new QLabel(Form);
        label_Comment->setObjectName("label_Comment");

        horizontalLayout->addWidget(label_Comment);

        horizontalSpacer_2 = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_Instruction = new QLabel(Form);
        label_Instruction->setObjectName("label_Instruction");

        horizontalLayout->addWidget(label_Instruction);

        horizontalSpacer_3 = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_Send = new QLabel(Form);
        label_Send->setObjectName("label_Send");

        horizontalLayout->addWidget(label_Send);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_Comment->setText(QCoreApplication::translate("Form", "\345\244\207\346\263\250", nullptr));
        label_Instruction->setText(QCoreApplication::translate("Form", "\346\214\207\344\273\244", nullptr));
        label_Send->setText(QCoreApplication::translate("Form", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TILTE_WIDGET_H
