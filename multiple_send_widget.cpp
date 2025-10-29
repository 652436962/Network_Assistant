#include "multiple_send_widget.h"
#include "ui_multiple_send_widget.h"

MultipleSendWidget::MultipleSendWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MultipleSendWidget)
{
    ui->setupUi(this);
}

MultipleSendWidget::~MultipleSendWidget()
{
    delete ui;
}
