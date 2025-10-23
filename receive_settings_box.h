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

public:
    QGridLayout* gridLayout;
    QRadioButton* radioButton_Text;
    QRadioButton* radioButton_HEX;
    QCheckBox* checkBox_ReceiveStopDisplay;
    QCheckBox* checkBox_Timestamp;
    QPushButton* pushButton_Clear;
    QPushButton* pushButton_Save;

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

//private:
//    /**
//     * @brief 重写绘图事件以显示边框
//     * @param event 
//     */
//    void paintEvent(QPaintEvent* event) override;
//private:
//    Ui::ReceiveSettingsWidget *ui;
};


