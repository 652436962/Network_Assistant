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
    if (this->objectName().isEmpty())
        this->setObjectName("ReceiveSettingsBox");
	this->resize(175, 125);
    this->setMinimumSize(QSize(175, 125));
    QFont font;
    font.setPointSize(10);
    this->setFont(font);
    this->setStyleSheet(QString::fromUtf8(""));
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(8, 8, 8, 8);
    radioButton_Text = new QRadioButton(this);
    radioButton_Text->setObjectName("radioButton_Text");
    radioButton_Text->setFont(font);
    radioButton_Text->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    radioButton_Text->setChecked(true);

    gridLayout->addWidget(radioButton_Text, 0, 0, 1, 1);

    radioButton_HEX = new QRadioButton(this);
    radioButton_HEX->setObjectName("radioButton_HEX");
    radioButton_HEX->setFont(font);
    radioButton_HEX->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    gridLayout->addWidget(radioButton_HEX, 0, 1, 1, 1);

    checkBox_StopDisplay = new QCheckBox(this);
    checkBox_StopDisplay->setObjectName("checkBox_ReceiveStopDisplay");
    checkBox_StopDisplay->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    gridLayout->addWidget(checkBox_StopDisplay, 1, 0, 1, 1);

    checkBox_Timestamp = new QCheckBox(this);
    checkBox_Timestamp->setObjectName("checkBox_Timestamp");
    checkBox_Timestamp->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    gridLayout->addWidget(checkBox_Timestamp, 1, 1, 1, 1);

    pushButton_Clear = new QPushButton(this);
    pushButton_Clear->setObjectName("pushButton_Clear");
    pushButton_Clear->setFont(font);

    gridLayout->addWidget(pushButton_Clear, 2, 0, 1, 1);

    pushButton_Save = new QPushButton(this);
    pushButton_Save->setObjectName("pushButton_Save");
    pushButton_Save->setFont(font);

    gridLayout->addWidget(pushButton_Save, 2, 1, 1, 1);


    retranslateUi();

    QMetaObject::connectSlotsByName(this);
} // setupUi

void ReceiveSettingsBox::retranslateUi(void)
{
    this->setWindowTitle(QCoreApplication::translate("ReceiveSettingsBox", "Form", nullptr));
    radioButton_Text->setText(QCoreApplication::translate("ReceiveSettingsBox", "\346\226\207\346\234\254", nullptr));
    radioButton_HEX->setText(QCoreApplication::translate("ReceiveSettingsBox", "HEX", nullptr));
    checkBox_StopDisplay->setText(QCoreApplication::translate("ReceiveSettingsBox", "\345\201\234\346\255\242\346\230\276\347\244\272", nullptr));
    checkBox_Timestamp->setText(QCoreApplication::translate("ReceiveSettingsBox", "\346\227\266\351\227\264\346\210\263", nullptr));
    pushButton_Clear->setText(QCoreApplication::translate("ReceiveSettingsBox", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", nullptr));
    pushButton_Save->setText(QCoreApplication::translate("ReceiveSettingsBox", "\344\277\235\345\255\230\345\210\260\346\226\207\344\273\266", nullptr));
} // retranslateUi

