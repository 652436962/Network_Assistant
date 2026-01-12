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
	this->comboBox_WorkMode->addItem("UDP 只发送", QVariant::fromValue(WorkMode::UDP_Send_Only));
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
	connect(this->button_Switch, &QPushButton::clicked, [this]() {
		emit this->requestWork(this->getSelectedMode());
		});

	//配置连接 刷新
	connect(this->button_Refresh, &QPushButton::clicked, [this]() {
		this->refreshLocalAddress();
		});
	
	this->changeUiAccordingState(false);
	this->changeUiAccordingOption();
	this->refreshLocalAddress();
	
	/*QSize min_size = this->gridLayout->totalMinimumSize();
	this->setMinimumSize(min_size);*/

	this->adjustSize();
	qDebug() << "网络设置窗口建立";
}

void NetworkSettingsBox::setupUi(void)
{
	this->resize(190, 309);
	this->setMinimumSize(QSize(128, 128));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(4);
	verticalLayout->setContentsMargins(2, 2, 2, 2);
	label_WorkMode = new QLabel(this);
	label_WorkMode->setFont(font);

	verticalLayout->addWidget(label_WorkMode);

	comboBox_WorkMode = new AutoWidthCombobox(this);
	comboBox_WorkMode->setFont(font);

	verticalLayout->addWidget(comboBox_WorkMode);

	label_LocalAddress = new QLabel(this);
	label_LocalAddress->setFont(font);

	verticalLayout->addWidget(label_LocalAddress);

	comboBox_LocalAddress = new AutoWidthCombobox(this);

	verticalLayout->addWidget(comboBox_LocalAddress);

	label_LocalPort = new QLabel(this);
	label_LocalPort->setFont(font);

	verticalLayout->addWidget(label_LocalPort);

	spinBox_LocalPort = new QSpinBox(this);
	spinBox_LocalPort->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
	spinBox_LocalPort->setMaximum(65535);
	spinBox_LocalPort->setValue(8080);

	verticalLayout->addWidget(spinBox_LocalPort);

	label_TargetAddress = new QLabel(this);
	label_TargetAddress->setFont(font);

	verticalLayout->addWidget(label_TargetAddress);

	lineEdit_TargetAddress = new QLineEdit(this);
	lineEdit_TargetAddress->setFont(font);

	verticalLayout->addWidget(lineEdit_TargetAddress);

	label_TargetPort = new QLabel(this);
	label_TargetPort->setFont(font);

	verticalLayout->addWidget(label_TargetPort);

	spinBox_TargetPort = new QSpinBox(this);
	spinBox_TargetPort->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
	spinBox_TargetPort->setMaximum(65535);
	spinBox_TargetPort->setValue(8080);

	verticalLayout->addWidget(spinBox_TargetPort);

	widget = new QWidget(this);
	widget->setMinimumSize(QSize(0, 32));
	widget->setMaximumSize(QSize(16777215, 48));
	horizontalLayout = new QHBoxLayout(widget);
	horizontalLayout->setSpacing(4);
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	led = new LED_Widget(widget);
	led->setMinimumSize(QSize(24, 24));
	led->setMaximumSize(QSize(24, 24));

	horizontalLayout->addWidget(led);

	button_Refresh = new QPushButton(widget);
	button_Refresh->setMinimumSize(QSize(32, 0));
	button_Refresh->setFont(font);

	horizontalLayout->addWidget(button_Refresh);

	button_Switch = new ToggleButton(widget);
	button_Switch->setMinimumSize(QSize(32, 0));
	button_Switch->setFont(font);

	horizontalLayout->addWidget(button_Switch);


	verticalLayout->addWidget(widget);

	clientListWidget = new ScrollableListWidget(this);
	clientListWidget->setMinimumSize(QSize(64, 32));

	verticalLayout->addWidget(clientListWidget);


	label_WorkMode->setText("工作模式");
	label_LocalAddress->setText("本地IP地址");
	label_LocalPort->setText("本地端口");
	label_TargetAddress->setText("目标IP地址");
	label_TargetPort->setText("目标端口");
	button_Refresh->setText("刷新");
	button_Switch->setText("启动");
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
		QString text = this->lineEdit_TargetAddress->text();
		address.setAddress(text);
	}
	// TCP 服务器 或 UDP 应当从地址下拉框中得到地址
	else if (mode == WorkMode::TCP_Server || mode==WorkMode::UDP)
	{
		// 从下拉框的用户数据中取
		QVariant data = this->comboBox_LocalAddress->currentData();
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
	return this->spinBox_LocalPort->value();
}

void NetworkSettingsBox::changeUiAccordingState(bool state)
{
	this->networkActive = state;
	this->led->setState(state);
	this->spinBox_LocalPort->setReadOnly(state);
	this->lineEdit_TargetAddress->setReadOnly(state);
	this->comboBox_WorkMode->setEnabled(!state);
	this->comboBox_LocalAddress->setEnabled(!state);
	this->button_Switch->setCheckedState(state);
}

void NetworkSettingsBox::changeUiAccordingOption(void)
{
	WorkMode mode = this->getSelectedMode();
	//如果是 TCP 客户端
	if (mode == WorkMode::TCP_Client)
	{
		this->label_LocalAddress->show();
		this->label_LocalAddress->setText("服务器 IP 地址");
		this->label_LocalPort->show();
		this->label_LocalPort->setText("服务器端口");
		this->lineEdit_TargetAddress->show();
		this->comboBox_LocalAddress->hide();
		this->button_Switch->setTexts("建立连接","断开连接");
		this->button_Refresh->hide();
		this->spinBox_LocalPort->show();
	}
	//如果是 TCP 服务器
	else if (mode == WorkMode::TCP_Server)
	{
		this->label_LocalAddress->show();
		this->label_LocalAddress->setText("本地 IP 地址");
		this->label_LocalPort->show();
		this->label_LocalPort->setText("本地端口");
		this->lineEdit_TargetAddress->hide();
		this->comboBox_LocalAddress->show();
		this->button_Switch->setTexts("启动监听","停止监听");
		this->button_Refresh->show();
		this->spinBox_LocalPort->show();
	}
	//如果是 UDP
	else if (mode == WorkMode::UDP)
	{
		this->label_LocalAddress->show();
		this->label_LocalAddress->setText("本地 IP 地址");
		this->label_LocalPort->show();
		this->label_LocalPort->setText("本地端口");
		this->lineEdit_TargetAddress->hide();
		this->comboBox_LocalAddress->show();
		this->button_Switch->setTexts("绑定","关闭");
		this->button_Refresh->show();
		this->spinBox_LocalPort->show();
	}
	//如果是 UDP只发送
	else if (mode == WorkMode::UDP_Send_Only)
	{
		this->label_LocalAddress->hide();
		this->label_LocalPort->hide();
		this->lineEdit_TargetAddress->hide();
		this->comboBox_LocalAddress->hide();
		this->button_Switch->setTexts("开始工作", "停止工作");
		this->button_Refresh->hide();
		this->spinBox_LocalPort->hide();
	}
	/*QSize min_size = this->gridLayout->totalMinimumSize();
	this->setMinimumSize(min_size);
	this->adjustSize();*/
}

void NetworkSettingsBox::refreshLocalAddress(void)
{
	this->comboBox_LocalAddress->clear();//清空下拉框

	// === 添加特殊通配符地址（用于监听所有接口）===
	this->comboBox_LocalAddress->addItem(
		"0.0.0.0    (IPv4 任意地址)", QVariant::fromValue(QHostAddress(QHostAddress::Any)));
	this->comboBox_LocalAddress->addItem(
		"::    (IPv6 任意地址)", QVariant::fromValue(QHostAddress(QHostAddress::AnyIPv6)));

	// === 添加回环地址 ===
	this->comboBox_LocalAddress->addItem(
		"127.0.0.1    (IPv4 回环地址)", QVariant::fromValue(QHostAddress(QHostAddress::LocalHost)));
	this->comboBox_LocalAddress->addItem(
		"::1    (IPv6 回环地址)", QVariant::fromValue(QHostAddress(QHostAddress::LocalHostIPv6)));

	// 获取本机所有 IPv4/IPv6 地址
	QList<QHostAddress> addresses = QNetworkInterface::allAddresses();	
	//添加选项
	for (const QHostAddress& addr : addresses)
	{
		//跳过已经添加的
		if (addr == QHostAddress::LocalHost || addr == QHostAddress::LocalHostIPv6) continue;
		
		// 添加 IP 地址
		this->comboBox_LocalAddress->addItem(addr.toString(), QVariant::fromValue(addr));
	}
}

NetworkSettingsBox::~NetworkSettingsBox()
{
	qDebug() << "网络设置窗口关闭";
}




ClientesTitle::ClientesTitle(QWidget* parent) :QWidget(parent)
{
	this->setupUi();
	this->adjustSize();
}
void ClientesTitle::setupUi()
{
	this->resize(270, 32);
	this->setMinimumSize(QSize(128, 32));
	this->setMaximumSize(QSize(16777215, 64));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	widget_2 = new QWidget(this);
	horizontalLayout_2 = new QHBoxLayout(widget_2);
	horizontalLayout_2->setSpacing(2);
	horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
	horizontalSpacer_00 = new QSpacerItem(46, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout_2->addItem(horizontalSpacer_00);

	label_Title = new QLabel(widget_2);
	label_Title->setText("连接到本服务器的所有客户端");

	horizontalLayout_2->addWidget(label_Title);

	horizontalSpacer_01 = new QSpacerItem(45, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout_2->addItem(horizontalSpacer_01);


	verticalLayout->addWidget(widget_2);

	widget = new QWidget(this);
	horizontalLayout = new QHBoxLayout(widget);
	horizontalLayout->setSpacing(2);
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	horizontalSpacer_10 = new QSpacerItem(62, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer_10);

	label_IP = new QLabel(widget);
	label_IP->setText("IP");

	horizontalLayout->addWidget(label_IP);

	horizontalSpacer_11 = new QSpacerItem(63, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer_11);

	label_LocalPort = new QLabel(widget);
	label_LocalPort->setText("端口");

	horizontalLayout->addWidget(label_LocalPort);

	horizontalSpacer_12 = new QSpacerItem(62, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer_12);

	label_Disconnect = new QLabel(widget);
	label_Disconnect->setText("断开");

	horizontalLayout->addWidget(label_Disconnect);


	verticalLayout->addWidget(widget);
}

ClientWidget::ClientWidget(QWidget* parent, QString ip, QString port) :QWidget(parent)
{
	this->setupUi();
	this->lineEdit_IP->setText(ip);
	this->lineEdit_Port->setText(port);
	this->adjustSize();

	//配置连接 断开客户端连接
	connect(this->pushButton, &QPushButton::clicked, [this]() {
		emit this->signal_Disconnect();
		});
}
void ClientWidget::setIP(const QString& ip)
{
	this->lineEdit_IP->setText(ip);
}
void ClientWidget::setPort(const QString& port)
{
	this->lineEdit_Port->setText(port);
}
void ClientWidget::setupUi()
{
	this->resize(346, 32);
	this->setMinimumSize(QSize(0, 32));
	this->setMaximumSize(QSize(16777215, 48));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(8);
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	lineEdit_IP = new QLineEdit(this);
	lineEdit_IP->setReadOnly(true);

	horizontalLayout->addWidget(lineEdit_IP);

	lineEdit_Port = new QLineEdit(this);
	lineEdit_Port->setReadOnly(true);

	horizontalLayout->addWidget(lineEdit_Port);

	pushButton = new QPushButton(this);
	pushButton->setMinimumSize(QSize(32, 32));
	pushButton->setMaximumSize(QSize(48, 48));
	pushButton->setIcon(QIcon(":/icon/image/disconnect.png"));
	horizontalLayout->addWidget(pushButton);

	pushButton->setText(QString());
}