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

#include "scrollable_list_widget.h"



MultipleSendWidget::MultipleSendWidget(QWidget* parent)
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
		QByteArray sendData = this->getSentContent(command);
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
	if (dataDir.exists()) {
		qDebug() << "文件夹:" << dataDirPath << "已存在";
	}
	else {
		qDebug() << "文件夹:" << dataDirPath << "原本不存在";
		if (QDir().mkpath(dataDirPath)) {
			qDebug() << "成功创建文件夹:" << dataDirPath;
		}
		else {
			qWarning() << "创建文件夹" << dataDirPath << "失败!";
		}
	}

	// 配置连接 打开文件保存目录
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

	// 配置连接 添加一页
	connect(ui->pushButton_Add, &QPushButton::clicked, this, &MultipleSendWidget::addTabPage);

	// 配置连接 移除当前页
	connect(ui->pushButton_Delete, &QPushButton::clicked, this, &MultipleSendWidget::removeCurrentTabPage);

	// 配置连接 导入.csv文件
	// 导入文件按钮
	connect(ui->pushButton_Import, &QPushButton::clicked, [this]() {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (fileName.isEmpty())return;
		this->ImportCsvFile(fileName); // 导入文件
		});

	///* 导入 multiple_data_files 中的所有.csv文件 */
	//// 获取所有 .csv 文件（不区分大小写）
	//QStringList filters;
	//filters << "*.csv" << "*.CSV";
	//QFileInfoList fileList = dataDir.entryInfoList(filters, QDir::Files); // 只找文件，不找子文件夹
	//// 遍历每个 .csv 文件
	//for (const QFileInfo& fileInfo : fileList)
	//{
	//	QString filePath = fileInfo.absoluteFilePath(); // 完整路径
	//	this->ImportCsvFile(filePath);
	//	// qDebug()<<"已导入"<<filePath;
	//}
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


void MultipleSendWidget::setAllowSending(bool checked)
{
	if (this->allowSending == checked) return;
	this->allowSending = checked;
	//遍历切换选项窗口
	for (int i = 0; i < this->ui->tabWidget->count(); i++)
	{
		LineTableWidget* tableWidget = static_cast<LineTableWidget*>(this->ui->tabWidget->widget(i));
		//遍历表格 2列
		for (int j = 0; j < tableWidget->rowCount(); j++)
		{
			ALineWidget* lineWidget = tableWidget->getLine(j);
			lineWidget->setButtonEnable(checked);
		}
	}

}

QByteArray MultipleSendWidget::getSentContent(QString& dataString)
{
	if (dataString.isEmpty()) return {};

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

void MultipleSendWidget::addTabPage(void)
{
	LineTableWidget* lineTable = new LineTableWidget(this->ui->tabWidget);
	lineTable->setAllButtonsEnable(this->allowSending);
	int pageCount = ui->tabWidget->count();
	ui->tabWidget->addTab(lineTable, QString::number(pageCount + 1));
	connect(lineTable, &LineTableWidget::sendSignal, [this](QString comment) {
		QByteArray byteArray = this->getSentContent(comment);
		emit this->requestToSend(byteArray);
		});
}

void MultipleSendWidget::removeCurrentTabPage(void)
{
	if (ui->tabWidget->count() <= 0)
	{
		return;
	}
	int index = ui->tabWidget->currentIndex();
	QWidget* widget = ui->tabWidget->widget(index);
	if (widget)
	{
		ui->tabWidget->removeTab(index);
		delete widget;
	}
	else {
		qDebug() << "错误 空指针 " << __FILE__ << __LINE__;
	}
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
		for (int j = 0; j < 2 && j < (formData[i]).size(); j++)
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
}

ALineWidget::ALineWidget(QWidget* parent, QString comment, QString instruction) : QWidget(parent)
{
	this->setupUi();
	this->commentEdit->setText(comment);
	this->instructionEdit->setText(instruction);
	connect(sendButton, &QPushButton::clicked, [this]() {
		emit sendSignal(instructionEdit->text());
		});
}

void ALineWidget::setupUi(void)
{
	this->resize(300, 32);
	this->setMinimumSize(QSize(50, 32));
	this->setMaximumSize(QSize(512, 100));
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(4);
	horizontalLayout->setContentsMargins(2, 2, 2, 2);
	commentEdit = new QLineEdit(this);

	horizontalLayout->addWidget(commentEdit);

	instructionEdit = new QLineEdit(this);

	horizontalLayout->addWidget(instructionEdit);

	sendButton = new QPushButton(this);
	sendButton->setMinimumSize(QSize(16, 16));
	sendButton->setMaximumSize(QSize(24, 24));
	sendButton->setIcon(QIcon(":/icon/image/send.png"));
	horizontalLayout->addWidget(sendButton);
}

QString ALineWidget::getComment(void) const
{
	return commentEdit->text();
}

QString ALineWidget::getInstruction(void) const
{
	return instructionEdit->text();
}

void ALineWidget::setButtonEnable(bool checked)
{
	sendButton->setEnabled(checked);
}

LineTableWidget::LineTableWidget(QWidget* parent) :QWidget(parent)
{
	this->setupUi();

	// 配置连接 插入新 “行窗口”
	connect(pushButton_Add, &QPushButton::clicked, [this]() {pushBackLine(); });
	// 配置连接 删除最后一个“行窗口”
	connect(pushButton_Remove, &QPushButton::clicked, this, &LineTableWidget::popBackLine);
}

void LineTableWidget::setupUi(void)
{
	this->resize(336, 80);
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->setContentsMargins(0, 0, 0, 0);

	scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);

	scrollAreaWidgetContents = new QWidget(this);
	scrollAreaWidgetContents->setGeometry(QRect(0, 0, 336, 337));
	verticalLayout_Scroll = new QVBoxLayout(scrollAreaWidgetContents);

	// 标签 widget
	widget_Labels = new QWidget(scrollAreaWidgetContents);
	widget_Labels->setMaximumSize(QSize(512, 48));
	horizontalLayout_2 = new QHBoxLayout(widget_Labels);
	horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
	horizontalLayout_2->addItem(horizontalSpacer_2);
	QFont fontLabels;
	fontLabels.setPointSize(12);
	label_Comment = new QLabel("备注", widget_Labels);
	label_Comment->setFont(fontLabels);
	horizontalLayout_2->addWidget(label_Comment);
	horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
	horizontalLayout_2->addItem(horizontalSpacer_3);
	label_Instruction = new QLabel("指令", widget_Labels);
	label_Instruction->setFont(fontLabels);
	horizontalLayout_2->addWidget(label_Instruction);
	horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
	horizontalLayout_2->addItem(horizontalSpacer_4);
	label_Send = new QLabel("发送", widget_Labels);
	label_Send->setFont(fontLabels);
	horizontalLayout_2->addWidget(label_Send);

	verticalLayout_Scroll->addWidget(widget_Labels);

	// 按钮 widget
	widget_Buttons = new QWidget(scrollAreaWidgetContents);
	widget_Buttons->setMinimumSize(QSize(256, 32));
	widget_Buttons->setMaximumSize(QSize(512, 48));
	horizontalLayout = new QHBoxLayout(widget_Buttons);
	horizontalLayout->setSpacing(4);
	horizontalLayout->setContentsMargins(2, 2, 2, 2);
	horizontalSpacer = new QSpacerItem(171, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
	horizontalLayout->addItem(horizontalSpacer);
	pushButton_Add = new QPushButton("添加一行", widget_Buttons);
	horizontalLayout->addWidget(pushButton_Add);
	pushButton_Remove = new QPushButton("删除一行", widget_Buttons);
	pushButton_Remove->setEnabled(false);//初始不应有删除
	horizontalLayout->addWidget(pushButton_Remove);

	verticalLayout_Scroll->addWidget(widget_Buttons);

	verticalLayout_Scroll->addStretch();//末尾添加一个弹性空间（stretch）

	//设置滚动窗口
	scrollArea->setWidget(scrollAreaWidgetContents);

	verticalLayout->addWidget(scrollArea);
}

void LineTableWidget::pushBackLine(QString comment, QString instruction)
{
	QVBoxLayout* vBoxLayout = qobject_cast<QVBoxLayout*>(this->scrollAreaWidgetContents->layout());
	if (!vBoxLayout) {
		qDebug() << "layout 错误 " << __FILE__ << __LINE__;
		return;
	}
	ALineWidget* aLine = new ALineWidget(this->scrollAreaWidgetContents, comment, instruction);

	vBoxLayout->insertWidget(vBoxLayout->count() - 2, aLine);//最后是两个按钮和一个弹性空间，所以要-2

	//配置连接 发送
	connect(aLine, &ALineWidget::sendSignal, this, &LineTableWidget::sendSignal);

	//启用删除按钮
	if (vBoxLayout->count() == 4) this->pushButton_Remove->setEnabled(true);
}

void LineTableWidget::popBackLine(void)
{
	QVBoxLayout* vBoxLayout = qobject_cast<QVBoxLayout*>(this->scrollAreaWidgetContents->layout());
	if (!vBoxLayout) {
		qDebug() << "layout 错误 " << __FILE__ << __LINE__;
		return;
	}
	int allCount = vBoxLayout->count();
	if (allCount <= 3) {
		qDebug() << "数量错误 " << __FILE__ << __LINE__;
		return;
	}
	// 在布局中移除 ，并从内部列表取出 item (item 仍然存在）
	QLayoutItem* item = vBoxLayout->takeAt(allCount - 3);//QVBoxLayout 中 QLayoutItem 编号从0开始
	if (!item) {
		qDebug() << "item takeAt 失败 " << __FILE__ << __LINE__;
		return;
	}
	// 从 Item 中取出窗口
	QWidget* aLine = item->widget();
	if (aLine) delete aLine;//删除窗口
	else qDebug() << "错误 空指针 " << __FILE__ << __LINE__;

	delete item;// 删除 Item 本身（防止内存泄漏）

	//禁用删除按钮
	if (vBoxLayout->count() <= 3) this->pushButton_Remove->setEnabled(false);
}

ALineWidget* LineTableWidget::getLine(int index)
{
	QVBoxLayout* vBoxLayout = qobject_cast<QVBoxLayout*>(this->scrollAreaWidgetContents->layout());
	if (!vBoxLayout) {
		qDebug() << "layout 错误 " << __FILE__ << __LINE__;
		return nullptr;
	}
	int allCount = vBoxLayout->count();
	if (index > (allCount - 3)) return nullptr;

	QLayoutItem* item = vBoxLayout->itemAt(index + 1);
	if (!item) return nullptr;

	return qobject_cast<ALineWidget*>(item->widget());
}

void LineTableWidget::setAllButtonsEnable(bool enabled)
{
	int linesCount = this->rowCount();
	if (linesCount <= 0) return;
	for (int i = 0; i < linesCount; i++)
	{
		ALineWidget* aLine = getLine(i);
		if (!aLine) return;
		aLine->setButtonEnable(enabled);
	}
}

int LineTableWidget::rowCount(void)
{
	QVBoxLayout* vBoxLayout = qobject_cast<QVBoxLayout*>(this->scrollAreaWidgetContents->layout());
	if (!vBoxLayout) {
		qDebug() << "layout 错误 " << __FILE__ << __LINE__;
		return 0;
	}
	return (vBoxLayout->count() - 3);
}

QVector<QString> LineTableWidget::getAllQStrings(void)
{
	int linesCount = this->rowCount();
	if (linesCount <= 0) return QVector<QString>();

	QVector<QString> allQStrings;
	allQStrings.reserve(linesCount);
	for (int i = 0; i < linesCount; i++)
	{
		ALineWidget* aLine = getLine(i);
		if(!aLine) return QVector<QString>();
		allQStrings.push_back(aLine->getComment());
		allQStrings.push_back(aLine->getInstruction());
	}

	return allQStrings;
}
