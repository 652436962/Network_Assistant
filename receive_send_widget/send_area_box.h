#pragma once

#include <QGroupBox>
#include <QTimer>


#include "editable_tabwidget.h"
#include "scrollable_list_widget.h"

#include "global.h"
#include "sundry_qt.h"


#include "single_send_widget.h"
#include "multiple_send_widget.h"

namespace Ui {
	class SendAreaBox;
}

/**
 * @brief 发送区
 */
class SendAreaBox : public QGroupBox
{
	Q_OBJECT
private:
	Ui::SendAreaBox* ui;


public:
	/**
	 * @brief 构造函数
	 * @param parent 父对象
	 */
	SendAreaBox(QWidget* parent);

private:
	SendMode mode = SendMode::Single;//工作模式
	bool text = true;//要发送的是否是文本字符串
	bool append = true;//是否追加内容
	QByteArray appendData = QByteArray("\r\n", 2);//要追加内容
	bool allowSending = false;//是否允许发送

	QTimer* timer;//自动发送定时器
public:
	/**
	 * @brief 切换发送模式
	 * @param m 发送模式枚举
	 */
	void switchMode(SendMode m);

private:
	/**
	 * @brief 根据选项获取要发送的内容
	 * @param str 原本的字符串
	 * @return 要发送的内容
	 */
	QByteArray getSentContent(QString str);
public:
	/**
	 * @brief 要发送的是否是文本字符串
	 * @param t true 是 false 否
	 */
	void setText(bool t);
	/**
	 * @brief 设置追加内容
	 * @param a true 追加 false 不追加
	 * @param data 要追加的数据
	 */
	void setAppend(bool a, QByteArray data);
	/**
	 * @brief 设置是否自动发送
	 * @param a true 是 false 否
	 */
	void setAutoSend(bool a);
	/**
	 * @brief 获取是否正在自动发送
	 * @return 是否正在自动发送
	 */
	bool isAutoSend(void) const;

	/**
	 * @brief 设置自动发送周期
	 * @param msec 自动发送周期毫秒
	 */
	void setSendCycle(int msec);

	/**
	 * @brief 是否允许发送
	 * @param a 是否
	 */
	void setAllowSending(bool a);

signals:
	/**
	 * @brief 请求发送
	 * @param data 要发送的数据
	 * @note Qt信号
	 */
	void requestToSend(QByteArray data);
signals:
	/**
	 * @brief 请求通知
	 * @param notification 通知文本
	 * @note Qt 信号
	 */
	void requestToNotification(QString notification);
};


