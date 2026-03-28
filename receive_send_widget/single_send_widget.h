#pragma once

#include <QWidget>

namespace Ui {
	class SingleSendWidget;
}

/**
 * @brief 单项发送窗口
 */
class SingleSendWidget : public QWidget
{
	Q_OBJECT
private:
	Ui::SingleSendWidget* ui;
//private:
//	QGridLayout* gridLayout;
//	QPlainTextEdit* plainTextEdit;
//	QSpacerItem* horizontalSpacer;
//	QPushButton* pushButton_Send;
//	QPushButton* pushButton_Clear;
//
//	void setupUi();
public:
	explicit SingleSendWidget(QWidget* parent = nullptr);
	~SingleSendWidget();
private:
	bool allowSending = false;//是否允许发送
public:
	/**
	 * @brief 是否允许发送
	 * @param a 是否
	 */
	void setAllowSending(bool a);

	/**
	 * @brief 获取用户输入的字符串
	 * @return 用户输入的字符串
	 * @note 用于自动发送
	 */
	QString getUserString();

signals:
	/**
	 * @brief 发送信号
	 * @param str 用户输入的字符串
	 * @note Qt信号
	 */
	void signal_Send(QString str);
};

