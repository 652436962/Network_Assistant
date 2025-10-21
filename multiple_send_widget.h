#ifndef MULTIPLE_SEND_WIDGET_H
#define MULTIPLE_SEND_WIDGET_H

#include <QWidget>

namespace Ui {
class MUltipleSendWidget;
}

class MUltipleSendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MUltipleSendWidget(QWidget *parent = nullptr);
    ~MUltipleSendWidget();

private:
    Ui::MUltipleSendWidget *ui;
};

#endif // MULTIPLE_SEND_WIDGET_H
