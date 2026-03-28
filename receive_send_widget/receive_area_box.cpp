#include "receive_area_box.h"
#include "ui_receive_area_box.h"

#include <QTextCodec>
#include <QFileDialog>

ReceiveAreaBox::ReceiveAreaBox(QWidget* parent)
	: QGroupBox(parent)
	, ui(new Ui::ReceiveAreaBox)
{
	ui->setupUi(this);

	qDebug() << "接收窗口建立";
}


ReceiveAreaBox::~ReceiveAreaBox()
{
	qDebug() << "接收窗口关闭";
}

void ReceiveAreaBox::setStopDisplaying(bool state)
{
	this->stopDisplaying = state;
}

void ReceiveAreaBox::setTimestamp(bool state)
{
	this->timestamp = state;
}

void ReceiveAreaBox::setText(bool state)
{
	this->text = state;
}

void ReceiveAreaBox::setEncoding(EncodingEnum theEncoding)
{
	this->encoding = theEncoding;
}

void ReceiveAreaBox::showData(QByteArray data)
{
	// 如果停止显示
	if (this->stopDisplaying)        return;

	/*在文本框中显示*/
	QString stringShow = ""; // 要显示的字符串

	// 如果选择了时间戳
	if (this->timestamp)
	{
		QString nowString = QString::fromStdString(getTimestamp());
		stringShow += (nowString + "  >>\n");
	}

	if (this->text) // 如果选择了文本
	{
		QString dataString;
		QByteArray encodingName = QByteArray::fromStdString(getEncodingString_Std(encoding));      // 得到编码的字符串
		QTextCodec* codec = QTextCodec::codecForName(encodingName); // 获取编码器
		dataString = codec->toUnicode(data);                   // 解码为 QString
		stringShow += dataString;
	}
	else // 如果选择了HEX
	{
		QString hexString = qByteArrayToHexSpaced(data);
		stringShow += hexString;
	}

	ui->plainTextEdit->appendPlainText(stringShow);
}

void ReceiveAreaBox::appendPlainText(const QString& text)
{
	if (this->stopDisplaying) return;
	ui->plainTextEdit->appendPlainText(text);
}

void ReceiveAreaBox::receiveToFile(void)
{
	QString text = ui->plainTextEdit->toPlainText();
	QString fileName = QFileDialog::getSaveFileName(this, "保存文本文件", "", "文本文件(*.txt);;所有文件(*)");
	if (fileName.isEmpty()) return;// 用户取消了？直接返回
	QFile file(fileName);
	if (!file.open(QIODeviceBase::WriteOnly | QIODevice::Text))
	{
		emit this->requestToNotification("无法创建文件");
		qDebug() << "无法创建文件 " << __FILE__ << __LINE__ << fileName << file.errorString();
		return;
	}
	QTextStream out(&file);
	out << text;
	file.close();
	this->requestToNotification("保存成功");
	qDebug() << "保存成功" << fileName;
}

void ReceiveAreaBox::clear(void)
{
	ui->plainTextEdit->clear();
}
