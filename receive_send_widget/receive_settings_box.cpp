#include "receive_settings_box.h"
#include "ui_receive_settings_box.h"

#include <QPainter>

ReceiveSettingsBox::ReceiveSettingsBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ReceiveSettingsBox)
{
    ui->setupUi(this);

    
    connect(ui->radioButton_Text, &QRadioButton::toggled, [this](bool checked) {
        emit this->setText(checked); });
    connect(ui->checkBox_StopDisplay, &QCheckBox::toggled, [this](bool checked) {
        emit this->setStopDispalying(checked); });
    connect(ui->checkBox_Timestamp, &QCheckBox::toggled, [this](bool checked) {
        emit this->setTimestamp(checked); });
    connect(ui->pushButton_Clear, &QPushButton::clicked, [this]() {
        emit this->receiveAreaClear(); });
    connect(ui->pushButton_Save, &QPushButton::clicked, [this]() {
        emit this->receiveToFile();
        });
    
}
