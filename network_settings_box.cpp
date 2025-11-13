#include "network_settings_box.h"


#include <QNetworkInterface>

NetworkSettingsBox::NetworkSettingsBox(QWidget* parent)
	: QGroupBox(parent)
{
	this->setupUi();

	//添加相关选项
	this->comboBox_WorkMode->addItem("TCP 客户端", QVariant::fromValue(WorkMode::TCP_Client));
	this->comboBox_WorkMode->addItem("TCP 服务器", QVariant::fromValue(WorkMode::TCP_Server));	
	this->comboBox_WorkMode->addItem("UDP", QVariant::fromValue(WorkMode::UDP));
	//配置连接 选项变化
	connect(this->comboBox_WorkMode, &QComboBox::currentIndexChanged, this, [this]() {
		if (this->networkActive == true)
		{
			qDebug() << "错误，网络正在活动时文本不应当变化" << __FILE__ << __LINE__;
			return;
		}
		
		this->changeUiAccordingOption();
		});

	//按钮按下
	connect(this->pushButton_Switch, &QPushButton::clicked, [this]() {
		emit this->clicked();
		});
	this->changeUiAccordingOption();
	this->changeUiAccordingState(false);
	this->getLocalAddress();
	

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
	label_WorkMode->setText("工作模式");

	gridLayout->addWidget(label_WorkMode, 0, 0, 1, 2);

	comboBox_WorkMode = new QComboBox(this);
	comboBox_WorkMode->setObjectName("comboBox_ProtocolType");
	comboBox_WorkMode->setFont(font);

	gridLayout->addWidget(comboBox_WorkMode, 1, 0, 1, 3);

	label_Address = new QLabel(this);
	label_Address->setObjectName("label_Address");
	label_Address->setFont(font);
	label_Address->setText("地址");

	gridLayout->addWidget(label_Address, 2, 0, 1, 1);

	lineEdit_Address = new QLineEdit(this);
	lineEdit_Address->setObjectName("lineEdit_Address");
	lineEdit_Address->setFont(font);

	gridLayout->addWidget(lineEdit_Address, 3, 0, 1, 3);

	comboBox_Address = new QComboBox(this);
	comboBox_Address->setObjectName("comboBox_Address");
	comboBox_Address->setFont(font);
	comboBox_Address->setEditable(true);

	gridLayout->addWidget(comboBox_Address, 4, 0, 1, 3);

	label_Port = new QLabel(this);
	label_Port->setObjectName("label_Port");
	label_Port->setFont(font);
	label_Port->setText("端口");

	gridLayout->addWidget(label_Port, 5, 0, 1, 1);

	spinBox_Port = new QSpinBox(this);
	spinBox_Port->setObjectName("spinBox_Port");
	spinBox_Port->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
	spinBox_Port->setMaximum(65535);
	spinBox_Port->setValue(8080);


	gridLayout->addWidget(spinBox_Port, 6, 0, 1, 3);

	led = new LED_Widget(this);
	led->setObjectName("led");
	led->setMinimumSize(QSize(24, 24));
	led->setMaximumSize(QSize(24, 24));

	gridLayout->addWidget(led, 7, 0, 1, 1);

	pushButton_Other = new QPushButton(this);
	pushButton_Other->setObjectName("pushButton_Other");
	pushButton_Other->setMinimumSize(QSize(40, 0));
	pushButton_Other->setFont(font);
	pushButton_Other->setText("其它");

	gridLayout->addWidget(pushButton_Other, 7, 1, 1, 1);

	pushButton_Switch = new QPushButton(this);
	pushButton_Switch->setObjectName("pushButton_Switch");
	pushButton_Switch->setMinimumSize(QSize(80, 0));
	pushButton_Switch->setFont(font);
	pushButton_Switch->setText("启动");

	gridLayout->addWidget(pushButton_Switch, 7, 2, 1, 1);


	QMetaObject::connectSlotsByName(this);
}


WorkMode NetworkSettingsBox::getSelectedMode(void)
{
	return this->comboBox_WorkMode->currentData().value<WorkMode>();
}


QHostAddress NetworkSettingsBox::getAddress(void)
{
	WorkMode mode = this->getSelectedMode();
	// TCP 客户端应当从地址编辑行中得到地址
	if (mode == WorkMode::TCP_Client)
	{
		QString text = this->lineEdit_Address->text();
		QHostAddress addr(text);
		return addr;
	}
	// TCP 服务器 或 UDP 应当从地址下拉框中得到地址
	else if (mode == WorkMode::TCP_Server || mode==WorkMode::UDP)
	{
		// 先尝试从 data 中取（说明是预设项）
		QVariant data = this->comboBox_Address->currentData();
		if (data.isValid() && data.canConvert<QHostAddress>())
		{
			return data.value<QHostAddress>();//预设项
		}

		//解析当前文本（用户手动输入）
		QString text = this->comboBox_Address->currentText().trimmed();
		QHostAddress addr(text);

		return addr;// 成功解析		
	}
	
}

uint16_t NetworkSettingsBox::getPortValue(void)
{
	return this->spinBox_Port->value();
}

void NetworkSettingsBox::changeUiAccordingState(bool state)
{
	this->networkActive = state;
	this->led->setState(state);
	this->spinBox_Port->setReadOnly(state);
	this->lineEdit_Address->setReadOnly(state);
	this->comboBox_WorkMode->setEnabled(!state);
	this->comboBox_Address->setEnabled(!state);
	WorkMode mode = this->getSelectedMode();
	//如果是 TCP 客户端
	if (mode == WorkMode::TCP_Client)
	{
		if (state) this->pushButton_Switch->setText("断开连接");
		else this->pushButton_Switch->setText("建立连接");
	}
	//如果是 TCP 服务器
	else if (mode == WorkMode::TCP_Server)
	{
		if (state) this->pushButton_Switch->setText("停止监听");
		else this->pushButton_Switch->setText("启动监听"); 
	}
	//如果是 UDP
	else if (mode == WorkMode::UDP)
	{
		if (state) this->pushButton_Switch->setText("关闭");
		else this->pushButton_Switch->setText("绑定");
	}
}

void NetworkSettingsBox::changeUiAccordingOption(void)
{
	WorkMode mode = this->getSelectedMode();
	//如果是 TCP 客户端
	if (mode == WorkMode::TCP_Client)
	{
		this->label_Address->setText("服务器 IP 地址");
		this->label_Port->setText("服务器端口");
		this->lineEdit_Address->show();
		this->comboBox_Address->hide();
		this->pushButton_Switch->setText("建立连接");
	}
	//如果是 TCP 服务器
	else if (mode == WorkMode::TCP_Server)
	{
		this->label_Address->setText("本地 IP 地址");
		this->label_Port->setText("本地端口");
		this->lineEdit_Address->hide();
		this->comboBox_Address->show();
		this->pushButton_Switch->setText("启动监听");
	}
	//如果是 UDP
	else if (mode == WorkMode::UDP)
	{
		this->label_Address->setText("本地 IP 地址");
		this->label_Port->setText("本地端口");
		this->lineEdit_Address->hide();
		this->comboBox_Address->show();
		this->pushButton_Switch->setText("绑定");
	}
}

void NetworkSettingsBox::getLocalAddress(void)
{
	// 获取本机所有 IPv4/IPv6 地址
	QList<QHostAddress> addresses = QNetworkInterface::allAddresses();

	for (const QHostAddress& addr : addresses)
	{
		QString displayText = addr.toString();

		// 添加项：text = 字符串, userData = QHostAddress
		this->comboBox_Address->addItem(displayText, QVariant::fromValue(addr));
	}
}

NetworkSettingsBox::~NetworkSettingsBox()
{
	qDebug() << "网络设置窗口关闭";
}

