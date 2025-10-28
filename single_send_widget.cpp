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
		emit this->requestToSend(dataString);
		});

	//清理按钮
	connect(ui->pushButton_Clear, &QPushButton::clicked, this, [this]() {
		ui->plainTextEdit->clear(); });

}

SingleSendWidget::~SingleSendWidget()
{
	delete ui;
}
