#pragma once

#include <QWidget>

namespace Ui {
class ReceiveSettingsWidget;
}

class ReceiveSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveSettingsWidget(QWidget *parent = nullptr);
    ~ReceiveSettingsWidget();

private:
    /**
     * @brief 重写绘图事件以显示边框
     * @param event 
     */
    void paintEvent(QPaintEvent* event) override;
public:
    Ui::ReceiveSettingsWidget *ui;
};


