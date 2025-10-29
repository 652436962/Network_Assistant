#ifndef MULTIPLE_SEND_WIDGET_H
#define MULTIPLE_SEND_WIDGET_H

#include <QWidget>

namespace Ui {
class MultipleSendWidget;
}

class MultipleSendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleSendWidget(QWidget *parent = nullptr);
    ~MultipleSendWidget();

private:
    Ui::MultipleSendWidget *ui;
};

#endif // MULTIPLE_SEND_WIDGET_H
