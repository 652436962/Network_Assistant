#include "target_box.h"

TargetBox::TargetBox(QWidget* parent):QGroupBox(parent)
{
    this->setupUi();
    this->setTitle(u8"UDP 发送目标");
}

void TargetBox::setupUi(void)
{
    this->resize(196, 128);
    this->setMinimumSize(QSize(196, 128));
    QFont font;
    font.setPointSize(10);
    this->setFont(font);
    verticalLayout = new QVBoxLayout(this);

    label_LocalAddress = new QLabel(this);
    label_LocalAddress->setText(u8"目标IP地址");

    verticalLayout->addWidget(label_LocalAddress);

    lineEdit_TargetAddress = new QLineEdit(this);

    verticalLayout->addWidget(lineEdit_TargetAddress);

    label_LocalPort = new QLabel(this);
    label_LocalPort->setText(u8"目标端口");

    verticalLayout->addWidget(label_LocalPort);

    spinBox_LocalPort = new QSpinBox(this);
    spinBox_LocalPort->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    spinBox_LocalPort->setMaximum(65535);

    verticalLayout->addWidget(spinBox_LocalPort);
}

uint16_t TargetBox::getPortValue(void)
{
    return this->spinBox_LocalPort->value();
}

QString TargetBox::getTargetAddress(void)
{
    return this->lineEdit_TargetAddress->text();
}
