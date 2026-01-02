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

    label_Address = new QLabel(this);
    label_Address->setText(u8"目标IP地址");

    verticalLayout->addWidget(label_Address);

    lineEdit_Address = new QLineEdit(this);

    verticalLayout->addWidget(lineEdit_Address);

    label_Port = new QLabel(this);
    label_Port->setText(u8"目标端口");

    verticalLayout->addWidget(label_Port);

    spinBox_Port = new QSpinBox(this);
    spinBox_Port->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    spinBox_Port->setMaximum(65535);

    verticalLayout->addWidget(spinBox_Port);
}

uint16_t TargetBox::getPortValue(void)
{
    return this->spinBox_Port->value();
}

QString TargetBox::getAddress(void)
{
    return this->lineEdit_Address->text();
}
