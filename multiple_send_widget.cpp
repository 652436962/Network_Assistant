#include "multiple_send_widget.h"
#include "ui_multiple_send_widget.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <QFileDialog>
#include <QScrollArea>

#include <QTableWidget>

#include <QTextCodec>

#include <QDesktopServices>

MultipleSendWidget::MultipleSendWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MultipleSendWidget)
{
    ui->setupUi(this);

	while (ui->tabWidget->count() > 0) // 开始清空tabWidget
	{
		ui->tabWidget->removeTab(0); // 索引会变更
	}

	this->timer = new QTimer(this);
	this->timer->stop();
	this->timer->setTimerType(Qt::PreciseTimer);//ms级精度
	this->timer->setSingleShot(false); // 循环
	this->timer->setInterval(500);
	//定时到了
	connect(this->timer, &QTimer::timeout, [this]() {
		if (ui->tabWidget->count() <= 0) // 多页窗口中没有表格
		{
			return;
		}

		// 获取当前表格窗口
		QTableWidget* tableWidget = static_cast<QTableWidget*>(ui->tabWidget->currentWidget());
		if (tableWidget->rowCount() <= 0) // 表格中没有数据
		{
			return;
		}
		// 获取当前行的指令
		QTableWidgetItem* item = tableWidget->item(this->currentRow, 1);
		if (!item)
			return;

		QString command = item->text();
		QByteArray sendData= this->getSentContent(command);
		emit this->requestToSend(sendData);

		tableWidget->setCurrentCell(this->currentRow, 1);

		// 更新行号（下一行）
		this->currentRow++;
		if (this->currentRow >= tableWidget->rowCount())
		{
			this->currentRow = 0; // 回到第一行，实现循环
		}
		});
	//切换页后 自动发送当前行归0
	connect(this->ui->tabWidget, &QTabWidget::currentChanged, [this]() {this->currentRow = 0; });

	/*创建保存发送数据的文件夹*/
	QString appDirPath = QCoreApplication::applicationDirPath(); // 获取 .exe 所在的目录
	qDebug() << "程序所在目录:" << appDirPath;
	QString dataDirPath = appDirPath + "/multiple_data_files"; // 构造目标文件夹路径
	QDir dataDir(dataDirPath);                                 // 指向保存数据文件夹的 QDir 对象
	if (dataDir.exists())
	{
		qDebug() << "文件夹:" << dataDirPath << "已存在";
	}
	else
	{
		qDebug() << "文件夹:" << dataDirPath << "原本不存在";
		if (QDir().mkpath(dataDirPath))
		{
			qDebug() << "成功创建文件夹:" << dataDirPath;
		}
		else
		{
			qWarning() << "创建文件夹" << dataDirPath << "失败!";
		}
	}

	// 打开文件保存目录
	connect(ui->pushButton_Location, &QPushButton::clicked, [this]() {
		QString location = QCoreApplication::applicationDirPath() + "/multiple_data_files";
		QDir locationDir(location);
		if (!locationDir.exists())
		{
			if (!QDir().mkpath(location))
			{
				qDebug() << "创建失败 " << __FILE__ << __LINE__;
			}
		}

		bool result = QDesktopServices::openUrl(location); // 在资源管理器中打开
		if (!result)
		{
			qDebug() << "无法打开文件夹";
			emit this->requestToNotification("找不到默认保存位置，请检查");
		}
		});

	// 配置连接 移除当前页
	connect(ui->pushButton_Delete, &QPushButton::clicked, [this]() {
		if (ui->tabWidget->count() <= 0)
		{
			return;
		}
		int index = ui->tabWidget->currentIndex();
		ui->tabWidget->removeTab(index);
		});

	// 配置连接 导入.csv文件
	// 导入文件按钮
	connect(ui->pushButton_Import, &QPushButton::clicked, [this]() {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (fileName.isEmpty())
		{
			return;
		}
		// 获取选择的编码
		if (fileName.isEmpty())
		{
			return;
		}
		this->ImportCsvFile(fileName); // 导入文件
		
		});

	/* 导入 multiple_data_files 中的所有.csv文件 */
	// 获取所有 .csv 文件（不区分大小写）
	QStringList filters;
	filters << "*.csv" << "*.CSV";
	QFileInfoList fileList = dataDir.entryInfoList(filters, QDir::Files); // 只找文件，不找子文件夹
	// 遍历每个 .csv 文件
	for (const QFileInfo& fileInfo : fileList)
	{
		QString filePath = fileInfo.absoluteFilePath(); // 完整路径
		this->ImportCsvFile(filePath);
		// qDebug()<<"已导入"<<filePath;
	}
}

MultipleSendWidget::~MultipleSendWidget()
{
    delete ui;
}
void MultipleSendWidget::setText(bool t)
{
	this->text = t;
}

void MultipleSendWidget::setAppend(bool a, QByteArray data)
{
	this->append = a;
	this->appendData = data;
}

void MultipleSendWidget::setAutoSend(bool a)
{
	if (a)
	{
			this->timer->start();
			qDebug() << "多项发送区开始自动发送";
	}
	else
	{
		this->timer->stop();
		qDebug() << "多项发送区停止自动发送";
	}
}

bool MultipleSendWidget::isAutoSend(void) const
{
	return this->timer->isActive();
}

void MultipleSendWidget::setSendCycle(int mesc)
{
	this->timer->setInterval(mesc);
}


void MultipleSendWidget::setAllowSending(bool a)
{
	if (this->allowSending == a) return;
	this->allowSending = a;
	//遍历切换选项窗口
	for (int i = 0; i < this->ui->tabWidget->count(); i++)
	{
		QTableWidget* tableWidget = static_cast<QTableWidget*>(this->ui->tabWidget->widget(i));
		//遍历表格 2列
		for (int j = 0; j < tableWidget->rowCount(); j++)
		{
			QPushButton* pushButton = static_cast<QPushButton*>(tableWidget->cellWidget(j, 2));
			pushButton->setEnabled(a);
		}
	}

}

QByteArray MultipleSendWidget::getSentContent(QString dataString)
{	
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

void MultipleSendWidget::ImportCsvFile(QString fileName)
{
	QFileInfo fileInfo(fileName);
	QString baseName = fileInfo.baseName(); // 文件名

	// 读取表格文件的数据
	QVector<QVector<QByteArray>> formData = readCsvFile_Qt(fileName);

	QTableWidget* tableWidget = new QTableWidget(ui->tabWidget); // 表格窗口
	tableWidget->setRowCount(formData.size());
	tableWidget->setColumnCount(3); // 设置为3列
	tableWidget->setHorizontalHeaderLabels(QStringList() << "备注" << "指令" << "发送");

	QVBoxLayout* layout = new QVBoxLayout(ui->tabWidget);
	layout->setContentsMargins(2, 2, 2, 2);
	layout->setSpacing(2);

	layout->addWidget(tableWidget);
	layout->addStretch();

	int lineNumber = 0;

	QByteArray encodingName = getEncodingQByteArray(encodingUsed);
	QTextCodec* codec = QTextCodec::codecForName(encodingName); // 编码转换

	for (int i = 0; i < formData.size(); i++)
	{
		for (int j = 0; j < 2 && j<(formData[i]).size(); j++)
		{
			QString temp = codec->toUnicode(formData[i][j]); // 编码转换
			tableWidget->setItem(i, j, new QTableWidgetItem(temp));
		}
		QPushButton* button = new QPushButton(tableWidget);
		button->setEnabled(this->allowSending);
		button->setIcon(QIcon(":/icon/image/send.png"));
		connect(button, &QPushButton::clicked, [=]() {
			QString sendString = tableWidget->item(i, 1)->text();
			if (sendString.isEmpty()) return;
			QByteArray sendData = this->getSentContent(sendString);
			if (sendData.isEmpty()) return;
			emit this->requestToSend(sendData);
			});

		tableWidget->setCellWidget(i, 2, button);
	}

	ui->tabWidget->addTab(tableWidget, baseName);
	tableWidget->resizeColumnsToContents();
	ui->tabWidget->setCurrentWidget(tableWidget); // 展示新导入的

	qDebug() << "成功从 " << fileName << " 中导入 " + QString::number(formData.size()) + " 条指令";
	// QMessageBox::information(this, "成功", "已导入 " + QString::number(lineNumber) + " 条指令");
}