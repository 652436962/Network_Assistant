#include "receive_settings_box.h"

#include <QPainter>

ReceiveSettingsBox::ReceiveSettingsBox(QWidget *parent)
    : QGroupBox(parent)
{
    this->setupUi();

    
    connect(this->radioButton_Text, &QRadioButton::toggled, [this](bool checked) {
        emit this->setText(checked); });
    connect(this->checkBox_StopDisplay, &QCheckBox::toggled, [this](bool checked) {
        emit this->setStopDispalying(checked); });
    connect(this->checkBox_Timestamp, &QCheckBox::toggled, [this](bool checked) {
        emit this->setTimestamp(checked); });
    connect(this->pushButton_Clear, &QPushButton::clicked, [this]() {
        emit this->receiveAreaClear(); });
    connect(this->pushButton_Save, &QPushButton::clicked, [this]() {
        emit this->receiveToFile();
        });
    
}

void ReceiveSettingsBox::setupUi(void)
{
	this->resize(175, 125);
    this->setMinimumSize(QSize(175, 125));
    QFont font;
    font.setPointSize(10);
    this->setFont(font);
    this->setStyleSheet(QString::fromUtf8(""));
    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(8, 8, 8, 8);
    radioButton_Text = new QRadioButton("文本",this);
    radioButton_Text->setFont(font);
    radioButton_Text->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    radioButton_Text->setChecked(true);

    gridLayout->addWidget(radioButton_Text, 0, 0, 1, 1);

    radioButton_HEX = new QRadioButton("HEX",this);
    radioButton_HEX->setFont(font);
    radioButton_HEX->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    gridLayout->addWidget(radioButton_HEX, 0, 1, 1, 1);

    checkBox_StopDisplay = new QCheckBox("停止显示",this);
    checkBox_StopDisplay->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    gridLayout->addWidget(checkBox_StopDisplay, 1, 0, 1, 1);

    checkBox_Timestamp = new QCheckBox("时间戳",this);
    checkBox_Timestamp->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    gridLayout->addWidget(checkBox_Timestamp, 1, 1, 1, 1);

    pushButton_Clear = new QPushButton("清空接收区",this);
    pushButton_Clear->setFont(font);

    gridLayout->addWidget(pushButton_Clear, 2, 0, 1, 1);

    pushButton_Save = new QPushButton("保存到文件",this);
    pushButton_Save->setFont(font);

    gridLayout->addWidget(pushButton_Save, 2, 1, 1, 1);
}

