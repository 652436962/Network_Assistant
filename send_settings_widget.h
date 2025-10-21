#ifndef SEND_SETTINGS_WIDGET_H
#define SEND_SETTINGS_WIDGET_H

#include <QWidget>

namespace Ui {
class SendSettingsWidget;
}

class SendSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendSettingsWidget(QWidget *parent = nullptr);
    ~SendSettingsWidget();

private:
    Ui::SendSettingsWidget *ui;

private:
    /**
     * @brief 重新绘图事件，以显示边框
     * @param event
     */
    void paintEvent(QPaintEvent* event) override;
};

#endif // SEND_SETTINGS_WIDGET_H
