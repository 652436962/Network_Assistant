#pragma once
#include "notification_bubble.h"
#include <list>

/**
 * @brief 通知气泡管理
 */
class NotificationManager : public QObject
{
	Q_OBJECT

private:
	/**
	 * @brief 管理所有气泡的链表
	 */
	std::list<NotificationBubble*> bubblesList;

	/**
	 * @brief 此管理器所属于的窗口
	 */
	QWidget* m_widget = nullptr;

public:
	/**
	 * @brief 构造函数
	 * @param paretn 父对象
	 * @param widget 此管理器所属于的窗口
	 */
	NotificationManager(QObject* parent = nullptr, QWidget* widget = nullptr);

	/**
	 * @brief 新通知气泡
	 * @param str 要展示的消息
	 * @param duration 持续时间 毫秒
	 */
	void newBubble(const QString str="", int duration=5000);

	/**
	 * @brief 某个气泡关闭了
	 * @param bubble 关闭的气泡
	 */
	void aBubbleClose(NotificationBubble* bubble);
};
