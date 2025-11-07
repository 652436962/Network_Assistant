#pragma once

#include <QFrame>
#include <QTimer>
#include <QLabel>
#include <QToolButton>
#include <QPropertyAnimation>

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
    QToolButton* toolButton_Close; // 关闭按钮
    
    QTimer* timer_Close;//本窗口关闭定时器
public:
    /**
     * @brief 构造一个通知气泡
     * @param parent 父窗口
     * @param text 显示的文本内容
     * @param duration 持续时间 毫秒
     * @note 本身默认隐藏，以配合后面的动画
     */
    explicit NotificationBubble(const QString& text, QWidget* parent, int duration = 5000);
    ~NotificationBubble();

    /**
     * @brief 在主窗口右上方播放滑入动画以显示
     */
    void startSlideInAnimation();

    
protected:
    /**
     * @brief 重写绘图事件
     * @param event 
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief 重写关闭事件
     * @param event 
     */
    void closeEvent(QCloseEvent* event) override;

signals:
    /**
     * @brief 泡泡已关闭
     * @param 关闭的泡泡指针
     * @note Qt 信号
     */
    void bubbleColsed(NotificationBubble* bubble);
};
