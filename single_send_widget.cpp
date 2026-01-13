#include "single_send_widget.h"

#include "sundry_qt.h"
#include "global.h"

#include <QTextCodec>
#include <QMessageBox>

SingleSendWidget::SingleSendWidget(QWidget* parent)	: QWidget(parent)
{
	this->setupUi();
	this->setAllowSending(false);

	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);//ms级精度
	this->timer->stop();
	this->timer->setInterval(500);
	//定时到了
	connect(timer, &QTimer::timeout, [this]() {
		QByteArray data = this->getSentContent();
		emit this->requestToSend(data);
		});

	//点击发送按钮
	connect(this->pushButton_Send, &QPushButton::clicked, [this]() {

		QByteArray data = this->getSentContent();
		emit this->requestToSend(data);
		});

	//清理按钮
	connect(this->pushButton_Clear, &QPushButton::clicked, [this]() {
		this->plainTextEdit->clear(); });

	qDebug() << "单项发送窗口建立";
}

SingleSendWidget::~SingleSendWidget()
{
	qDebug() << "单项发送窗口关闭";
}

void SingleSendWidget::setupUi()
{
	gridLayout = new QGridLayout(this);
	gridLayout->setHorizontalSpacing(8);
	gridLayout->setVerticalSpacing(4);
	gridLayout->setContentsMargins(2, 2, 2, 2);
	plainTextEdit = new QPlainTextEdit(this);
	plainTextEdit->setMinimumSize(QSize(150, 150));

	gridLayout->addWidget(plainTextEdit, 0, 0, 1, 3);

	horizontalSpacer = new QSpacerItem(230, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

	pushButton_Send = new QPushButton(this);
	pushButton_Send->setEnabled(true);
	pushButton_Send->setMinimumSize(QSize(32, 16));
	pushButton_Send->setMaximumSize(QSize(64, 32));

	gridLayout->addWidget(pushButton_Send, 1, 1, 1, 1);

	pushButton_Clear = new QPushButton(this);
	pushButton_Clear->setMinimumSize(QSize(32, 16));
	pushButton_Clear->setMaximumSize(QSize(64, 32));

	gridLayout->addWidget(pushButton_Clear, 1, 2, 1, 1);


	pushButton_Send->setText("发送");
	pushButton_Clear->setText("清空");
}

QByteArray SingleSendWidget::getSentContent(void)
{
	QString dataString = this->plainTextEdit->toPlainText();
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

void SingleSendWidget::setAutoSend(bool a)
{
	if (a)
	{
		this->timer->start();
		qDebug() << "单项发送区开始自动发送";
	}
	else
	{
		this->timer->stop();
		qDebug() << "单项发送区停止自动发送";
	}
}

bool SingleSendWidget::isAutoSend(void) const
{
	return this->timer->isActive();
}

void SingleSendWidget::setSendCycle(int msec)
{
	this->timer->setInterval(msec);
	qDebug() << "单项发送区自动发送周期改变";
}

void SingleSendWidget::setAllowSending(bool a)
{
	this->allowSending = a;
	this->pushButton_Send->setEnabled(a);
}
