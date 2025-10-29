#pragma once

#include <QWidget>

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
signals:
	/**
	 * @brief 请求发送
	 * @param data 要发送的数据
	 * @note Qt信号
	 */
	void requestToSend(QByteArray data);
};


