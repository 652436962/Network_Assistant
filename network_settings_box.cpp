#include "network_settings_box.h"

#include <QPainter>

NetworkSettingsBox::NetworkSettingsBox(QWidget *parent)
    : QGroupBox(parent)
{
    
    this->setupUi();
    
}

void NetworkSettingsBox::setupUi(void)
{
    if (this->objectName().isEmpty())
        this->setObjectName("NetworkSettingsBox");
    this->resize(175, 180);
    this->setMinimumSize(QSize(175, 180));
    QFont font;
    font.setPointSize(10);
    this->setFont(font);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(8, 8, 8, 8);
    label_ProtocolType = new QLabel(this);
    label_ProtocolType->setObjectName("label_ProtocolType");
    label_ProtocolType->setFont(font);

    gridLayout->addWidget(label_ProtocolType, 0, 0, 1, 1);

    label_Address = new QLabel(this);
    label_Address->setObjectName("label_Address");
    label_Address->setFont(font);

    gridLayout->addWidget(label_Address, 2, 0, 1, 1);

    label_Port = new QLabel(this);
    label_Port->setObjectName("label_Port");
    label_Port->setFont(font);

    gridLayout->addWidget(label_Port, 4, 0, 1, 1);

    horizontalSpacer = new QSpacerItem(51, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

    gridLayout->addItem(horizontalSpacer, 6, 0, 1, 1);

    led = new LED_Widget(this);
    led->setObjectName("led");
    led->setMinimumSize(QSize(24, 24));
    led->setMaximumSize(QSize(24, 24));

    gridLayout->addWidget(led, 6, 1, 1, 1);

    pushButton_Other = new QPushButton(this);
    pushButton_Other->setObjectName("pushButton_Other");
    pushButton_Other->setMinimumSize(QSize(40, 0));
    pushButton_Other->setFont(font);

    gridLayout->addWidget(pushButton_Other, 6, 2, 1, 1);

    pushButton_Start = new QPushButton(this);
    pushButton_Start->setObjectName("pushButton_Start");
    pushButton_Start->setMinimumSize(QSize(40, 0));
    pushButton_Start->setFont(font);

    gridLayout->addWidget(pushButton_Start, 6, 3, 1, 1);

    lineEdit_Address = new QLineEdit(this);
    lineEdit_Address->setObjectName("lineEdit_Address");
    lineEdit_Address->setFont(font);

    gridLayout->addWidget(lineEdit_Address, 3, 0, 1, 4);

    spinBox = new QSpinBox(this);
    spinBox->setObjectName("spinBox");
    spinBox->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

    gridLayout->addWidget(spinBox, 5, 0, 1, 4);

    comboBox_ProtocolType = new QComboBox(this);
    comboBox_ProtocolType->setObjectName("comboBox_ProtocolType");
    comboBox_ProtocolType->setFont(font);

    gridLayout->addWidget(comboBox_ProtocolType, 1, 0, 1, 4);


    this->retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void NetworkSettingsBox::retranslateUi(void)
{
    this->setWindowTitle(QCoreApplication::translate("NetworkSettingsBox", "Form", nullptr));
    label_ProtocolType->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\215\217\350\256\256\347\261\273\345\236\213", nullptr));
    label_Address->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\234\260\345\235\200", nullptr));
    label_Port->setText(QCoreApplication::translate("NetworkSettingsBox", "\347\253\257\345\217\243", nullptr));
    pushButton_Other->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\205\266\345\256\203", nullptr));
    pushButton_Start->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\220\257\345\212\250", nullptr));
}

//NetworkSettingsBox::~NetworkSettingsBox()
//{
//    delete ui;
//}

//void NetworkSettingsWidget::paintEvent(QPaintEvent* event)
//{
//    // 1. 先调用父类的 paintEvent，确保正常绘制背景和子控件
//    QWidget::paintEvent(event);
//    // 2. 使用 QPainter 绘制虚线边框
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, false); // 边框不需要抗锯齿
//
//    // 3. 创建虚线画笔
//    QPen pen;
//    pen.setColor(QColor("#aaaaaa"));  // 灰色
//    pen.setWidth(1);
//    pen.setStyle(Qt::DashLine);       // 虚线样式
//    pen.setDashPattern({ 2, 2 });       // 2像素实线，2像素空隙（可调）
//    painter.setPen(pen);
//
//    // 4. 计算绘制矩形（避开边缘，留出边框空间）
//    QRect rect = this->rect();
//    rect.adjust(1, 1, -1, -1); // 缩小1像素，防止边框被裁剪
//
//    // 5. 绘制矩形边框
//    painter.drawRect(rect);
//}
