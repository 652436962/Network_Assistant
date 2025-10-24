#pragma once

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


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
public:
    /**
     * @brief 创建对话框展示本机网络信息
     */
    void showLocalIPConfig(void);

private:
    QTcpServer* tcpServer = nullptr;//TCP 服务器
public:
    void do_TCP_newConnection(void);

    QTcpSocket* tcpSocket = nullptr; // TCP 通信的 socket

public:
    void do_connection(void);

signals:
    /**
     * @brief 连接状态改变
     * @note Qt 信号
     */
    void connectionStatusChanged(bool state);
};
