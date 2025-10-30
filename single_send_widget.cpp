#include "single_send_widget.h"
#include "ui_single_send_widget.h"

#include "sundry_qt.h"

#include <QTextCodec>
#include <QMessageBox>

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

        QByteArray dataSend;//要发送的数据

        if (this->text)//如果选择了文本
        {
            QTextCodec* codec = QTextCodec::codecForName(QByteArray::fromStdString(getEncodingString(this->encoding)));
            dataSend = codec->fromUnicode(dataString);//编码转换
        }
        else//选择了 HEX
        {
            if (isValidHexSequence(dataString) != true)
            {
                QMessageBox::warning(this, "警告", "要发送的不是 HEX 字符串，请检查或者发送文本");
                qDebug() << "要发送的不是 HEX 字符串，请检查或者发送文本";
                return;
            }
            dataSend = hexSpacedToQByteArray(dataString);//将对应字符串还原为十六进制数据
        }
        
        if (this->append)// 在结尾追加
        {
			dataSend.append(this->appendData);
        }

		emit this->requestToSend(dataSend);
	});

	//清理按钮
	connect(ui->pushButton_Clear, &QPushButton::clicked, this, [this]() {
		ui->plainTextEdit->clear(); });

	qDebug() << "单项发送窗口建立";
}

SingleSendWidget::~SingleSendWidget()
{
	delete ui;
	qDebug() << "单项发送窗口关闭";
}

void SingleSendWidget::setText(bool t)
{
	this->text = t;
}
void SingleSendWidget::setEncoding(EncodingEnum e)
{
	this->encoding = e;
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
}
