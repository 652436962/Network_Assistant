#include "single_send_widget.h"
#include "ui_single_send_widget.h"

SingleSendWidget::SingleSendWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::SingleSendWidget)
{
	ui->setupUi(this);

	//点击发送按钮
	connect(ui->pushButton_Send, &QPushButton::clicked, this, [this]() {
		QString dataString = ui->plainTextEdit->toPlainText();
		if (dataString.isEmpty())
		{
			return;
		}
		emit this->requestToSend(dataString.toUtf8());
		});

	//清理按钮
	connect(ui->pushButton_Clear, &QPushButton::clicked, this, [this]() {
		ui->plainTextEdit->clear(); });

	qDebug() << "单项发送窗口建立";
}

SingleSendWidget::~SingleSendWidget()
{
	delete ui;
	qDebug() << "单项发送窗口删除";
}
