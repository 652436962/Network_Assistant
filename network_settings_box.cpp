#include "network_settings_box.h"

#include <QPainter>

NetworkSettingsBox::NetworkSettingsBox(QWidget* parent)
	: QGroupBox(parent)
{
	this->setupUi();

	//添加相关选项
	this->comboBox_WorkMode->addItem("TCP 服务器", QVariant::fromValue(WorkMode::TCP_Server));
	this->comboBox_WorkMode->addItem("TCP 客户端", QVariant::fromValue(WorkMode::TCP_Client));
	this->comboBox_WorkMode->addItem("UDP", QVariant::fromValue(WorkMode::UDP));
	//配置连接 选项变化
	connect(this->comboBox_WorkMode, &QComboBox::currentIndexChanged, this, [this]() {
		if (this->networkActive == true)
		{
			qDebug() << "错误，网络正在活动时文本不应当变化";
			return;
		}
		WorkMode type = this->getSelectedMode();
		QString switchString = "";
		switch (type)
		{
		case WorkMode::TCP_Server:
			switchString = "启动监听";
			break;
		case WorkMode::TCP_Client:
			switchString = "建立连接";
			break;
		case WorkMode::UDP:
			switchString = "打开";
			break;
		default: break;
		}
		this->pushButton_Switch->setText(switchString);
		});

	//按钮按下
	connect(this->pushButton_Switch, &QPushButton::clicked, this, &NetworkSettingsBox::clicked);

	this->changeUI(false);

	qDebug() << "网络设置窗口建立";
}

void NetworkSettingsBox::setupUi(void)
{
	if (this->objectName().isEmpty())
		this->setObjectName("NetworkSettingsBox");
	this->resize(175, 225);
	this->setMinimumSize(QSize(175, 225));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	gridLayout = new QGridLayout(this);
	gridLayout->setObjectName("gridLayout");
	label_WorkMode = new QLabel(this);
	label_WorkMode->setObjectName("label_WorkMode");
	label_WorkMode->setFont(font);

	gridLayout->addWidget(label_WorkMode, 0, 0, 1, 2);

	comboBox_WorkMode = new QComboBox(this);
	comboBox_WorkMode->setObjectName("comboBox_ProtocolType");
	comboBox_WorkMode->setFont(font);

	gridLayout->addWidget(comboBox_WorkMode, 1, 0, 1, 3);

	label_Address = new QLabel(this);
	label_Address->setObjectName("label_Address");
	label_Address->setFont(font);

	gridLayout->addWidget(label_Address, 2, 0, 1, 1);

	lineEdit_Address = new QLineEdit(this);
	lineEdit_Address->setObjectName("lineEdit_Address");
	lineEdit_Address->setFont(font);

	gridLayout->addWidget(lineEdit_Address, 3, 0, 1, 3);

	label_Port = new QLabel(this);
	label_Port->setObjectName("label_Port");
	label_Port->setFont(font);

	gridLayout->addWidget(label_Port, 4, 0, 1, 1);

	spinBox_Port = new QSpinBox(this);
	spinBox_Port->setObjectName("spinBox_Port");
	spinBox_Port->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
	spinBox_Port->setMaximum(65535);
	spinBox_Port->setValue(8080);


	gridLayout->addWidget(spinBox_Port, 5, 0, 1, 3);

	led = new LED_Widget(this);
	led->setObjectName("led");
	led->setMinimumSize(QSize(24, 24));
	led->setMaximumSize(QSize(24, 24));

	gridLayout->addWidget(led, 6, 0, 1, 1);

	pushButton_Other = new QPushButton(this);
	pushButton_Other->setObjectName("pushButton_Other");
	pushButton_Other->setMinimumSize(QSize(40, 0));
	pushButton_Other->setFont(font);

	gridLayout->addWidget(pushButton_Other, 6, 1, 1, 1);

	pushButton_Switch = new QPushButton(this);
	pushButton_Switch->setObjectName("pushButton_Switch");
	pushButton_Switch->setMinimumSize(QSize(80, 0));
	pushButton_Switch->setFont(font);

	gridLayout->addWidget(pushButton_Switch, 6, 2, 1, 1);


	retranslateUi();

	QMetaObject::connectSlotsByName(this);
}

void NetworkSettingsBox::retranslateUi(void)
{
	this->setWindowTitle(QCoreApplication::translate("NetworkSettingsBox", "Form", nullptr));
	label_WorkMode->setText(QCoreApplication::translate("NetworkSettingsBox", reinterpret_cast<const char*>(u8"工作模式"), nullptr));
	label_Address->setText(QCoreApplication::translate("NetworkSettingsBox", reinterpret_cast<const char*>(u8"地址"), nullptr));
	label_Port->setText(QCoreApplication::translate("NetworkSettingsBox", reinterpret_cast<const char*>(u8"端口"), nullptr));
	pushButton_Other->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\205\266\345\256\203", nullptr));
	pushButton_Switch->setText(QCoreApplication::translate("NetworkSettingsBox", "\345\220\257\345\212\250", nullptr));
}

WorkMode NetworkSettingsBox::getSelectedMode(void)
{
	return this->comboBox_WorkMode->currentData().value<WorkMode>();
}

QString NetworkSettingsBox::getAddress(void)
{
	return this->lineEdit_Address->text();
}

uint16_t NetworkSettingsBox::getPortValue(void)
{
	return this->spinBox_Port->value();
}

void NetworkSettingsBox::changeUI(bool state)
{
	this->networkActive = state;
	this->led->setState(state);
	WorkMode type = this->getSelectedMode();
	QString switchString = "";
	switch (type)
	{
	case WorkMode::TCP_Server:
		if (state) switchString = "停止监听";
		else switchString = "启动监听";
		break;
	case WorkMode::TCP_Client:
		if (state) switchString = "断开连接";
		else switchString = "建立连接";
		break;
	case WorkMode::UDP:
		if (state) switchString = "关闭";
		else switchString = "打开";
		break;
	default: break;
	}
	this->pushButton_Switch->setText(switchString);
	this->comboBox_WorkMode->setEnabled(!state);
	this->lineEdit_Address->setReadOnly(state);
	this->spinBox_Port->setReadOnly(state);
}

NetworkSettingsBox::~NetworkSettingsBox()
{
	qDebug() << "网络设置窗口关闭";
}

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
