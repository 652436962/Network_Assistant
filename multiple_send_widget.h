#pragma once

#include <QWidget>
#include <QTimer>
#include <QTableWidget>

#include "global.h"
#include "sundry_qt.h"

namespace Ui {
class MultipleSendWidget;
}

class MultipleSendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleSendWidget(QWidget *parent = nullptr);
    ~MultipleSendWidget();

private:
    Ui::MultipleSendWidget *ui;
private:
	bool text = true;//要发送的是否是文本字符串
	bool append = true;//是否追加内容
	QByteArray appendData = QByteArray("\r\n", 2);//要追加内容
	QTimer* timer;//自动发送定时器
	int currentRow = 0;//自动发送的当前行号
	bool allowSending = false;//是否允许发送
private:
	/**
	 * @brief 根据选项获取要发送的内容
	 * @param dataString 界面中的字符串
	 * @return 要发送的内容
	 */
	QByteArray getSentContent(QString dataString);
	/**
	 * @brief 导入.csv表格文件
	 * @param fileName 文件完整路径
	 */
	void ImportCsvFile(QString fileName);
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
	 * @brief 是否正在自动发送
	 * @return 是否正在自动发送
	 */
	bool isAutoSend(void) const;
	/**
	 * @brief 设置自动发送周期
	 * @param mesc 周期 毫秒
	 */
	void setSendCycle(int mesc);
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


