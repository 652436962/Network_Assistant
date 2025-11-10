#pragma once

#include <QFrame>
#include <QTimer>
#include <QLabel>
#include <QToolButton>
#include <QPropertyAnimation>

/**
 * @brief 单个通知气泡组件
 */
class NotificationBubble: public QFrame
{
    Q_OBJECT
private:
    static constexpr int WIDTH = 512;//窗口宽
    static constexpr int HEIGHT = 48;//窗口高
private:
    QLabel* label_Text;          // 显示文本内容的标签
    QToolButton* toolButton_Close; // 关闭按钮
    
    QTimer* timer_Close;//本窗口关闭定时器
public:
    /**
     * @brief 构造一个通知气泡 
     * @param text 显示的文本内容
     * @param duration 持续时间 毫秒
     * @param parent 父窗口
     * @note 本身默认隐藏，以配合后面的动画
     */
    explicit NotificationBubble(const QString text="", int duration = 5000, QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~NotificationBubble();

    /**
     * @brief 启动气泡的定时器
     */
    void startTimer(void);

    /**
     * @brief 左移一个身位，有动画
     */
    void movePositionLeft(void);
    /**
     * @brief 上移一个身位，有动画
     */
    void movePositionUp(void);

    
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
