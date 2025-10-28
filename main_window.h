#pragma once

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "single_send_widget.h"


QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    SingleSendWidget* singleSend = nullptr;//单项发送区
public:
    /**
     * @brief 创建对话框展示本机网络信息
     */
    void showLocalIPConfig(void);

private:
    QTcpServer* tcpServer = nullptr;//TCP 服务器 负责“监听”和“接受连接”

    QTcpSocket* tcpSocket = nullptr; // TCP 通信的 socket 负责“实际通信”
    /**
     * @brief 有客户端成功接入
     * @param  
     */
    void do_TCP_newConnection(void);
    
    /**
     * @brief TCP 客户端断开连接
     * @param  
     */
    void do_TCP_clientDisconnected(void);

    /**
     * @brief TCP 客户端可以读取
     * @param  
     */
    void do_TCP_clientReadyRead(void);
    

public:
    /**
     * @brief 网络设置中的按钮被按下
     * @param  
     */
    void do_clicked(void);

signals:
    /**
     * @brief 连接状态改变
     * @note Qt 信号
     */
    void connectionStatusChanged(bool state);
};
