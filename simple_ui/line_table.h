/********************************************************************************
** Form generated from reading UI file 'line_table.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LINE_TABLE_H
#define LINE_TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_Scroll;
    QWidget *widget_Labels;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_Comment;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_Instruction;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_Send;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_Buttons;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Remove;

    void setupUi(QWidget *Form)
    {
        Form->resize(524, 339);
        QFont font;
        font.setPointSize(10);
        Form->setFont(font);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(Form);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 522, 337));
        verticalLayout_Scroll = new QVBoxLayout(scrollAreaWidgetContents);

        // 标签 widget
        widget_Labels = new QWidget(scrollAreaWidgetContents);
        widget_Labels->setMaximumSize(QSize(512, 48));
        horizontalLayout_2 = new QHBoxLayout(widget_Labels);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        horizontalLayout_2->addItem(horizontalSpacer_2);
        label_Comment = new QLabel(widget_Labels);
        QFont font1;
        font1.setPointSize(12);
        label_Comment->setFont(font1);
        horizontalLayout_2->addWidget(label_Comment);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        horizontalLayout_2->addItem(horizontalSpacer_3);
        label_Instruction = new QLabel(widget_Labels);
        label_Instruction->setFont(font1);
        horizontalLayout_2->addWidget(label_Instruction);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        horizontalLayout_2->addItem(horizontalSpacer_4);
        label_Send = new QLabel(widget_Labels);
        label_Send->setObjectName("label_Send");
        label_Send->setFont(font1);
        horizontalLayout_2->addWidget(label_Send);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        horizontalLayout_2->addItem(horizontalSpacer_5);

        verticalLayout_Scroll->addWidget(widget_Labels);

        // 按钮 widget
        widget_Buttons = new QWidget(scrollAreaWidgetContents);
        widget_Buttons->setMinimumSize(QSize(256, 32));
        widget_Buttons->setMaximumSize(QSize(512, 48));
        horizontalLayout = new QHBoxLayout(widget_Buttons);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(339, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        pushButton_Add = new QPushButton(widget_Buttons);
        horizontalLayout->addWidget(pushButton_Add);
        pushButton_Remove = new QPushButton(widget_Buttons);
        horizontalLayout->addWidget(pushButton_Remove);

        verticalLayout_Scroll->addWidget(widget_Buttons);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_Comment->setText(QCoreApplication::translate("Form", "\345\244\207\346\263\250", nullptr));
        label_Instruction->setText(QCoreApplication::translate("Form", "\346\214\207\344\273\244", nullptr));
        label_Send->setText(QCoreApplication::translate("Form", "\345\217\221\351\200\201", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("Form", "\346\267\273\345\212\240\344\270\200\350\241\214", nullptr));
        pushButton_Remove->setText(QCoreApplication::translate("Form", "\345\210\240\351\231\244\344\270\200\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LINE_TABLE_H
