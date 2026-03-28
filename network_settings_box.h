#pragma once


#include <QGroupBox>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

#include <QHostAddress>

#include "led_widget.h"
#include "toggle_button.h"
#include "auto_width_combobox.h"
#include "scrollable_list_widget.h"

#include "global.h"
#include "sundry_qt.h"

class ClientWidget;

namespace Ui {
	class NetworkSettingsBox;
}

class NetworkSettingsBox : public QGroupBox
{
	Q_OBJECT

public:
	explicit NetworkSettingsBox(QWidget* parent = nullptr);
	~NetworkSettingsBox();
private:
	Ui::NetworkSettingsBox* ui;


public:
	/**
	 * @brief 获取选择的工作模式
	 * @return 选择的工作模式
	 */
	WorkMode getSelectedMode(void) const;

	/**
	 * @brief 获取本地IP地址
	 * @return 选择的本地IP地址
	 * @note 用于 TCP 服务器 和 UDP 收发
	 */
	QHostAddress getLocalAddress(void) const;

	/**
	 * @brief 获取本地端口号
	 * @return 选择的本地端口号
	 */
	uint16_t getLocalPort(void) const;

	/**
	 * @brief 获取目标IP地址
	 * @return 目标IP地址
	 */
	QHostAddress getTargetAddress(void) const;
	/**
	 * @brief 获取目标端口号
	 * @return 目标端口号
	 */
	uint16_t getTargetPort(void) const;

private:
	bool networkActive = false;//是否正在进行网络活动
private:
	/**
	 * @brief 根据选项改变 UI
	 */
	void changeUiAccordingOption(void);

	/**
	 * @brief 获取本地所有可用 IP 地址并刷新下拉框
	 */
	void refreshLocalAddress(void);
public:
	/**
	 * @brief 根据网络的连接情况改变UI
	 * @param state 是否正在进行网络活动
	 */
	void changeUiAccordingState(bool state);

	/**
	 * @brief 在TCP客户端展示窗口中添加
	 * @param ip IP地址
	 * @param port 端口
	 * @return 对应窗口
	 * @note 用于TCP服务器
	 */
	ClientWidget* push_backClientLine(QString ip, uint16_t port);
	/**
	 * @brief 在TCP客户端展示窗口中移除
	 * @param pos 索引
	 * @note 用于TCP服务器
	 */
	void eraseClientLine(int pos);
	/**
	 * @brief 清除所有客户端行窗口
	 */
	void clearClientLines();
signals:
	/**
	 * @brief 请求工作
	 * @note Qt 信号
	 */
	void requestWork(WorkMode mode);
signals:
	/**
	 * @brief 模式选项改变
	 * @param 工作模式
	 * @note Qt 信号
	 */
	void modeOptionChanged(WorkMode mode);

};



class ClientesTitle :public QWidget
{
	Q_OBJECT
private:
	QVBoxLayout* verticalLayout;
	QWidget* widget_2;
	QHBoxLayout* horizontalLayout_2;
	QSpacerItem* horizontalSpacer_00;
	QLabel* label_Title;
	QSpacerItem* horizontalSpacer_01;
	QWidget* widget;
	QHBoxLayout* horizontalLayout;
	QSpacerItem* horizontalSpacer_10;
	QLabel* label_IP;
	QSpacerItem* horizontalSpacer_11;
	QLabel* label_LocalPort;
	QSpacerItem* horizontalSpacer_12;
	QLabel* label_Disconnect;

	void setupUi(void);
public:
	ClientesTitle(QWidget* parent = nullptr);
};

class ClientWidget :public QWidget
{
	Q_OBJECT
private:
	QHBoxLayout* horizontalLayout;
	QLineEdit* lineEdit_IP;
	QLineEdit* lineEdit_Port;
	QPushButton* pushButton;

	void setupUi();
public:
	/**
	 * @brief 构造函数
	 * @param parent 父对象
	 * @param ip IP字符串
	 * @param port 端口字符串
	 */
	ClientWidget(QWidget* parent = nullptr, QString ip = "", QString port = "");

	void setIP(const QString& ip);
	void setPort(const QString& port);
signals:
	void signal_Disconnect(void);
};