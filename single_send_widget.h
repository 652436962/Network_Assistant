#pragma once

#include <QWidget>

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

signals:
	/**
	 * @brief 请求发送
	 * @param data 要传递的字符串
	 * @note Qt信号
	 */
	void requestToSend(QString data);
};


