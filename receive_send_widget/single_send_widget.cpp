#include "single_send_widget.h"
#include "ui_single_send_widget.h"

SingleSendWidget::SingleSendWidget(QWidget* parent) 
	: QWidget(parent)
	, ui(new Ui::SingleSendWidget)
{
	ui->setupUi(this);
	this->setAllowSending(false);

	//点击发送按钮
	connect(ui->pushButton_Send, &QPushButton::clicked, [this]() {

		QString str = ui->plainTextEdit->toPlainText();
		emit this->signal_Send(str);
		});

	//清理按钮
	connect(ui->pushButton_Clear, &QPushButton::clicked, [this]() {
		ui->plainTextEdit->clear(); });

	qDebug() << "单项发送窗口建立";
}

SingleSendWidget::~SingleSendWidget()
{
	qDebug() << "单项发送窗口关闭";
}

QString SingleSendWidget::getUserString()
{
	return ui->plainTextEdit->toPlainText();
}

void SingleSendWidget::setAllowSending(bool a)
{
	this->allowSending = a;
	ui->pushButton_Send->setEnabled(a);
}