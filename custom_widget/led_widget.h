#pragma once

#include "qwidget.h"
#include "qcolor.h"


/**
 * @brief LED 窗口
 */
class LED_Widget: public QWidget
{
    Q_OBJECT
public:
    LED_Widget(QWidget* parent = nullptr);
    ~LED_Widget() override = default;
private:
    bool state = false;//是否打开
public:
    /**
     * @brief 打开
     */
    void open(void);
    /**
     * @brief 关闭
     */
    void close(void);
    /**
     * @brief 设置打开或关闭
     * @param state true 打开 false 关闭
     */
    void setState(bool state);
    /**
     * @brief 获取当前是否打开
     * @return 当前是否打开
     */
    bool getState(void) const;
    /**
     * @brief 切换打开或关闭
     */
    void toggle(void);
private:
    QColor color = Qt::green;//LED 颜色
public:
    /**
     * @brief 设置颜色
     * @param color 颜色
     */
    void setColor(const QColor& color);
    /**
     * @brief 获取设置的颜色 
     * @return 设置的颜色
     */
    QColor getColor(void) const;

protected:
    void paintEvent(QPaintEvent* event) override;
};
