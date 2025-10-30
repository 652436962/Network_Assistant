#pragma once

#include <QWidget>
#include <QByteArray>
#include "sundry.h"

namespace Ui {
	class SingleSendWidget;
}

class SingleSendWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SingleSendWidget(QWidget* parent = nullptr);
	~SingleSendWidget();

private:
	Ui::SingleSendWidget* ui;
private:
	bool text = true;//要发送的是否是文本字符串
	EncodingEnum encoding = EncodingEnum::UTF8;//要发送的文本编码
	bool append = true;//是否追加内容
	QByteArray appendData = QByteArray("\r\n", 2);//要追加内容
	bool autoSend = false;//是否自动发送
	int autoCycle = 65535;//自动发送周期
public:
	/**
	 * @brief 要发送的是否是文本字符串
	 * @param t true 是 false 否
	 */
	void setText(bool t);
	/**
	 * @brief 要发送的文本编码
	 * @param e 文本编码
	 */
	void setEncoding(EncodingEnum e);
	/**
	 * @brief 设置追加内容
	 * @param a true 追加 false 不追加
	 * @param data 要追加的数据
	 */
	void setAppend(bool a, QByteArray data);
	/**
	 * @brief 设置是否自动发送
	 * @param a true 是 false 否
	 * @param c 自动发送周期
	 */
	void setAutoSend(bool a, int c);
signals:
	/**
	 * @brief 请求发送
	 * @param data 要发送的数据
	 * @note Qt信号
	 */
	void requestToSend(QByteArray data);
};


