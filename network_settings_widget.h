#pragma once

#include <QWidget>

namespace Ui
{
    class NetworkSettingsWidget;
}

class NetworkSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkSettingsWidget(QWidget *parent = nullptr);
    ~NetworkSettingsWidget();

private:
    /**
     * @brief 重新绘图事件，以显示边框
     * @param event 
     */
    void paintEvent(QPaintEvent* event) override;

public:
    Ui::NetworkSettingsWidget *ui;
};


