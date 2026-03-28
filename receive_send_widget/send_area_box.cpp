#include "send_area_box.h"

#include "ui_send_area_box.h"

#include <QTextCodec>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QScrollArea>
#include <QTableWidget>
#include <QDesktopServices>

SendAreaBox::SendAreaBox(QWidget* parent) 
	: QGroupBox(parent)
	, ui(new Ui::SendAreaBox)
{
    ui->setupUi(this);
	this->switchMode(SendMode::Single);

	//配置连接 单项窗口发送
	connect(ui->single, &SingleSendWidget::signal_Send, [this](QString str) {
		QByteArray byteArray = this->getSentContent(str);
		emit this->requestToSend(byteArray);
		});

	//配置连接 多项窗口发送
	connect(ui->multiple, &MultipleSendWidget::signal_Send, [this](QString str) {
		QByteArray byteArray = this->getSentContent(str);
		emit this->requestToSend(byteArray);
		});
	//配置连接 多项窗口通知
	connect(ui->multiple, &MultipleSendWidget::signal_Notification, [this](QString str) {
		emit this->requestToNotification(str);
		});


	/* 用于自动发送的定时器 */
	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);//ms级精度
	this->timer->stop();
	this->timer->setInterval(500);
	//定时到了
	connect(timer, &QTimer::timeout, [this]() {
		QString str;
		if (this->mode == SendMode::Single)
			str = ui->single->getUserString();
		else if (this->mode == SendMode::Multiple)
			str = ui->multiple->getUserString();
		qDebug() << str;
		QByteArray data = this->getSentContent(str);
		emit this->requestToSend(data);
		qDebug() << data;
		});

}

void SendAreaBox::switchMode(SendMode m)
{
	this->mode = m;
	if (m == SendMode::Single)
	{
		this->setTitle("发送区（单项发送）");
		ui->single->show();
		ui->multiple->hide();
	}
	else if (m == SendMode::Multiple)
	{
		this->setTitle("发送区（多项发送）");
		ui->single->hide();
		ui->multiple->show();
	}
}

void SendAreaBox::setAllowSending(bool a)
{
	ui->single->setAllowSending(a);
	ui->multiple->setAllowSending(a);
}

void SendAreaBox::setText(bool t)
{
	this->text = t;
}

void SendAreaBox::setAppend(bool a, QByteArray data)
{
	this->append = a;
	this->appendData = data;
}

QByteArray SendAreaBox::getSentContent(QString str)
{
	if (str.isEmpty()) return {};

	QByteArray dataSend;//要发送的数据

	if (this->text)//如果选择了文本
	{
		QTextCodec* codec = QTextCodec::codecForName(getEncodingQByteArray(encodingUsed));
		dataSend = codec->fromUnicode(str);//编码转换
	}
	else//选择了 HEX
	{
		if (isValidHexSequence(str) != true)
		{
			emit this->requestToNotification("不是 HEX 字符串");
			qDebug() << "要发送的不是 HEX 字符串";
			return {};
		}
		dataSend = hexSpacedToQByteArray(str);//将对应字符串还原为十六进制数据
	}

	if (this->append)// 在结尾追加
	{
		dataSend.append(this->appendData);
	}

	return dataSend;
}


void SendAreaBox::setAutoSend(bool a)
{
	if (a)
	{
		this->timer->start();
		qDebug() << "开始自动发送";
	}
	else
	{
		this->timer->stop();
		qDebug() << "停止自动发送";
	}
}

bool SendAreaBox::isAutoSend(void) const
{
	return this->timer->isActive();
}

void SendAreaBox::setSendCycle(int msec)
{
	this->timer->setInterval(msec);
	qDebug() << "自动发送周期改变";
}


