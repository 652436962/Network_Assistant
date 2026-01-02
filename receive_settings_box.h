#pragma once

#include <QWidget>
#include <QGroupBox>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

class ReceiveSettingsBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit ReceiveSettingsBox(QWidget *parent = nullptr);
    /*~ReceiveSettingsWidget();*/

private:
    QGridLayout* gridLayout;
    QRadioButton* radioButton_Text;
    QRadioButton* radioButton_HEX;
    QCheckBox* checkBox_StopDisplay;
    QCheckBox* checkBox_Timestamp;
    QPushButton* pushButton_Clear;
    QPushButton* pushButton_Save;

    /**
     * @brief 设置 UI
     * @param  
     */
    void setupUi(void);

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


