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

class NetworkSettingsBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit NetworkSettingsBox(QWidget *parent = nullptr);
    /*~NetworkSettingsBox();*/

public:
    QGridLayout* gridLayout;
    QLabel* label_ProtocolType;
    QLabel* label_Address;
    QLabel* label_Port;
    QSpacerItem* horizontalSpacer;
    LED_Widget* led;
    QPushButton* pushButton_Other;
    QPushButton* pushButton_Start;
    QLineEdit* lineEdit_Address;
    QSpinBox* spinBox;
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

//private:
//    /**
//     * @brief 重新绘图事件，以显示边框
//     * @param event 
//     */
//    void paintEvent(QPaintEvent* event) override;

//private:
//    Ui::NetworkSettingsWidget *ui;
};


