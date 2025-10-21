#include "single_send_widget.h"
#include "ui_single_send_widget.h"

SingleSendWidget::SingleSendWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleSendWidget)
{
    ui->setupUi(this);
}

SingleSendWidget::~SingleSendWidget()
{
    delete ui;
}
