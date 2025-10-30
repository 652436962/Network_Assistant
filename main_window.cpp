#include "main_window.h"

#include "ui_main_window.h"

#include "led_widget.h"

#include <QDialog>
#include <QHostInfo>

#include <QTableWidget>//表格

#include <QSysInfo>//系统信息
#include <QNetworkInterface>
#include <QVBoxLayout>

#include "sundry_qt.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);

    
    

    //配置连接 展示主机信息
    connect(ui->action_Info, &QAction::triggered, this, &MainWindow::showLocalIPConfig);

    //左侧窗口相关配置
    
    //配置连接 按钮被点击
    connect(ui->network_settings, &NetworkSettingsBox::clicked, this, &MainWindow::do_clicked);

    //配置连接 
    connect(this, &MainWindow::connectionStatusChanged, ui->network_settings, &NetworkSettingsBox::changeUI);

    //配置连接 有新的客户端连接
    connect(this->tcpServer, &QTcpServer::newConnection, this, &MainWindow::do_TCP_newConnection);

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
    if (tcpSocket != nullptr)
    {
        if (tcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            tcpSocket->disconnectFromHost();//断开连接
        }
    }
    if (tcpServer != nullptr)
    {
        if (tcpServer->isListening())
        {
            tcpServer->close();//停止网络监听
        }
    }
    if (this->clientTcpSocket != nullptr)
    {
        if (clientTcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            clientTcpSocket->disconnectFromHost();//断开连接
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

    addRow("操作系统", QSysInfo::prettyProductName(),"");
    addRow("操作系统内核", QSysInfo::kernelType(),"");
    addRow("内核版本", QSysInfo::kernelVersion(),"");
    addRow(" CPU 架构", QSysInfo::currentCpuArchitecture(),"");
    addRow("本机名", QSysInfo::machineHostName(),"");// 获取主机信息
    

    // 获取本机所有网络接口（网卡）
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const auto& it_interface : interfaces)
    {
        // 跳过未激活的网卡（比如没插网线、Wi-Fi 关闭） 或 回环地址
        if (!it_interface.flags().testFlag(QNetworkInterface::IsUp) || it_interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            continue;
        }

        qDebug() << "网卡名称" << it_interface.name() <<"可读名称"<< it_interface.humanReadableName();        
        qDebug() << "硬件地址(MAC)" << it_interface.hardwareAddress();
        qDebug() << "接口类型" << it_interface.type();
        qDebug() << "标志" << it_interface.flags();
        addRow("网卡名称", it_interface.humanReadableName(),"");
        addRow("", it_interface.name(),"");
        addRow("硬件地址(MAC)", it_interface.hardwareAddress(),"");
        addRow("接口类型", interfaceTypeToString(it_interface.type()),"");

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
            else if(ip.protocol()==QAbstractSocket::IPv6Protocol)
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

void MainWindow::do_TCP_newConnection(void)
{
    this->tcpSocket = this->tcpServer->nextPendingConnection();//创建与客户端通信的 socket

    ui->receive_area->appendPlainText("客户端接入");
    ui->receive_area->appendPlainText("地址 " + tcpSocket->peerAddress().toString());
    ui->receive_area->appendPlainText("端口 " + QString::number(tcpSocket->peerPort()));
    qDebug() << "有客户端接入";
    qDebug() << "地址 " << tcpSocket->peerAddress();
    qDebug() << "端口 " << tcpSocket->peerPort();

    //配置连接 客户端断开
    connect(this->tcpSocket, &QTcpSocket::disconnected, this, &MainWindow::do_TCP_clientDisconnected);

    //配置连接 展示客户端发来的数据
    connect(this->tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::do_TCP_clientReadyRead);
}



void MainWindow::do_TCP_clientDisconnected(void)
{
    ui->receive_area->appendPlainText("客户端断开");
    ui->receive_area->appendPlainText("地址 " + tcpSocket->peerAddress().toString());
    ui->receive_area->appendPlainText("端口 " + QString::number(tcpSocket->peerPort()) + '\n');
    qDebug() << "客户端断开";
    qDebug() << "地址 " << tcpSocket->peerAddress();
    qDebug() << "端口 " << tcpSocket->peerPort();
    this->tcpSocket->deleteLater();
    this->tcpSocket = nullptr;
}

void MainWindow::do_TCP_clientReadyRead(void)
{
    qDebug() << "收到了客户端的数据";
    QByteArray byteArray = tcpSocket->readAll();
    ui->receive_area->showData(byteArray);    
}

void MainWindow::do_clicked(void)
{
    ProtocolType type = ui->network_settings->getProtocolType();
    QString address = ui->network_settings->getAddress();
    uint16_t port = ui->network_settings->getPortValue();
    /*qDebug() << "选择的内容";
    qDebug() << "type " << getProtocolTypeString(type);
    qDebug() << "address " << address;
    qDebug() << "port" << port;*/
    if (type == ProtocolType::TCP_Server)//TCP 服务器
    {
        if (tcpServer->isListening()) 
        {
            if (tcpSocket != nullptr)
            {
                if (tcpSocket->state() == QAbstractSocket::ConnectedState)
                {
                    tcpSocket->disconnectFromHost();
                }
            }
            tcpServer->close();//停止监听
            emit this->connectionStatusChanged(false);
            qDebug() << "停止监听";            
        }
        else
        {
            QHostAddress hostAddress(address);
            bool result = tcpServer->listen(hostAddress, port); //开始监听
            if (result)
            {
                emit this->connectionStatusChanged(true);
                qDebug() << "开始监听  地址" << hostAddress << " 端口 " << port;                
            }
            else
            {
                qDebug() << "监听启动失败！";
            }

            
        }
        
    }
    else if (type == ProtocolType::TCP_Client)
    {
        this->AsTcpClientOperation();
    }
    else if (type == ProtocolType::UDP)
    {

    }

}

void MainWindow::AsTcpClientOperation(void)
{  
    if (this->clientTcpSocket == nullptr)//建立连接
    {
        this->clientTcpSocket = new QTcpSocket(this);//创建 socket 变量
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
            ui->receive_area->appendPlainText("已连接到服务器");
            ui->receive_area->appendPlainText("地址 " + clientTcpSocket->peerAddress().toString() + " 端口 " + QString::number(clientTcpSocket->peerPort()) + '\n');
            emit this->connectionStatusChanged(true);
            qDebug() << "已连接到服务器";
            qDebug() << "地址 " << clientTcpSocket->peerAddress() << " 端口 " << clientTcpSocket->peerPort();
            });
        //发生错误
        connect(this->clientTcpSocket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError error) {
            qDebug() << "出现错误 " << error;
            });
        //与服务器断开了连接
        connect(this->clientTcpSocket, &QTcpSocket::disconnected, this, [this]() {
            if (clientTcpSocket == nullptr)
            {
                qDebug() << "错误 " << __FILE__ << __LINE__;
                return;
            }
            ui->receive_area->appendPlainText("与服务器断开了连接");
            clientTcpSocket->deleteLater();
            clientTcpSocket = nullptr;
            emit this->connectionStatusChanged(false);
            qDebug() << "与服务器断开了连接";
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
        //配置连接 单项发送
        connect(this->singleSend, &SingleSendWidget::requestToSend, this, [this](QByteArray byteArray) {
            if (clientTcpSocket == nullptr)
            {
                qDebug() << "错误 " << __FILE__ << __LINE__;
                return;
            }
            this->clientTcpSocket->write(byteArray);
            });
    }
    else//断开连接
    {
        if (clientTcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            this->clientTcpSocket->disconnectFromHost();//启动4次挥手，断开连接
            
        }
        else
        {
            qDebug() << "错误 " << __FILE__ << __LINE__;
        }
    }
    

}

