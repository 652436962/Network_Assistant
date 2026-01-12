#pragma once

#include <QMainWindow>
#include <QTableWidget>

#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include "single_send_widget.h"
#include "multiple_send_widget.h"
#include "notification_manager.h"
#include "target_box.h"
#include "scrollable_list_widget.h"


#include "global.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
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
	NotificationManager* notificationManager;//通知管理
private:
	/**
	 * @brief 创建对话框展示本机网络信息
	 */
	void showLocalIPConfig(void);


	/**
	* 工作模式 TCP 客户端 的相关功能
	*/
private:
	/**
	 * @brief 作为客户端使用时的 TCP 套接字
	 */
	QTcpSocket* clientTcpSocket = nullptr;

	/**
	 * @brief 作为TCP客户端工作
	 */
	void asTcpClientOperation(void);


	/**
	 * 工作模式 TCP 服务器 的相关功能
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
	QList<QTcpSocket*> tcpClientesList;

	/**
	 * @brief 作为 TCP 服务器 工作
	 * @param
	 */
	void asTcpServerOperation(void);


	/**
	 * 工作模式 UDP 的相关功能
	 */
private:
	/**
	 * @brief UPD Socket
	 */
	QUdpSocket* udpSocket = nullptr;
	/**
	 * @brief 作为 UDP 工作
	 */
	void asUdpOperation(void);

/**
 * 工作模式 UDP 只发送 的相关功能 
 */
private:
	QUdpSocket* udpSocket_OnlySend = nullptr;
	/**
	 * @brief 作为 只发送的UDP 工作
	 */
	void asUdpSendOnlyOperation(void);

signals:
	/**
	 * @brief 工作状态改变
	 * @param 是否正在工作
	 * @note Qt 信号
	 */
	void workingStateChanged(bool state);
};

