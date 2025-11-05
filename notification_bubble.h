#pragma once

#include <QFrame>
#include <QTimer>
#include <QLabel>
#include <QToolButton>

/**
 * @brief 单个通知气泡组件
 *
 * 用于在屏幕右上角显示短暂提示信息，支持自动消失、手动关闭、
 * 鼠标悬停暂停等功能。通常由 NotificationManager 管理。
 */
class NotificationBubble: public QFrame
{
    Q_OBJECT

private:
    QLabel* label_Text;          // 显示文本内容的标签
    QToolButton* toolButton_Close; // 关闭按钮（×）
    QTimer* m_timer;          // 自动消失计时器
    int m_duration;           // 倒计时时长（毫秒）

public:
    /**
     * @brief 构造一个通知气泡
     * @param text 显示的文本内容
     * @param durationMs 自动消失的毫秒数，默认 5000（5秒）
     * @param parent 父窗口，通常为 NotificationManager
     */
    explicit NotificationBubble(const QString& text, int durationMs = 5000, QWidget* parent = nullptr);

    /**
     * @brief 启动自动消失计时器
     *
     * 调用后，气泡将在设定的 durationMs 后自动关闭。
     */
    void startTimer();

    /**
     * @brief 暂停自动消失计时器
     *
     * 通常在鼠标悬停时调用，防止用户阅读时气泡突然消失。
     */
    void pauseTimer();

    /**
     * @brief 恢复自动消失计时器
     *
     * 通常在鼠标离开时调用，继续倒计时。
     */
    void resumeTimer();

signals:
    /**
     * @brief 气泡已过期或被用户关闭，应从管理器中移除
     *
     * 此信号由内部自动触发（超时或点击关闭按钮），外部不应手动发射。
     */
    void expired();

private:
    /**
     * @brief 计时器超时槽函数
     *
     * 触发 expired() 信号并安排自身删除。
     */
    void onTimeout();

};
