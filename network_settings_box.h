#pragma once

#include <QWidget>
#include <QGroupBox>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

#include <QHostAddress>

#include "led_widget.h"
#include "toggle_button.h"

#include "global.h"
#include "sundry.h"

class NetworkSettingsBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit NetworkSettingsBox(QWidget *parent = nullptr);
    ~NetworkSettingsBox();

private:
    QGridLayout* gridLayout;
    QLabel* label_WorkMode;
    QLabel* label_Address;
    QLabel* label_Port;
    LED_Widget* led;
    QPushButton* pushButton_Other;
    ToggleButton* toggleButton;//开关
    QLineEdit* lineEdit_Address;
    QSpinBox* spinBox_Port;
    QComboBox* comboBox_WorkMode;
    QComboBox* comboBox_Address;

    /**
     * @brief 设置 UI
     */
    void setupUi(void);


public:
    /**
     * @brief 获取选择的网络协议类型
     * @param  
     * @return 选择的网络协议类型
     */
    WorkMode getSelectedMode(void);

    ///**
    // * @brief 获取输入的地址
    // * @return 输入的地址
    // */
    //QString getAddress(void);

    /**
     * @brief 获取IP地址
     * @return 选择或输入的IP地址
     */
    QHostAddress getAddress(void);

    /**
     * @brief 获取端口号
     * @return 选择的端口号
     */
    uint16_t getPortValue(void);

private:
    bool networkActive = false;//是否正在进行网络活动
private:


    /**
     * @brief 根据选项改变 UI
     */
    void changeUiAccordingOption(void);

    /**
     * @brief 获取本地所有可用 IP 地址并刷新下拉框
     */
    void getLocalAddress(void);
public:
    /**
     * @brief 根据网络的连接情况改变UI
     * @param state 是否正在进行网络活动
     */
    void changeUiAccordingState(bool state);
signals:
    /**
     * @brief 请求工作
     * @note Qt 信号  
     */
    void requestWork(WorkMode mode);
signals:
    /**
     * @brief 模式选项改变
     * @param 工作模式
     * @note Qt 信号  
     */
    void modeOptionChanged(WorkMode mode);

};


