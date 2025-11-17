#include "single_send_widget.h"
#include "ui_single_send_widget.h"

#include "sundry_qt.h"
#include "global.h"

#include <QTextCodec>
#include <QMessageBox>

SingleSendWidget::SingleSendWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::SingleSendWidget)
{
	ui->setupUi(this);
	this->setAllowSending(false);

	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);//ms级精度
	this->timer->stop();
	//定时到了
	connect(timer, &QTimer::timeout, [this]() {
		QByteArray data = this->getSentContent();
		emit this->requestToSend(data);
		});

	//点击发送按钮
	connect(ui->pushButton_Send, &QPushButton::clicked, [this]() {

		QByteArray data = this->getSentContent();
		emit this->requestToSend(data);
		});

	//清理按钮
	connect(ui->pushButton_Clear, &QPushButton::clicked, [this]() {
		ui->plainTextEdit->clear(); });

	qDebug() << "单项发送窗口建立";
}

SingleSendWidget::~SingleSendWidget()
{
	delete ui;
	qDebug() << "单项发送窗口关闭";
}

QByteArray SingleSendWidget::getSentContent(void)
{
	QString dataString = ui->plainTextEdit->toPlainText();
	if (dataString.isEmpty())
	{
		return {};
	}

	QByteArray dataSend;//要发送的数据

	if (this->text)//如果选择了文本
	{
		QTextCodec* codec = QTextCodec::codecForName(getEncodingQByteArray(encodingUsed));
		dataSend = codec->fromUnicode(dataString);//编码转换
	}
	else//选择了 HEX
	{
		if (isValidHexSequence(dataString) != true)
		{
			emit this->requestToNotification("不是 HEX 字符串");
			qDebug() << "要发送的不是 HEX 字符串";
			return {};
		}
		dataSend = hexSpacedToQByteArray(dataString);//将对应字符串还原为十六进制数据
	}

	if (this->append)// 在结尾追加
	{
		dataSend.append(this->appendData);
	}

	return dataSend;
}

void SingleSendWidget::setText(bool t)
{
	this->text = t;
}

void SingleSendWidget::setAppend(bool a, QByteArray data)
{
	this->append = a;
	this->appendData = data;
}

void SingleSendWidget::setAutoSend(bool a, int c)
{
	this->autoSend = a;
	this->autoCycle = c;

	if (this->autoSend)
	{
		if (this->timer->isActive())
		{
			this->timer->setInterval(autoCycle);
			qDebug() << "单项发送区自动发送周期改变";
		}
		else
		{
			this->timer->start(autoCycle);
			qDebug() << "单项发送区开始自动发送";
		}
	}
	else
	{
		this->timer->stop();
		qDebug() << "单项发送区停止自动发送";
	}
}

bool SingleSendWidget::getAutoSend(void) const
{
	return this->autoSend;
}

void SingleSendWidget::setAllowSending(bool a)
{
	this->allowSending = a;
	this->ui->pushButton_Send->setEnabled(a);
}
