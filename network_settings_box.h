#pragma once

#include <QWidget>
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
#include "sundry.h"

class NetworkSettingsBox : public QGroupBox
{
	Q_OBJECT

public:
	explicit NetworkSettingsBox(QWidget* parent = nullptr);
	~NetworkSettingsBox();

private:	
	QVBoxLayout* verticalLayout;
	QLabel* label_WorkMode;
	AutoWidthCombobox* comboBox_WorkMode;
	QLabel* label_LocalAddress;
	AutoWidthCombobox* comboBox_LocalAddress;
	QLabel* label_LocalPort;
	QSpinBox* spinBox_LocalPort;
	QLabel* label_TargetAddress;
	QLineEdit* lineEdit_TargetAddress;
	QLabel* label_TargetPort;
	QSpinBox* spinBox_TargetPort;
	QWidget* widget;
	QHBoxLayout* horizontalLayout;
	LED_Widget* led;
	QPushButton* button_Refresh;
	ToggleButton* button_Switch;//开关
	ScrollableListWidget* clientListWidget;
		

	/**
	 * @brief 设置 UI
	 */
	void setupUi(void);

public:
	/**
	 * @brief 获取选择的网络协议类型
	 * @param
	 * @return 选择的网络协议类型
	 */
	WorkMode getSelectedMode(void);

	/**
	 * @brief 获取IP地址
	 * @return 选择或输入的IP地址
	 */
	QHostAddress getAddress(void);

	/**
	 * @brief 获取端口号
	 * @return 选择的端口号
	 */
	uint16_t getPortValue(void);

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