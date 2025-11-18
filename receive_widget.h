#pragma once

#include <QObject>
#include <QWidget>

#include <QPlainTextEdit>

#include "sundry.h"
#include "sundry_qt.h"

class ReceiveWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ReceiveWidget(QWidget* parent = nullptr);
    ~ReceiveWidget();
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

signals:
};


