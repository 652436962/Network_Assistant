#include "notification_manager.h"



NotificationManager::NotificationManager(QObject* parent, QWidget* widget):QObject(parent)
{
	this->m_widget = widget;
	qDebug() << "通知管理建立";
}

void NotificationManager::newBubble(const QString& str, int duration)
{
	if (this->m_widget == nullptr)
	{
		qDebug() << "错误，没有所属窗口" << __FILE__ << __LINE__;
		return;
	}
	NotificationBubble* bubble = new NotificationBubble(str, duration, this->m_widget);
	this->bubblesList.push_back(bubble);//加入链表
	//配置连接，气泡关闭
	connect(bubble, &NotificationBubble::bubbleColsed, this, &NotificationManager::aBubbleClose);

	//确定位置，准备弹出动画
	int x = this->m_widget->x() + this->m_widget->width() - 8;
	int y = this->m_widget->y() + this->bubblesList.size() * (bubble->height()+8);
	QPoint point(x, y);
	bubble->move(point);
	bubble->movePositionLeft();
	bubble->startTimer();
}

void NotificationManager::aBubbleClose(NotificationBubble* bubble)
{
	std::list<NotificationBubble*>::iterator it_target;
	it_target = std::find(this->bubblesList.begin(), this->bubblesList.end(), bubble);
	if (it_target == this->bubblesList.end())
	{
		qDebug() << "错误，找不到对应气泡" << __FILE__ << __LINE__;
	}
	auto it = it_target++;//目标的后一个
	this->bubblesList.erase(it_target);//在链表中移除目标
	//后面的上移
	for (; it != this->bubblesList.end(); it++)
	{
		(*it)->movePositionUp();
	}
}

