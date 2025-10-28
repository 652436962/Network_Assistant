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

class SendSettingsBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit SendSettingsBox(QWidget *parent = nullptr);
    /*~SendSettingsWidget();*/
public:
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
    QSpinBox* spinBox_AutoSendCycle;
    QLabel* label_MS;

    /**
     * @brief 设置 UI
     * @param  
     */
    void setupUi(void);

    /**
     * @brief 设置 UI 中的文本
     * @param  
     */
    void retranslateUi(void);

signals:
    /**
     * @brief 设置显示文本
     * @param state 是否
     * @note Qt 信号
     */
    void setText(bool state);

    /**
     * @brief 设置停止显示
     * @param state 是否
     * @note Qt 信号
     */
    void setStopDispalying(bool state);

    /**
     * @brief 设置是否显示时间戳
     * @param state 是否
     * @note Qt 信号
     */
    void setTimestamp(bool state);


//private:
//    Ui::SendSettingsWidget *ui;

//private:
//    /**
//     * @brief 重新绘图事件，以显示边框
//     * @param event
//     */
//    void paintEvent(QPaintEvent* event) override;
};

