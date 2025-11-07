/********************************************************************************
** Form generated from reading UI file 'notification_bubble.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef NOTIFICATION_BUBBLE_H
#define NOTIFICATION_BUBBLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bubble
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label_Text;
    QPushButton *pushButton_Close;

    void setupUi(QWidget *bubble)
    {
        if (bubble->objectName().isEmpty())
            bubble->setObjectName("bubble");
        bubble->resize(128, 48);
        bubble->setMinimumSize(QSize(128, 32));
        bubble->setMaximumSize(QSize(256, 64));
        QFont font;
        font.setPointSize(10);
        bubble->setFont(font);
        horizontalLayout = new QHBoxLayout(bubble);
        horizontalLayout->setObjectName("horizontalLayout");
        label_Text = new QLabel(bubble);
        label_Text->setObjectName("label_Text");

        horizontalLayout->addWidget(label_Text);

        pushButton_Close = new QPushButton(bubble);
        pushButton_Close->setObjectName("pushButton_Close");
        pushButton_Close->setMaximumSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton_Close);


        retranslateUi(bubble);
        QObject::connect(pushButton_Close, &QPushButton::clicked, bubble, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(bubble);
    } // setupUi

    void retranslateUi(QWidget *bubble)
    {
        bubble->setWindowTitle(QCoreApplication::translate("bubble", "Form", nullptr));
        label_Text->setText(QCoreApplication::translate("bubble", "TextLabel", nullptr));
        pushButton_Close->setText(QCoreApplication::translate("bubble", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bubble: public Ui_bubble {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NOTIFICATION_BUBBLE_H
