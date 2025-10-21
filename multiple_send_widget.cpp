#include "multiple_send_widget.h"
#include "ui_multiple_send_widget.h"

MUltipleSendWidget::MUltipleSendWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MUltipleSendWidget)
{
    ui->setupUi(this);
}

MUltipleSendWidget::~MUltipleSendWidget()
{
    delete ui;
}
