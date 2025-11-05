#pragma once

#include <QWidget>
#include <QList>
#include <QEnterEvent>
#include <QVBoxLayout>
#include "notification_bubble.h"


/**
 * @brief 全局通知气泡管理器
 *
 * 负责在屏幕右上角统一管理多个 NotificationBubble 实例。
 * 采用单例模式，确保整个应用只有一个通知区域。
 * 支持堆叠显示、自动布局调整、悬停暂停等功能。
 */
class NotificationManager : public QWidget
{
    Q_OBJECT
private:
    QList<NotificationBubble*> bubblesList;// 当前显示的所有气泡列表
    QVBoxLayout* m_layout;                // 垂直布局

public:
    /**
     * @brief 私有构造函数（单例模式）
     * @param parent 父窗口
     */
    explicit NotificationManager(QWidget* parent = nullptr);

    /**
     * @brief 从管理器中移除一个气泡
     * @param bubble 要移除的气泡指针
     *
     * 调整布局并释放资源，通常由 expired() 信号触发。
     */
    void removeBubble(NotificationBubble* bubble);

    /**
     * @brief 显示一条新通知
     * @param text 通知文本内容
     * @param durationMs 自动消失时间（毫秒），默认 5000
     *
     * 新通知将显示在现有通知的上方，5秒后自动消失，
     * 或用户点击关闭按钮提前消失。
     */
    void showNotification(const QString& text, int durationMs = 5000);

protected:
    /**
     * @brief 鼠标进入通知区域事件
     *
     * 暂停所有气泡的倒计时，防止用户阅读时消失。
     */
    void enterEvent(QEnterEvent* event) override;

    /**
     * @brief 鼠标离开通知区域事件
     *
     * 恢复所有气泡的倒计时。
     */
    void leaveEvent(QEvent* event) override;
};
