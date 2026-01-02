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
	connect(this->comboBox_WorkMode, &QComboBox::currentIndexChanged, [this]() {
		if (this->networkActive == true)
		{
			qDebug() << "错误，网络正在活动时文本不应当变化" << __FILE__ << __LINE__;
			return;
		}
		
		this->changeUiAccordingOption();

		emit this->modeOptionChanged(this->getSelectedMode());
		});

	//按钮按下
	connect(this->toggleButton, &QPushButton::clicked, [this]() {
		emit this->requestWork(this->getSelectedMode());
		});

	//配置连接 刷新
	connect(this->pushButton_Refresh, &QPushButton::clicked, [this]() {
		this->refreshAddress();
		});
	
	this->changeUiAccordingState(false);
	this->changeUiAccordingOption();
	this->refreshAddress();
	

	qDebug() << "网络设置窗口建立";
}

void NetworkSettingsBox::setupUi(void)
{
	this->resize(175, 225);
	this->setMinimumSize(QSize(175, 225));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	gridLayout = new QGridLayout(this);
	label_WorkMode = new QLabel(this);
	label_WorkMode->setFont(font);
	label_WorkMode->setText("工作模式");

	gridLayout->addWidget(label_WorkMode, 0, 0, 1, 2);

	comboBox_WorkMode = new QComboBox(this);
	comboBox_WorkMode->setFont(font);

	gridLayout->addWidget(comboBox_WorkMode, 1, 0, 1, 3);

	label_Address = new QLabel(this);
	label_Address->setFont(font);
	label_Address->setText("地址");

	gridLayout->addWidget(label_Address, 2, 0, 1, 1);

	lineEdit_Address = new QLineEdit(this);
	lineEdit_Address->setFont(font);

	gridLayout->addWidget(lineEdit_Address, 3, 0, 1, 3);

	comboBox_Address = new AutoWidthCombobox(this);
	comboBox_Address->setFont(font);

	gridLayout->addWidget(comboBox_Address, 4, 0, 1, 3);

	label_Port = new QLabel(this);
	label_Port->setFont(font);
	label_Port->setText("端口");

	gridLayout->addWidget(label_Port, 5, 0, 1, 1);

	spinBox_Port = new QSpinBox(this);
	spinBox_Port->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
	spinBox_Port->setMaximum(65535);
	spinBox_Port->setValue(9999);

	gridLayout->addWidget(spinBox_Port, 6, 0, 1, 3);

	led = new LED_Widget(this);
	led->setMinimumSize(QSize(24, 24));
	led->setMaximumSize(QSize(24, 24));

	gridLayout->addWidget(led, 7, 0, 1, 1);

	pushButton_Refresh = new QPushButton(this);
	pushButton_Refresh->setMinimumSize(QSize(40, 0));
	pushButton_Refresh->setFont(font);
	pushButton_Refresh->setText("刷新");

	gridLayout->addWidget(pushButton_Refresh, 7, 1, 1, 1);

	toggleButton = new ToggleButton(this);
	toggleButton->setMinimumSize(QSize(80, 0));
	toggleButton->setFont(font);
	toggleButton->setText("启动");

	gridLayout->addWidget(toggleButton, 7, 2, 1, 1);
}


WorkMode NetworkSettingsBox::getSelectedMode(void)
{
	return this->comboBox_WorkMode->currentData().value<WorkMode>();
}


QHostAddress NetworkSettingsBox::getAddress(void)
{
	WorkMode mode = this->getSelectedMode();
	QHostAddress address;
	// TCP 客户端应当从地址编辑行中得到地址
	if (mode == WorkMode::TCP_Client)
	{
		QString text = this->lineEdit_Address->text();
		address.setAddress(text);
	}
	// TCP 服务器 或 UDP 应当从地址下拉框中得到地址
	else if (mode == WorkMode::TCP_Server || mode==WorkMode::UDP)
	{
		// 从下拉框的用户数据中取
		QVariant data = this->comboBox_Address->currentData();
		if (data.isValid())
		{
			address = data.value<QHostAddress>();//预设项
		}
	}
	qDebug()<<"选择的 IP 地址为： " << address;
	return address;
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
	this->toggleButton->setCheckedState(state);
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
		this->toggleButton->setTexts("建立连接","断开连接");
		this->pushButton_Refresh->hide();
	}
	//如果是 TCP 服务器
	else if (mode == WorkMode::TCP_Server)
	{
		this->label_Address->setText("本地 IP 地址");
		this->label_Port->setText("本地端口");
		this->lineEdit_Address->hide();
		this->comboBox_Address->show();
		this->toggleButton->setTexts("启动监听","停止监听");
		this->pushButton_Refresh->show();
	}
	//如果是 UDP
	else if (mode == WorkMode::UDP)
	{
		this->label_Address->setText("本地 IP 地址");
		this->label_Port->setText("本地端口");
		this->lineEdit_Address->hide();
		this->comboBox_Address->show();
		this->toggleButton->setTexts("绑定","关闭");
		this->pushButton_Refresh->show();
	}
}

void NetworkSettingsBox::refreshAddress(void)
{
	this->comboBox_Address->clear();//清空下拉框

	// === 添加特殊通配符地址（用于监听所有接口）===
	this->comboBox_Address->addItem(
		"0.0.0.0    (IPv4 任意地址)", QVariant::fromValue(QHostAddress(QHostAddress::Any)));
	this->comboBox_Address->addItem(
		"::    (IPv6 任意地址)", QVariant::fromValue(QHostAddress(QHostAddress::AnyIPv6)));

	// === 添加回环地址 ===
	this->comboBox_Address->addItem(
		"127.0.0.1    (IPv4 回环地址)", QVariant::fromValue(QHostAddress(QHostAddress::LocalHost)));
	this->comboBox_Address->addItem(
		"::1    (IPv6 回环地址)", QVariant::fromValue(QHostAddress(QHostAddress::LocalHostIPv6)));

	// 获取本机所有 IPv4/IPv6 地址
	QList<QHostAddress> addresses = QNetworkInterface::allAddresses();	
	//添加选项
	for (const QHostAddress& addr : addresses)
	{
		//跳过已经添加的
		if (addr == QHostAddress::LocalHost || addr == QHostAddress::LocalHostIPv6) continue;
		
		// 添加 IP 地址
		this->comboBox_Address->addItem(addr.toString(), QVariant::fromValue(addr));
	}
}

NetworkSettingsBox::~NetworkSettingsBox()
{
	qDebug() << "网络设置窗口关闭";
}

