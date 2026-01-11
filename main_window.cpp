#include "main_window.h"

#include "ui_main_window.h"

#include "led_widget.h"

#include <QDialog>
#include <QHostInfo>

#include <QTableWidget>//表格
#include <QActionGroup>
#include <QSysInfo>//系统信息
#include <QNetworkInterface>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>

#include <QProcess>

#include "sundry_qt.h"

#include "Windows.h"


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);//配置UI



	this->notificationManager = new NotificationManager(this, this);//通知气泡管理
	this->notificationManager->newBubble("欢迎使用");

	encodingUsed = getLocalEncoding();//获取本机使用的编码
	qDebug() << "本机编码" << getEncodingQByteArray(encodingUsed);


	//菜单栏相关设置
	{
		connect(ui->action_Ncpa, &QAction::triggered, [this]() {
			// 打开“网络连接”窗口
			qDebug() << "打开Windows网络连接";
			QProcess::startDetached("control.exe", { "ncpa.cpl" });
			});
		connect(ui->action_Control, &QAction::triggered, [this]() {
			qDebug() << "打开Windows控制面板";
			QProcess::startDetached("control.exe");//打开Windows控制面板
			});
		//配置连接 展示主机信息
		connect(ui->action_Infomation, &QAction::triggered, this, &MainWindow::showLocalIPConfig);
		//将编码选项加入组
		QActionGroup* encodingGroup = new QActionGroup(this);
		encodingGroup->setExclusive(true);//自动互斥
		encodingGroup->addAction(ui->action_UTF8);
		encodingGroup->addAction(ui->action_GB18030);
		connect(ui->action_UTF8, &QAction::triggered, [](bool checked) {
			if (checked) encodingUsed = EncodingEnum::UTF8;
			qDebug() << "编码 " << getEncodingQByteArray(encodingUsed);
			});
		connect(ui->action_GB18030, &QAction::triggered, [](bool checked) {
			if (checked) encodingUsed = EncodingEnum::GB18030;
			qDebug() << "编码 " << getEncodingQByteArray(encodingUsed);
			});
		if (encodingUsed == EncodingEnum::UTF8) ui->action_UTF8->setChecked(true);
		else if (encodingUsed == EncodingEnum::GB18030) ui->action_GB18030->setChecked(true);
	}


	//左侧窗口相关配置
	ui->udpTargetBox->hide();// UDP 发送目标窗口开始隐藏
	//创建 TCP 服务器 需要的 连接到本服务器的客户端展示表格
	ClientesTitle* title = new ClientesTitle(this);
	ui->clientListWidget->setTitleWidget(title);
	ui->clientListWidget->hide();//默认隐藏


	//配置连接 请求工作
	connect(ui->network_settings, &NetworkSettingsBox::requestWork, [this](WorkMode mode) {
		//作为 TCP 客户端工作
		if (mode == WorkMode::TCP_Client)
		{
			this->asTcpClientOperation();
		}
		//作为 TCP 服务器工作
		else if (mode == WorkMode::TCP_Server)
		{
			this->asTcpServerOperation();
		}
		//作为 UDP 工作
		else if (mode == WorkMode::UDP)
		{
			this->asUdpOperation();
		}
		//工作模式 UDP 只发送
		else if (mode == WorkMode::UDP_Send_Only)
		{
			this->asUdpSendOnlyOperation();
		}
		});
	//配置连接 工作模式选项切换
	connect(ui->network_settings, &NetworkSettingsBox::modeOptionChanged, [this](WorkMode mode) {
		//作为 TCP 客户端工作
		if (mode == WorkMode::TCP_Client)
		{
			ui->clientListWidget->hide();
			ui->udpTargetBox->hide();
			ui->groupBox_Receive->show();
			ui->receive_settings->show();
		}
		//作为 TCP 服务器工作
		else if (mode == WorkMode::TCP_Server)
		{
			ui->clientListWidget->show();
			ui->udpTargetBox->hide();
			ui->groupBox_Receive->show();
			ui->receive_settings->show();
		}
		//作为 UDP 工作
		else if (mode == WorkMode::UDP)
		{
			ui->clientListWidget->hide();
			ui->udpTargetBox->show();
			ui->groupBox_Receive->show();
			ui->receive_settings->show();
		}
		//工作模式 UDP 只发送
		else if (mode == WorkMode::UDP_Send_Only)
		{
			ui->clientListWidget->hide();
			ui->udpTargetBox->show();
			ui->groupBox_Receive->hide();//隐藏接收区
			ui->receive_settings->hide();//隐藏接收设置
		}
		this->adjustSize();//让窗口自动缩放到刚好容纳所有内容
		});

	//配置连接 网络设置改变 UI
	connect(this, &MainWindow::workingStateChanged, ui->network_settings, &NetworkSettingsBox::changeUiAccordingState);
	connect(this, &MainWindow::workingStateChanged, ui->send_settings, &SendSettingsBox::changeAccordingState);

	//配置连接 切换发送区
	connect(ui->send_settings, &SendSettingsBox::changeSendArray, [this](SendOptions option) {
		if (option == SendOptions::single)
		{
			ui->singleSend->show();//展示单项发送区
			ui->multipleSend->hide();//隐藏多项发送区

			if (ui->send_settings->getAutoSend())//如果设置了自动发送
			{
				ui->singleSend->setAutoSend(true);//开启单项发送区自动发送
				ui->multipleSend->setAutoSend(false);//取消多项发送区自动发送
			}
		}
		else if (option == SendOptions::multiple)
		{
			ui->singleSend->hide();//隐藏单项发送区
			ui->multipleSend->show();//展示多项发送区

			if (ui->send_settings->getAutoSend())//如果设置了自动发送
			{
				ui->singleSend->setAutoSend(false);//取消单项发送区自动发送
				ui->multipleSend->setAutoSend(true);//开启多项发送区自动发送
			}
		}
		});

	//配置连接 接收设置 发出
	{
		connect(ui->receive_settings, &ReceiveSettingsBox::receiveAreaClear, ui->receive_area, &ReceiveWidget::clear);
		connect(ui->receive_settings, &ReceiveSettingsBox::setText, ui->receive_area, &ReceiveWidget::setText);
		connect(ui->receive_settings, &ReceiveSettingsBox::setStopDispalying, ui->receive_area, &ReceiveWidget::setStopDisplaying);
		connect(ui->receive_settings, &ReceiveSettingsBox::setTimestamp, ui->receive_area, &ReceiveWidget::setTimestamp);
		//配置连接 保存到文本文件
		connect(ui->receive_settings, &ReceiveSettingsBox::receiveToFile, ui->receive_area, &ReceiveWidget::receiveToFile);
	}


	//右侧窗口相关配置

	//配置连接 接收区请求通知
	connect(ui->receive_area, &ReceiveWidget::requestToNotification, [this](QString notification) {
		this->notificationManager->newBubble(notification);
		});

	QVBoxLayout* verticalLayout = qobject_cast<QVBoxLayout*>(ui->widget_Right->layout());
	if (verticalLayout == nullptr) {
		qDebug() << "错误 空指针" << __FILE__ << __LINE__;
	}
	//配置连接 工作中 允许发送
	connect(this, &MainWindow::workingStateChanged, ui->singleSend, &SingleSendWidget::setAllowSending);
	//配置连接 请求通知
	connect(ui->singleSend, &SingleSendWidget::requestToNotification, [this](QString notification) {
		this->notificationManager->newBubble(notification);
		});

	// 开始隐藏多项发送区
	ui->multipleSend->hide();
	//配置连接 工作中 允许发送
	connect(this, &MainWindow::workingStateChanged, ui->multipleSend, &MultipleSendWidget::setAllowSending);
	//配置连接 请求通知
	connect(ui->multipleSend, &MultipleSendWidget::requestToNotification, [this](QString notification) {
		this->notificationManager->newBubble(notification);
		});

	//配置连接 发送设置 -> 单项发送区 和 多项发送区
	{
		connect(ui->send_settings, &SendSettingsBox::setText, ui->singleSend, &SingleSendWidget::setText);
		connect(ui->send_settings, &SendSettingsBox::setAppend, ui->singleSend, &SingleSendWidget::setAppend);

		connect(ui->send_settings, &SendSettingsBox::setText, ui->multipleSend, &MultipleSendWidget::setText);
		connect(ui->send_settings, &SendSettingsBox::setAppend, ui->multipleSend, &MultipleSendWidget::setAppend);

		//自动发送
		connect(ui->send_settings, &SendSettingsBox::requestAutoSend, [this](bool open) {
			SendOptions option = ui->send_settings->getSendOption();
			if (option == SendOptions::single)
			{
				ui->singleSend->setAutoSend(open);
			}
			else if (option == SendOptions::multiple)
			{
				ui->multipleSend->setAutoSend(open);
			}
			});
		connect(ui->send_settings, &SendSettingsBox::requestChangeCycle, [this](int msec) {
			SendOptions option = ui->send_settings->getSendOption();
			if (option == SendOptions::single)
			{
				ui->singleSend->setSendCycle(msec);
			}
			else if (option == SendOptions::multiple)
			{
				ui->multipleSend->setSendCycle(msec);
			}
			});
	}

	this->adjustSize();
	qDebug() << "主窗口建立";
}

MainWindow::~MainWindow()
{
	//关闭 Tcp 服务器	
	//断开所有客户端连接
	QList<QTcpSocket*> socketsList = this->tcpClientesList;// 复制一份指针列表（浅拷贝，安全）
	for (auto it = socketsList.begin(); it != socketsList.end(); it++)//遍历指针列表
	{
		QTcpSocket* tcpSocket = *it;
		if (tcpSocket == nullptr)
		{
			qDebug() << "错误 空指针" << __FILE__ << __LINE__;
			continue;
		}
		if (tcpSocket->state() == QAbstractSocket::ConnectedState)
		{
			tcpSocket->disconnectFromHost();
		}
		//会在 tcpSocket 的 disconnected 信号对应的槽函数中清理
	}
	//注意，在清理时会删除链表节点，因此，如果遍历原本的链表会错！！
	// 关闭服务器
	if (this->tcpServer != nullptr)//关闭服务器
	{
		if (tcpServer->isListening())
		{
			tcpServer->close();//停止网络监听
		}
	}

	//关闭 Tcp 客户端
	if (this->clientTcpSocket != nullptr)
	{
		if (clientTcpSocket->state() == QAbstractSocket::ConnectedState)
		{
			clientTcpSocket->disconnectFromHost();//正常 TCP 4次挥手
			//在 disconnected 对应的槽函数中清理
		}
	}

	//udp 没有四次挥手  parent 是 mainwindow 自动释放，不需要额外处理

	delete ui;

	qDebug() << "主窗口关闭";
}

void MainWindow::showLocalIPConfig(void)
{
	qDebug() << "展示本机信息";
	QDialog* dialog = new QDialog(this);
	dialog->setWindowTitle("本机信息");
	dialog->setMinimumSize(400, 400);
	QTableWidget* table = new QTableWidget(dialog);
	/*table->resize(200, 300);*/
	table->setColumnCount(3);
	/*table->setHorizontalHeaderLabels(QStringList() << "属性" << "值");*/
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);// 禁止编辑
	//table->setSelectionBehavior(QAbstractItemView::SelectRows);// 点击选中行
	QFont font;
	font.setPointSize(10);
	table->setFont(font);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(table);
	dialog->setLayout(layout);
	// 设置为非模态对话框
	dialog->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动释放内存
	dialog->show();

	int row = 0;
	auto addRow = [&](const QString& c0, const QString& c1, const QString& c2)
		{
			table->insertRow(row);
			table->setItem(row, 0, new QTableWidgetItem(c0));
			table->setItem(row, 1, new QTableWidgetItem(c1));
			table->setItem(row, 2, new QTableWidgetItem(c2));
			row++;
		};

	addRow("操作系统", QSysInfo::prettyProductName(), "");
	addRow("操作系统内核", QSysInfo::kernelType(), "");
	addRow("内核版本", QSysInfo::kernelVersion(), "");
	addRow("CPU 架构", QSysInfo::currentCpuArchitecture(), "");
	addRow("本机名", QSysInfo::machineHostName(), "");// 获取主机信息

	// 获取本机所有网络接口（网卡）
	QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
	for (const auto& it_interface : interfaces)
	{
		// 跳过未激活的网卡（比如没插网线、Wi-Fi 关闭） 或 回环地址
		if (!it_interface.flags().testFlag(QNetworkInterface::IsUp) || it_interface.flags().testFlag(QNetworkInterface::IsLoopBack))
		{
			continue;
		}

		qDebug() << "网卡名称" << it_interface.name() << "可读名称" << it_interface.humanReadableName();
		qDebug() << "硬件地址(MAC)" << it_interface.hardwareAddress();
		qDebug() << "接口类型" << it_interface.type();
		qDebug() << "标志" << it_interface.flags();
		addRow("网卡名称", it_interface.humanReadableName(), "");
		addRow("", it_interface.name(), "");
		addRow("硬件地址(MAC)", it_interface.hardwareAddress(), "");
		addRow("接口类型", interfaceTypeToString(it_interface.type()), "");

		//// 输出接口是否活跃
		//if (it_interface.flags().testFlag(QNetworkInterface::IsUp))
		//{
		//    qDebug()<<"状态" << "活动";
		//}
		//else
		//{
		//    qDebug() << "状态" << "非活动";
		//}
		////是否回环
		//if (it_interface.flags().testFlag(QNetworkInterface::IsLoopBack))
		//{
		//    qDebug() << "回环";
		//}
		//else
		//{
		//    qDebug() << "非回环";
		//}


		// 遍历该接口的所有 IP 地址条目（含子网掩码和广播）
		QList<QNetworkAddressEntry> entries = it_interface.addressEntries();
		for (const auto& it_entry : entries)
		{
			QHostAddress ip = it_entry.ip();
			QHostAddress netmask = it_entry.netmask();
			QHostAddress broadcast = it_entry.broadcast();
			if (ip.protocol() == QAbstractSocket::IPv4Protocol)
			{
				qDebug() << "IPv4 地址" << ip.toString();
				qDebug() << "子网掩码" << netmask.toString();
				qDebug() << "广播地址" << broadcast.toString();
				addRow("", "IPv4 地址", ip.toString());
				addRow("", "子网掩码", netmask.toString());
				addRow("", "广播地址", broadcast.toString());

			}
			else if (ip.protocol() == QAbstractSocket::IPv6Protocol)
			{
				qDebug() << "IPv6 地址" << ip.toString();
				qDebug() << "子网前缀" << it_entry.prefixLength();
				addRow("", "IPv6 地址", ip.toString());
				addRow("", "子网前缀", QString::number(it_entry.prefixLength()));
			}
		}
	}


	table->resizeColumnsToContents();
	dialog->adjustSize();
}
void MainWindow::asTcpClientOperation(void)
{
	if (this->clientTcpSocket == nullptr)//客户端 TcpSocket 未创建
	{
		uint16_t port = ui->network_settings->getPortValue();//获取端口
		QHostAddress address = ui->network_settings->getAddress();//获取 IP 地址
		if (address.isNull())
		{
			this->notificationManager->newBubble("地址无效");
			qDebug() << "地址无效" << __FILE__ << __LINE__;
			return;
		}

		this->clientTcpSocket = new QTcpSocket(this);//创建 TcpSocket 变量
		this->clientTcpSocket->connectToHost(address, port);//尝试连接服务器

		/*配置相关链接*/
		//与服务器建立了连接
		connect(this->clientTcpSocket, &QTcpSocket::connected, [this]() {
			if (clientTcpSocket == nullptr)
			{
				qDebug() << "错误 " << __FILE__ << __LINE__;
				return;
			}
			QString connectString = "";
			QTextStream connectStream(&connectString);
			connectStream << "已连接到服务器  " << clientTcpSocket->peerAddress().toString() << " " << clientTcpSocket->peerPort();
			this->notificationManager->newBubble(connectString);
			emit this->workingStateChanged(true);
			qDebug() << connectString;

			});
		//与服务器断开了连接
		connect(this->clientTcpSocket, &QTcpSocket::disconnected, [this]() {
			if (clientTcpSocket == nullptr)
			{
				qDebug() << "错误 " << __FILE__ << __LINE__;
				return;
			}
			QString disconnectString = "";
			QTextStream disconnectStream(&disconnectString);
			disconnectStream << "已断开与服务器  " << clientTcpSocket->peerAddress().toString() << " " << clientTcpSocket->peerPort() << "  的连接";
			this->notificationManager->newBubble(disconnectString);
			clientTcpSocket->deleteLater();//删除 Socket
			clientTcpSocket = nullptr;
			emit this->workingStateChanged(false);
			qDebug() << disconnectString;
			});
		//发生错误
		connect(this->clientTcpSocket, &QTcpSocket::errorOccurred, [this](QAbstractSocket::SocketError error) {
			if (error == QAbstractSocket::RemoteHostClosedError)//这并不是错误情况！！！
			{
				qDebug() << "服务端已关闭连接";
				// 此时 disconnected 会触发，由它清理
				return;
			}
			switch (error) {
			case QAbstractSocket::RemoteHostClosedError://这并不是错误情况！！！
				// ✅ 服务端主动断开，属于正常情况
				qDebug() << "服务端已关闭连接";
				// 此时 disconnected 会触发，由它清理
				break;

			case QAbstractSocket::HostNotFoundError:
				qDebug() << error << "错误：无法找到服务器，请检查 IP 和端口";
				QMessageBox::warning(this, "错误", "无法找到服务器，请检查 IP 和端口");
				break;

			case QAbstractSocket::ConnectionRefusedError:
				qDebug() << error << "错误：连接被拒绝，服务器可能未启动";
				QMessageBox::warning(this, "错误", "连接被拒绝，服务器可能未启动");
				break;

			case QAbstractSocket::NetworkError:
				qDebug() << error << "网络错误：如断网、超时等";
				QMessageBox::warning(this, "错误", "网络错误：如断网、超时等");
				break;

			default:
				qDebug() << error << "未知错误";
				QMessageBox::warning(this, "错误", "未知错误");
				break;
			}
			if (error != QAbstractSocket::RemoteHostClosedError)//不是服务器断开了连接
			{//清理
				if (this->clientTcpSocket != nullptr)
				{
					this->clientTcpSocket->deleteLater();//删除
					this->clientTcpSocket = nullptr;
				}
			}
			});

		//接收到了服务器的数据
		connect(this->clientTcpSocket, &QTcpSocket::readyRead, [this]() {
			if (clientTcpSocket == nullptr)
			{
				qDebug() << "错误 " << __FILE__ << __LINE__;
				return;
			}
			ui->receive_area->appendPlainText("[From TCP Server]");
			QByteArray byteArray = clientTcpSocket->readAll();
			ui->receive_area->showData(byteArray);//在接收区中展示数据
			});

		//配置连接 请求发送
		connect(ui->singleSend, &SingleSendWidget::requestToSend, this->clientTcpSocket,
			static_cast<qint64(QTcpSocket::*)(const QByteArray & data)>(&QTcpSocket::write));
		connect(ui->multipleSend, &MultipleSendWidget::requestToSend, this->clientTcpSocket,
			static_cast<qint64(QTcpSocket::*)(const QByteArray & data)>(&QTcpSocket::write));
	}
	//客户端 TcpSocket 已创建
	else
	{
		if (clientTcpSocket->state() == QAbstractSocket::ConnectedState)
		{
			this->clientTcpSocket->disconnectFromHost();//启动4次挥手，断开连接
		}
		else//正常情况下不应该执行到这里
		{
			this->clientTcpSocket->deleteLater();
			this->clientTcpSocket = nullptr;
			qDebug() << "错误 本客户端Socket未连接" << __FILE__ << __LINE__;
		}
	}
}

void MainWindow::asTcpServerOperation(void)
{
	//服务器还没有创建
	if (this->tcpServer == nullptr)
	{
		if (this->tcpClientesList.empty() != true)
		{
			qDebug() << "错误 服务器创建前客户端链表非空" << __FILE__ << __LINE__;
			return;
		}
		uint16_t port = ui->network_settings->getPortValue();//获取端口
		QHostAddress address = ui->network_settings->getAddress();//获取地址
		if (address.isNull())
		{
			this->notificationManager->newBubble("地址无效");
			qDebug() << "地址无效" << __FILE__ << __LINE__;
			return;
		}

		this->tcpServer = new QTcpServer(this);//创建TCP服务器
		this->tcpServer->setObjectName("TCP Server");


		bool result = tcpServer->listen(address, port); //开始监听
		if (result)//监听启动成功
		{
			emit this->workingStateChanged(true);
			this->notificationManager->newBubble("TCP服务器开始监听");
			qDebug() << "TCP服务器开始监听  地址" << address << " 端口 " << port;
		}
		else//监听启动失败
		{
			this->notificationManager->newBubble("TCP服务器监听启动失败");
			qDebug() << "TCP服务器监听启动失败！ " << __FILE__ << __LINE__;
			QAbstractSocket::SocketError error = tcpServer->serverError();
			QString errorMsg = tcpServer->errorString();
			qDebug() << "错误码 " << error << " 错误信息 " << errorMsg;
			this->tcpServer->deleteLater();
			this->tcpServer = nullptr;

		}

		//配置连接 有新的客户端连接
		connect(this->tcpServer, &QTcpServer::newConnection, this, [this]() {
			/*创建与客户端通信的 socket
			* 自 Qt 6.4 起，创建的 socket 默认父对象为 对应的 QTcpServer 实例
			*/
			QTcpSocket* tcpSocket = this->tcpServer->nextPendingConnection();
			tcpSocket->setParent(this);//设置父对象，由我管理它

			QString address = tcpSocket->peerAddress().toString();
			uint16_t port = tcpSocket->peerPort();

			this->tcpClientesList.push_back(tcpSocket);//加入到队列末尾

			//在表格中展示
			{
				// 插入新行
				ClientWidget* clientLine = new ClientWidget(this, address, QString::number(port));
				ui->clientListWidget->push_back(clientLine);
				connect(clientLine, &ClientWidget::signal_Disconnect, this, [tcpSocket]() {
					if (tcpSocket == nullptr)
					{
						qDebug() << "错误 空指针" << __FILE__ << __LINE__;
						return;
					}
					if (tcpSocket->state() != QAbstractSocket::ConnectedState)
					{
						qDebug() << "错误 socket 没有连接" << __FILE__ << __LINE__;
						return;
					}
					tcpSocket->disconnectFromHost();//开始四次挥手断开连接
					});
			}

			QString connectString = "";
			QTextStream text(&connectString);
			text << "客户端  " << address << " " << port << "  接入";
			this->notificationManager->newBubble(connectString);//通知气泡
			qDebug() << connectString;

			//配置连接 有客户端断开
			connect(tcpSocket, &QTcpSocket::disconnected, this, [this, tcpSocket]() {
				if (tcpSocket == nullptr)
				{
					qDebug() << "错误 空指针" << __FILE__ << __LINE__;
					return;
				}
				//在链表中查找
				int index = tcpClientesList.indexOf(tcpSocket);
				if (index == -1)
				{
					qDebug() << "错误 查找不到" << __FILE__ << __LINE__;
					return;
				}
				this->tcpClientesList.removeOne(tcpSocket);//移除链表中对应节点
				ui->clientListWidget->erase(index);//在链表窗口中移除对应窗口
				tcpSocket->deleteLater();//删除

				QString disconnectString = "";
				QTextStream stream(&disconnectString);
				stream << "客户端  " << tcpSocket->peerAddress().toString() << " " << tcpSocket->peerPort() << "  已断开";
				this->notificationManager->newBubble(disconnectString);
				qDebug() << disconnectString;
				});

			//配置连接 展示新连接的客户端发来的数据
			connect(tcpSocket, &QTcpSocket::readyRead, this, [this, tcpSocket]() {
				if (tcpSocket == nullptr)
				{
					qDebug() << "错误 空指针" << __FILE__ << __LINE__;
					return;
				}
				/*qDebug() << "收到了客户端的数据";*/
				QString string;
				QTextStream ts(&string);
				ts << "\n[Tcp client " << tcpSocket->peerAddress().toString() << ' ' << tcpSocket->peerPort() << "]";
				ui->receive_area->appendPlainText(string);
				QByteArray byteArray = tcpSocket->readAll();
				ui->receive_area->showData(byteArray);
				});

			//配置连接 请求发送
			connect(ui->singleSend, &SingleSendWidget::requestToSend, tcpSocket,
				static_cast<qint64(QTcpSocket::*)(const QByteArray & data)>(&QTcpSocket::write));
			connect(ui->multipleSend, &MultipleSendWidget::requestToSend, tcpSocket,
				static_cast<qint64(QTcpSocket::*)(const QByteArray & data)>(&QTcpSocket::write));
			});

	}
	//服务器已经创建
	else
	{
		//断开所有客户端连接
		QList<QTcpSocket*> socketsList = this->tcpClientesList;// 复制一份指针列表（浅拷贝，安全）
		for (auto it = socketsList.begin(); it != socketsList.end(); it++)//遍历指针列表
		{
			QTcpSocket* tcpSocket = *it;
			if (tcpSocket == nullptr)
			{
				qDebug() << "错误 空指针" << __FILE__ << __LINE__;
				continue;
			}
			if (tcpSocket->state() == QAbstractSocket::ConnectedState)
			{
				tcpSocket->disconnectFromHost();
			}
			//会在 tcpSocket 的 disconnected 信号对应的槽函数中清理
		}
		//注意，在清理时会删除链表节点，因此，如果遍历原本的链表会错！！

		//清空客户端表格
		ui->clientListWidget->clear();		


		//服务器正在监听
		if (this->tcpServer->isListening())
		{
			this->tcpServer->close();//停止监听
			this->tcpServer->deleteLater();
			this->tcpServer = nullptr;
			emit this->workingStateChanged(false);
			this->notificationManager->newBubble("服务器停止监听");
			qDebug() << "停止监听";
		}
		else//正常情况下不应该执行到这里
		{
			this->tcpServer->deleteLater();
			this->tcpServer = nullptr;
			qDebug() << "错误 服务器没有监听 " << __FILE__ << __LINE__;
		}
	}

}


void MainWindow::asUdpOperation(void)
{
	if (this->udpSocket == nullptr)
	{
		QHostAddress address = ui->network_settings->getAddress();
		if (address.isNull())
		{
			this->notificationManager->newBubble("地址无效");
			qDebug() << "地址无效" << __FILE__ << __LINE__;
			return;
		}
		uint16_t port = ui->network_settings->getPortValue();
		this->udpSocket = new QUdpSocket(this);//创建UDP套接字
		bool result = this->udpSocket->bind(address, port);//UDP 绑定
		if (!result)
		{
			qDebug() << "UDP 绑定失败" << __FILE__ << __LINE__;
			this->notificationManager->newBubble("UDP 绑定失败");
			this->udpSocket->deleteLater();
			this->udpSocket = nullptr;
		}
		QString message = "";
		QTextStream stream(&message);
		stream << "UDP 绑定成功" << address.toString() << " " << port;
		this->notificationManager->newBubble(message);
		qDebug() << message;


		//配置连接 接收 UDP 套接字数据
		connect(this->udpSocket, &QUdpSocket::readyRead, this, [this]() {
			/*QUdpSocket 是 数据报（Datagram）套接字，不是流式套接字！
			* TCP (QTcpSocket) 是流式的 → 可以用 readAll()、read() 等 QIODevice 方法
			* UDP (QUdpSocket) 是基于数据包（Datagram） 的 → 必须用 readDatagram()
			*/
			// 是否有待读取的数据报
			while (this->udpSocket->hasPendingDatagrams())
			{
				QByteArray data;
				data.resize(this->udpSocket->pendingDatagramSize());
				QHostAddress senderAddress;
				uint16_t senderPort;
				//读取数据，并记录发送者的地址和端口
				this->udpSocket->readDatagram(data.data(), data.count(), &senderAddress, &senderPort);
				QString senderString = QString("[UDP from %1:%2]").arg(senderAddress.toString()).arg(senderPort);
				ui->receive_area->appendPlainText(senderString);
				ui->receive_area->showData(data);
			}
			});

		//配置连接 请求发送 通过 UDP 发送数据
		connect(ui->singleSend, &SingleSendWidget::requestToSend, this->udpSocket, [this](QByteArray data) {
			QString targetAddressString = ui->udpTargetBox->getAddress();
			uint16_t targetPort = ui->udpTargetBox->getPortValue();
			QHostAddress targetAddress(targetAddressString);
			this->udpSocket->writeDatagram(data, targetAddress, targetPort);//UDP 发送数据包
			});
		connect(ui->multipleSend, &MultipleSendWidget::requestToSend, this->udpSocket, [this](QByteArray data) {
			QString targetAddressString = ui->udpTargetBox->getAddress();
			uint16_t targetPort = ui->udpTargetBox->getPortValue();
			QHostAddress targetAddress(targetAddressString);
			this->udpSocket->writeDatagram(data, targetAddress, targetPort);//UDP 发送数据包
			});

		emit this->workingStateChanged(true);
	}
	else
	{
		//UDP 是无连接协议，没有“连接状态”，自然也没有“断开连接”或“解绑”操作。
		this->udpSocket->deleteLater();
		this->udpSocket = nullptr;
		emit this->workingStateChanged(false);
		this->notificationManager->newBubble("UDP 已关闭");
		qDebug() << "UDP 已关闭";
	}
}

void MainWindow::asUdpSendOnlyOperation(void)
{
	if (this->udpSocket_OnlySend == nullptr)
	{
		this->udpSocket_OnlySend = new QUdpSocket(this);//创建UDP套接字

		this->notificationManager->newBubble("UDP 只发送 开始工作");
		qDebug() << "UDP 只发送 开始工作";

		//配置连接 请求发送 通过 UDP 发送数据
		connect(ui->singleSend, &SingleSendWidget::requestToSend, this->udpSocket_OnlySend, [this](QByteArray data) {
			QString targetAddressString = ui->udpTargetBox->getAddress();
			uint16_t targetPort = ui->udpTargetBox->getPortValue();
			QHostAddress targetAddress(targetAddressString);
			this->udpSocket_OnlySend->writeDatagram(data, targetAddress, targetPort);//UDP 发送数据包
			});
		connect(ui->multipleSend, &MultipleSendWidget::requestToSend, this->udpSocket_OnlySend, [this](QByteArray data) {
			QString targetAddressString = ui->udpTargetBox->getAddress();
			uint16_t targetPort = ui->udpTargetBox->getPortValue();
			QHostAddress targetAddress(targetAddressString);
			this->udpSocket_OnlySend->writeDatagram(data, targetAddress, targetPort);//UDP 发送数据包
			});

		emit this->workingStateChanged(true);
	}
	else
	{
		//UDP 是无连接协议，没有“连接状态”，自然也没有“断开连接”或“解绑”操作。
		this->udpSocket_OnlySend->deleteLater();
		this->udpSocket_OnlySend = nullptr;
		emit this->workingStateChanged(false);
		this->notificationManager->newBubble("UDP 只发送 停止工作");
		qDebug() << "UDP 只发送 停止工作";
	}
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

	label_Port = new QLabel(widget);
	label_Port->setText("端口");

	horizontalLayout->addWidget(label_Port);

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