#include "main_window.h"

#include "ui_main_window.h"

#include "led_widget.h"

#include <QDialog>
#include <QHostInfo>

#include <QTableWidget>//表格

#include <QSysInfo>//系统信息
#include <QNetworkInterface>
#include <QVBoxLayout>
#include <QMessageBox>

#include "sundry_qt.h"


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);//配置UI


	this->notificationManager = new NotificationManager(this, this);//通知气泡管理
	this->notificationManager->newBubble("欢迎使用");

	//配置连接 展示主机信息
	connect(ui->action_Info, &QAction::triggered, this, &MainWindow::showLocalIPConfig);

	//左侧窗口相关配置

	//配置连接 按钮被点击
	connect(ui->network_settings, &NetworkSettingsBox::clicked, this, &MainWindow::do_clicked);

	//配置连接 网络设置改变 UI
	connect(this, &MainWindow::connectionStatusChanged, ui->network_settings, &NetworkSettingsBox::changeUI);


	//配置连接 接收设置 -> 接收区 各种链接
	{
		connect(ui->receive_settings, &ReceiveSettingsBox::clear, ui->receive_area, &ReceiveWidget::clear);
		connect(ui->receive_settings, &ReceiveSettingsBox::setText, ui->receive_area, &ReceiveWidget::setText);
		connect(ui->receive_settings, &ReceiveSettingsBox::setStopDispalying, ui->receive_area, &ReceiveWidget::setStopDisplaying);
		connect(ui->receive_settings, &ReceiveSettingsBox::setTimestamp, ui->receive_area, &ReceiveWidget::setTimestamp);
	}


	//右侧窗口相关配置

	QVBoxLayout* verticalLayout = qobject_cast<QVBoxLayout*>(ui->widget_Right->layout());
	if (verticalLayout == nullptr)
	{
		qDebug() << "错误" << __FILE__ << __LINE__;
	}
	this->singleSend = new SingleSendWidget(this);//创建单项发送窗口
	verticalLayout->addWidget(singleSend);//添加到布局

	//配置连接 发送设置 -> 单项发送区
	{
		connect(ui->send_settings, &SendSettingsBox::setText, singleSend, &SingleSendWidget::setText);
		connect(ui->send_settings, &SendSettingsBox::setAppend, singleSend, &SingleSendWidget::setAppend);
		connect(ui->send_settings, &SendSettingsBox::setAutoSend, singleSend, &SingleSendWidget::setAutoSend);
	}


	qDebug() << "主窗口建立";
}

MainWindow::~MainWindow()
{
	//关闭 Tcp 服务器	
	//断开所有客户端连接
	std::list<QTcpSocket*> socketsList = this->tcpSocketsList;// 复制一份指针列表（浅拷贝，安全）
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
	addRow(" CPU 架构", QSysInfo::currentCpuArchitecture(), "");
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
}



void MainWindow::AsTcpServerOperation(void)
{	
	//服务器还没有创建
	if (this->tcpServer == nullptr)
	{
		if (this->tcpSocketsList.empty() != true)
		{
			qDebug() << "错误 服务器创建前客户端链表非空" << __FILE__ << __LINE__;
		}
		this->tcpServer = new QTcpServer(this);//创建TCP服务器
		this->tcpServer->setObjectName("TCP Server");

		QString address = ui->network_settings->getAddress();//获取地址
		uint16_t port = ui->network_settings->getPortValue();//获取端口
		QHostAddress hostAddress(address);
		bool result = tcpServer->listen(hostAddress, port); //开始监听
		if (result)
		{
			emit this->connectionStatusChanged(true);
			this->notificationManager->newBubble("TCP服务器开始监听");
			qDebug() << "开始监听  地址" << hostAddress << " 端口 " << port;
		}
		else
		{
			this->tcpServer->deleteLater();
			this->tcpServer = nullptr;
			this->notificationManager->newBubble("TCP服务器监听启动失败");
			qDebug() << "监听启动失败！";
		}

		//创建客户端展示表格
		this->clientTable = new QTableWidget(this);
		QVBoxLayout* layout = static_cast<QVBoxLayout*>(ui->widget_Left->layout());
		layout->insertWidget(1, this->clientTable);


		//配置连接 有新的客户端连接
		connect(this->tcpServer, &QTcpServer::newConnection, this, [this]() {
			/*创建与客户端通信的 socket
			* 自 Qt 6.4 起，创建的 socket 默认父对象为 对应的 QTcpServer 实例
			*/
			QTcpSocket* tcpSocket = this->tcpServer->nextPendingConnection();
			qDebug() << tcpSocket->parent()->objectName();			
			tcpSocket->setParent(this);//设置父对象，由我管理它
			qDebug() << "改变tcpSocket父对象";
			qDebug() << tcpSocket->parent()->objectName();


			this->tcpSocketsList.push_back(tcpSocket);//加入到队列末尾
			std::list<QTcpSocket*>::iterator it = --this->tcpSocketsList.end();//迭代器指向对应节点

			QString connectString = "";
			QTextStream text(&connectString);
			text << "客户端  " << tcpSocket->peerAddress().toString()<<" " << tcpSocket->peerPort() << "  接入";
			this->notificationManager->newBubble(connectString);
			qDebug() << connectString;
			qDebug() << "当前连接客户端总数" << this->tcpSocketsList.size();

			//配置连接 有客户端断开
			connect(tcpSocket, &QTcpSocket::disconnected, this, [this, it]() {
				if (this->tcpSocketsList.empty() == true)
				{
					qDebug() << "错误 链表为空" << __FILE__ << __LINE__;
				}
				QTcpSocket* tcpSocket = *it;
				if (tcpSocket == nullptr)
				{
					qDebug() << "错误 空指针" << __FILE__ << __LINE__;
					return;
				}
				QString disconnectString = "";
				QTextStream stream(&disconnectString);
				stream << "客户端  " << tcpSocket->peerAddress().toString() << " " << tcpSocket->peerPort() << "  已断开";
				this->notificationManager->newBubble(disconnectString);
				qDebug() << disconnectString;
				tcpSocket->deleteLater();
				tcpSocket = nullptr;
				this->tcpSocketsList.erase(it);//移除链表中对应节点
				qDebug() << "当前连接客户端总数" << this->tcpSocketsList.size();
				});

			//配置连接 展示新连接的客户端发来的数据
			connect(tcpSocket, &QTcpSocket::readyRead, this, [this, it]() {
				QTcpSocket* tcpSocket = *it;
				if (tcpSocket == nullptr)
				{
					qDebug() << "错误 空指针" << __FILE__ << __LINE__;
					return;
				}
				qDebug() << "收到了客户端的数据";
				QString string;
				QTextStream ts(&string);
				ts << "\n[Tcp client " << tcpSocket->peerAddress().toString() << ' ' << tcpSocket->peerPort() << "]\n";
				ui->receive_area->insertPlainText(string);
				QByteArray byteArray = tcpSocket->readAll();
				ui->receive_area->showData(byteArray);
				});

			//配置连接 向新连接的客户端发送数据
			connect(this->singleSend, &SingleSendWidget::requestToSend, tcpSocket,
				static_cast<qint64(QTcpSocket::*)(const QByteArray & data)>(&QTcpSocket::write));

			});
		
	}
	//服务器已经创建
	else
	{
		//断开所有客户端连接
		std::list<QTcpSocket*> socketsList = this->tcpSocketsList;// 复制一份指针列表（浅拷贝，安全）
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
		
		this->clientTable->deleteLater();//删除客户端表格
		
		//服务器正在监听
		if (this->tcpServer->isListening())
		{
			this->tcpServer->close();//停止监听
			this->tcpServer->deleteLater();
			this->tcpServer = nullptr;
			emit this->connectionStatusChanged(false);
			this->notificationManager->newBubble("服务器停止监听");
			qDebug() << "停止监听";
		}
		else//正常情况下不应该执行到这里
		{
			this->tcpServer->deleteLater();
			this->tcpServer = nullptr;
			qDebug() << "错误 服务器没有监听 " << __FILE__ << __LINE__ ;
		}
	}

}

void MainWindow::do_clicked(void)
{
	WorkMode mode = ui->network_settings->getSelectedMode();
	/*qDebug() << "选择的内容";
	qDebug() << "type " << getProtocolTypeString(type);
	qDebug() << "address " << address;
	qDebug() << "port" << port;*/
	if (mode == WorkMode::TCP_Server)//作为 TCP 服务器工作
	{
		this->AsTcpServerOperation();
	}
	else if (mode == WorkMode::TCP_Client)//作为 TCP 客户端工作
	{
		this->AsTcpClientOperation();
	}
	else if (mode == WorkMode::UDP)
	{

	}

}

void MainWindow::AsTcpClientOperation(void)
{
	if (this->clientTcpSocket == nullptr)//客户端 TcpSocket 未创建
	{
		this->clientTcpSocket = new QTcpSocket(this);//创建 TcpSocket 变量
		QString address = ui->network_settings->getAddress();//获取 IP 地址
		uint16_t port = ui->network_settings->getPortValue();//获取端口
		this->clientTcpSocket->connectToHost(address, port);//尝试连接服务器

		/*配置相关链接*/
		//与服务器建立了连接
		connect(this->clientTcpSocket, &QTcpSocket::connected, this, [this]() {
			if (clientTcpSocket == nullptr)
			{
				qDebug() << "错误 " << __FILE__ << __LINE__;
				return;
			}
			QString connectString = "";
			QTextStream connectStream(&connectString);
			connectStream << "已连接到服务器  " << clientTcpSocket->peerAddress().toString() << " " << clientTcpSocket->peerPort();
			this->notificationManager->newBubble(connectString);
			emit this->connectionStatusChanged(true);
			qDebug() << connectString;
			
			});
		//与服务器断开了连接
		connect(this->clientTcpSocket, &QTcpSocket::disconnected, this, [this]() {
			if (clientTcpSocket == nullptr)
			{
				qDebug() << "错误 " << __FILE__ << __LINE__;
				return;
			}
			QString disconnectString = "";
			QTextStream disconnectStream(&disconnectString);
			disconnectStream << "已断开与服务器  " << clientTcpSocket->peerAddress().toString() << " " << clientTcpSocket->peerPort()<<"  的连接";
			this->notificationManager->newBubble(disconnectString);
			clientTcpSocket->deleteLater();//删除 Socket
			clientTcpSocket = nullptr;
			emit this->connectionStatusChanged(false);
			qDebug() << disconnectString;
			});
		//发生错误
		connect(this->clientTcpSocket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError error) {
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
		connect(this->clientTcpSocket, &QTcpSocket::readyRead, this, [this]() {
			if (clientTcpSocket == nullptr)
			{
				qDebug() << "错误 " << __FILE__ << __LINE__;
				return;
			}
			QByteArray byteArray = clientTcpSocket->readAll();
			ui->receive_area->showData(byteArray);//在接收区中展示数据
			});
		////配置连接 单项发送
		// 这里代码有问题，this->singleSend this 都是长期存在，不会自动disconnect，因此每次执行都会重复连接
		//connect(this->singleSend, &SingleSendWidget::requestToSend, this, [this](QByteArray byteArray) {
		//    if (clientTcpSocket == nullptr)
		//    {
		//        qDebug() << "错误 " << __FILE__ << __LINE__;
		//        return;
		//    }
		//    qDebug() << "客户端发送 " << byteArray;
		//    this->clientTcpSocket->write(byteArray);
		//    });
		//配置连接 单项发送
		connect(this->singleSend, &SingleSendWidget::requestToSend, this->clientTcpSocket,
			static_cast<qint64(QTcpSocket::*)(const QByteArray& data)>(&QTcpSocket::write));
	}
	else//客户端 TcpSocket 已创建
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

