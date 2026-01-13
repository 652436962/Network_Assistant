#pragma once

#include <QWidget>

#include <QGroupBox>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include "debounced_spin_box.h"

#include "global.h"
#include "sundry.h"

class SendSettingsBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit SendSettingsBox(QWidget *parent = nullptr);
    ~SendSettingsBox();
private:
    QGridLayout* gridLayout;
    QLabel* label_Option;
    QComboBox* comboBox_Option;
    QRadioButton* radioButton_Text;
    QRadioButton* radioButton_HEX;
    QCheckBox* checkBox_Append;
    QComboBox* comboBox_Append;
    QCheckBox* checkBox_AutoSend;
    QSpacerItem* horizontalSpacer;
    QLabel* label_AutoSendCycle;
    DebouncedSpinBox* spinBox_AutoSendCycle;
    QLabel* label_MS;

    /**
     * @brief 设置 UI
     * @param  
     */
    void setupUi(void);
public:
    /**
     * @brief 是否开启了自动发送
     * @return 是否
     */
    bool getAutoSend(void) const;
    /**
     * @brief 获取自动发送周期
     * @return 自动发送周期 ms
     */
    int getAutoSendCycle(void) const;

    /**
     * @brief 获取发送选项
     * @return 发送选项
     */
    SendMode getSendOption(void) const;

    /**
     * @brief 根据网络的连接情况改变
     * @param checked 是否正在进行网络活动
     */
    void changeAccordingState(bool checked);
signals:
    /**
     * @brief 切换发送区
     * @param option 发送区选项
     * @note Qt 信号
     */
    void changeSendArray(SendMode option);

signals:
    /**
     * @brief 设置显示文本
     * @param state 是否
     * @note Qt 信号
     */
    void setText(bool state);
signals:
    /**
     * @brief 请求自动发送是否开启
     * @param open 是否开启
     * @note Qt 信号
     */
    void signal_AutoSend(bool open);
signals:
    /**
     * @brief 请求设置自动发送周期
     * @param msec 自动发送周期 毫秒
     * @note Qt 信号
     */
    void requestChangeCycle(int msec);

signals:
    /**
     * @brief 设置追加
     * @param checked 是否追加
     * @param content 要追加的数据
     * @note Qt 信号
     */
    void setAppend(bool checked, QByteArray content);


};

