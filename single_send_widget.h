#ifndef SINGLE_SEND_WIDGET_H
#define SINGLE_SEND_WIDGET_H

#include <QWidget>

namespace Ui {
class SingleSendWidget;
}

class SingleSendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleSendWidget(QWidget *parent = nullptr);
    ~SingleSendWidget();

private:
    Ui::SingleSendWidget *ui;
};

#endif // SINGLE_SEND_WIDGET_H
