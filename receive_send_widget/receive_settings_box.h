#pragma once

#include <QWidget>
#include <QGroupBox>


namespace Ui {
    class ReceiveSettingsBox;
}

class ReceiveSettingsBox : public QGroupBox
{
    Q_OBJECT
private:
    Ui::ReceiveSettingsBox* ui;

public:
    explicit ReceiveSettingsBox(QWidget *parent = nullptr);

signals:
    /**
     * @brief 接收区清屏
     */
    void receiveAreaClear(void);
signals:
    /**
     * @brief 设置显示文本
     * @param state 是否
     * @note Qt 信号
     */
    void setText(bool state);
signals:
    /**
     * @brief 设置停止显示
     * @param state 是否
     * @note Qt 信号
     */
    void setStopDispalying(bool state);
signals:
    /**
     * @brief 设置是否显示时间戳
     * @param state 是否
     * @note Qt 信号
     */
    void setTimestamp(bool state);
signals:
    /**
     * @brief 请求保存到文件
     * @note Qt 信号
     */
    void receiveToFile(void);
};


