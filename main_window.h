#pragma once

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "single_send_widget.h"
#include "multiple_send_widget.h"
#include <list>


QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    MainWindow(QWidget* parent = nullptr);

    /**
     * @brief 主窗口析构
     */
    ~MainWindow();

private:
    Ui::MainWindow* ui;

private:
    SingleSendWidget* singleSend = nullptr;//单项发送区
    MultipleSendWidget* multipleSend = nullptr;//多项发送区
private:
    /**
     * @brief 创建对话框展示本机网络信息
     */
    void showLocalIPConfig(void);

private:
    /**
     * @brief 网络设置中的按钮被按下
     * @param
     */
    void do_clicked(void);

/**
 * 作为 TCP 服务器时的相关功能
 */
private:
    /**
     * @brief TCP 服务器 负责“监听”和“接受连接”
     * @note 内部有个socket负责监听
     */
    QTcpServer* tcpServer = nullptr;
    /**
     * @brief 所有连接到的客户端
     * @note TCP 通信的 socket 负责“实际通信”
     */
    std::list<QTcpSocket*> tcpSocketsList;
    /*QTcpSocket* tcpSocket = nullptr;*/
     
    /**
     * @brief 作为 TCP 服务器 工作
     * @param  
     */
    void AsTcpServerOperation(void);


/**
 * 作为 TCP 客户端时的相关功能 
 */
private:
    /**
     * @brief 作为客户端使用时的 TCP 套接字
     */
    QTcpSocket* clientTcpSocket=nullptr;

    /**
     * @brief 作为TCP客户端工作
     */
    void AsTcpClientOperation(void);


signals:
    /**
     * @brief 连接状态改变
     * @note Qt 信号
     */
    void connectionStatusChanged(bool state);
};
