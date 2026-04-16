#pragma once

#include <QGroupBox>
#include "sundry_qt.h"

namespace Ui {
    class ReceiveAreaBox;
}

class ReceiveAreaBox : public QGroupBox
{
    Q_OBJECT
private:
    Ui::ReceiveAreaBox* ui;

public:
    explicit ReceiveAreaBox(QWidget* parent = nullptr);
    ~ReceiveAreaBox();
private:
    bool stopDisplaying = false;//停止显示
    bool timestamp = false;//显示时间戳
    bool text = true;//是否将数据作为文本显示
    EncodingEnum encoding = EncodingEnum::UTF8;//要显示的编码
public:
    /**
     * @brief 设置停止显示
     * @param state 是否停止显示
     */
    void setStopDisplaying(bool state);
    /**
     * @brief 设置显示时间戳
     * @param state 是否显示
     */
    void setTimestamp(bool state);
    /**
     * @brief 要展示的数据是否为文本
     * @param state 是否为文本
     */
    void setText(bool state);
    /**
     * @brief 设置文本数据的编码
     * @param theEncoding 编码
     */
    void setEncoding(EncodingEnum theEncoding);
    /**
     * @brief 在接收区中展示数据
     * @param data 要展示的数据
     */
    void showData(QByteArray data);

    /**
     * @brief 文本追加
     * @param text 文本
     */
    void appendPlainText(const QString& text);

    /**
     * @brief 保存到文件
     */
    void receiveToFile(void);
    /**
     * @brief 清空接收区
     */
    void clear(void);

signals:
    /**
     * @brief 请求通知
     * @param notification 通知文本
     * @note Qt 信号
     */
    void requestToNotification(QString notification);
};


