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

#include "led_widget.h"


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
    QPushButton* pushButton_Switch;//开关
    QLineEdit* lineEdit_Address;
    QSpinBox* spinBox_Port;
    QComboBox* comboBox_ProtocolType;

    /**
     * @brief 设置 UI
     */
    void setupUi(void);

    /**
     * @brief 设置 UI 中的文本
     * @param  
     */
    void retranslateUi(void);



public:
    /**
     * @brief 获取选择的网络协议类型
     * @param  
     * @return 选择的网络协议类型
     */
    WorkMode getSelectedMode(void);

    /**
     * @brief 获取输入的地址
     * @return 输入的地址
     */
    QString getAddress(void);

    /**
     * @brief 获取端口号
     * @return 选择的端口号
     */
    uint16_t getPortValue(void);

private:
    bool networkActive = false;//是否正在进行网络活动
public:
    /**
     * @brief 根据网络的连接情况改变UI
     * @param state 是否正在进行网络活动
     */
    void changeUI(bool state);

signals:
    /**
     * @brief 点击
     * @note Qt 信号  
     */
    void clicked(void);


//private:
//    /**
//     * @brief 重新绘图事件，以显示边框
//     * @param event 
//     */
//    void paintEvent(QPaintEvent* event) override;

//private:
//    Ui::NetworkSettingsWidget *ui;
};


