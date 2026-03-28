#include "network_settings_box.h"
#include "ui_network_settings_box.h"

#include <QNetworkInterface>

NetworkSettingsBox::NetworkSettingsBox(QWidget* parent)
	: QGroupBox(parent)
	, ui(new Ui::NetworkSettingsBox)
{
	ui->setupUi(this);

	//创建 TCP 服务器 需要的 连接到本服务器的客户端展示表格
	ClientesTitle* title = new ClientesTitle(this);
	ui->clientListWidget->setTitleWidget(title);

	//添加相关选项
	ui->comboBox_WorkMode->addItem("TCP 客户端", QVariant::fromValue(WorkMode::TCP_Client));
	ui->comboBox_WorkMode->addItem("TCP 服务器", QVariant::fromValue(WorkMode::TCP_Server));
	ui->comboBox_WorkMode->addItem("UDP", QVariant::fromValue(WorkMode::UDP));
	ui->comboBox_WorkMode->addItem("UDP 只发送", QVariant::fromValue(WorkMode::UDP_Send_Only));
	//配置连接 选项变化
	connect(ui->comboBox_WorkMode, &QComboBox::currentIndexChanged, [this]() {
		if (this->networkActive == true)
		{
			qDebug() << "错误，网络正在活动时文本不应当变化" << __FILE__ << __LINE__;
			return;
		}

		this->changeUiAccordingOption();

		emit this->modeOptionChanged(this->getSelectedMode());
		});

	//按钮按下
	connect(ui->button_Switch, &QPushButton::clicked, [this]() {
		emit this->requestWork(this->getSelectedMode());
		});

	//配置连接 刷新
	connect(ui->button_Refresh, &QPushButton::clicked, [this]() {
		this->refreshLocalAddress();
		});

	this->changeUiAccordingState(false);
	this->changeUiAccordingOption();
	this->refreshLocalAddress();

	/*QSize min_size = this->gridLayout->totalMinimumSize();
	this->setMinimumSize(min_size);*/

	this->adjustSize();// 让窗口自己计算合适尺寸
	this->setMinimumSize(this->sizeHint());// 锁定最小尺寸（防止被压缩）
	qDebug() << "网络设置窗口建立";
}


WorkMode NetworkSettingsBox::getSelectedMode(void) const
{
	return ui->comboBox_WorkMode->currentData().value<WorkMode>();
}


QHostAddress NetworkSettingsBox::getLocalAddress(void) const
{
	QHostAddress address;

	// TCP 服务器 或 UDP 应当从地址下拉框中得到地址
	// 从下拉框的用户数据中取
	QVariant data = ui->comboBox_LocalAddress->currentData();
	if (data.isValid())
	{
		address = data.value<QHostAddress>();//预设项
	}

	//qDebug()<<"选择的 本地 IP 地址为： " << address;
	return address;
}

uint16_t NetworkSettingsBox::getLocalPort(void) const
{
	return ui->spinBox_LocalPort->value();
}

QHostAddress NetworkSettingsBox::getTargetAddress(void) const
{
	// 从编辑框得到ip地址字符串
	QString ip_str = ui->lineEdit_TargetAddress->text();
	QHostAddress address(ip_str);

	//qDebug() << "选择的 目标 IP 地址为： " << address;
	return address;
}

uint16_t NetworkSettingsBox::getTargetPort(void) const
{
	return ui->spinBox_TargetPort->value();
}

void NetworkSettingsBox::changeUiAccordingState(bool state)
{
	this->networkActive = state;//更新网络状态

	ui->comboBox_WorkMode->setEnabled(!state);
	ui->comboBox_LocalAddress->setEnabled(!state);
	ui->spinBox_LocalPort->setReadOnly(state);
	//TCP 客户端工作模式下，开始工作后，目标地址端口只读，停止工作后恢复
	if (this->getSelectedMode() == WorkMode::TCP_Client)
	{
		ui->lineEdit_TargetAddress->setReadOnly(state);
		ui->spinBox_TargetPort->setReadOnly(state);
	}

	ui->led->setState(state);
	ui->button_Switch->setCheckedState(state);
}

ClientWidget* NetworkSettingsBox::push_backClientLine(QString ip, uint16_t port)
{
	ClientWidget* clientLine = new ClientWidget(this, ip, QString::number(port));
	ui->clientListWidget->push_back(clientLine);
	return clientLine;
}

void NetworkSettingsBox::eraseClientLine(int pos)
{
	ui->clientListWidget->erase(pos);
}

void NetworkSettingsBox::clearClientLines()
{
	ui->clientListWidget->clear();
}



void NetworkSettingsBox::changeUiAccordingOption(void)
{
	WorkMode mode = this->getSelectedMode();
	//如果是 TCP 客户端
	if (mode == WorkMode::TCP_Client)
	{
		// 隐藏本地地址、端口这些
		ui->label_LocalAddress->hide();
		ui->comboBox_LocalAddress->hide();
		ui->label_LocalPort->hide();
		ui->spinBox_LocalPort->hide();

		//展示目标地址、端口这些
		ui->label_TargetAddress->show();
		ui->lineEdit_TargetAddress->show();
		ui->label_TargetPort->show();
		ui->spinBox_TargetPort->show();

		ui->button_Switch->setTexts("建立连接", "断开连接");//调整按钮文字
		ui->button_Refresh->hide();//隐藏刷新按钮

		ui->clientListWidget->hide();//隐藏tcp客户端展示窗口
	}
	//如果是 TCP 服务器
	else if (mode == WorkMode::TCP_Server)
	{
		// 展示本地地址、端口这些
		ui->label_LocalAddress->show();
		ui->comboBox_LocalAddress->show();
		ui->label_LocalPort->show();
		ui->spinBox_LocalPort->show();

		//隐藏目标地址、端口这些
		ui->label_TargetAddress->hide();
		ui->lineEdit_TargetAddress->hide();
		ui->label_TargetPort->hide();
		ui->spinBox_TargetPort->hide();

		ui->button_Switch->setTexts("启动监听", "停止监听");//调整按钮文字
		ui->button_Refresh->show();//展示刷新按钮

		ui->clientListWidget->show();//展示tcp客户端展示窗口
	}
	//如果是 UDP
	else if (mode == WorkMode::UDP)
	{
		// 展示本地地址、端口这些
		ui->label_LocalAddress->show();
		ui->comboBox_LocalAddress->show();
		ui->label_LocalPort->show();
		ui->spinBox_LocalPort->show();

		//展示目标地址、端口这些
		ui->label_TargetAddress->show();
		ui->lineEdit_TargetAddress->show();
		ui->label_TargetPort->show();
		ui->spinBox_TargetPort->show();

		ui->button_Switch->setTexts("绑定", "关闭");//调整按钮文字
		ui->button_Refresh->show();//展示刷新按钮

		ui->clientListWidget->hide();//展示tcp客户端展示窗口
	}
	//如果是 UDP只发送
	else if (mode == WorkMode::UDP_Send_Only)
	{
		// 隐藏本地地址、端口这些
		ui->label_LocalAddress->hide();
		ui->comboBox_LocalAddress->hide();
		ui->label_LocalPort->hide();
		ui->spinBox_LocalPort->hide();

		//展示目标地址、端口这些
		ui->label_TargetAddress->show();
		ui->lineEdit_TargetAddress->show();
		ui->label_TargetPort->show();
		ui->spinBox_TargetPort->show();

		ui->button_Switch->setTexts("开始工作", "停止工作");//调整按钮文字
		ui->button_Refresh->hide();//隐藏刷新按钮

		ui->clientListWidget->hide();//隐藏tcp客户端展示窗口
	}
	this->adjustSize();// 让窗口自己计算合适尺寸
	//this->setMinimumHeight(this->sizeHint().height());// 锁定最小高度（防止被压缩）
}

void NetworkSettingsBox::refreshLocalAddress(void)
{
	ui->comboBox_LocalAddress->clear();//清空下拉框

	// === 添加特殊通配符地址（用于监听所有接口）===
	ui->comboBox_LocalAddress->addItem(
		"0.0.0.0    (IPv4 任意地址)", QVariant::fromValue(QHostAddress(QHostAddress::Any)));
	ui->comboBox_LocalAddress->addItem(
		"::    (IPv6 任意地址)", QVariant::fromValue(QHostAddress(QHostAddress::AnyIPv6)));

	// === 添加回环地址 ===
	ui->comboBox_LocalAddress->addItem(
		"127.0.0.1    (IPv4 回环地址)", QVariant::fromValue(QHostAddress(QHostAddress::LocalHost)));
	ui->comboBox_LocalAddress->addItem(
		"::1    (IPv6 回环地址)", QVariant::fromValue(QHostAddress(QHostAddress::LocalHostIPv6)));

	// 获取本机所有 IPv4/IPv6 地址
	QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
	//添加选项
	for (const QHostAddress& addr : addresses)
	{
		//跳过已经添加的
		if (addr == QHostAddress::LocalHost || addr == QHostAddress::LocalHostIPv6) continue;

		// 添加 IP 地址
		ui->comboBox_LocalAddress->addItem(addr.toString(), QVariant::fromValue(addr));
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