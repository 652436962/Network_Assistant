#include "multiple_send_widget.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QScrollArea>
#include <QTableWidget>
#include <QTextCodec>
#include <QDesktopServices>


MultipleSendWidget::MultipleSendWidget(QWidget* parent)
	: QWidget(parent)
{
	this->setupUi();

	while (this->tabWidget->count() > 0) // 开始清空tabWidget
	{
		this->tabWidget->removeTab(0); // 索引会变更
	}

	this->timer = new QTimer(this);
	this->timer->stop();
	this->timer->setTimerType(Qt::PreciseTimer);//ms级精度
	this->timer->setSingleShot(false); // 循环
	this->timer->setInterval(500);
	//定时到了
	connect(this->timer, &QTimer::timeout, [this]() {
		if (this->tabWidget->count() <= 0) return;

		// 获取当前窗口
		ScrollableListWidget* scroll = qobject_cast<ScrollableListWidget*>(this->tabWidget->currentWidget());
		if (!scroll) return;

		// 获取当前行的指令
		ALineWidget* aLine = qobject_cast<ALineWidget*>(scroll->at(this->rowIndex));
		if (!aLine) return;

		aLine->setInstructionEditFocus();
		QString command = aLine->getInstruction();
		QByteArray sendData = this->getSentContent(command);
		emit this->requestToSend(sendData);//请求发送

		// 更新索引（下一行）
		this->rowIndex++;
		if (this->rowIndex >= scroll->count()) this->rowIndex = 0; // 回到第一行，实现循环
		});
	//切换页后 自动发送当前行归0
	connect(this->tabWidget, &QTabWidget::currentChanged, [this]() {this->rowIndex = 0; });

	// 配置连接 添加一页
	connect(this->pushButton_Add, &QPushButton::clicked, [this]() {
		ScrollableListWidget* scroll = this->addTabPage();
		// 开始就有 5 行
		for (int i = 0; i < 5; i++) this->addALine(scroll);
		});

	// 配置连接 移除当前页
	connect(this->pushButton_Delete, &QPushButton::clicked, this, &MultipleSendWidget::removeCurrentTabPage);

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

	//配置连接 打开文件保存目录
	connect(this->pushButton_Location, &QPushButton::clicked, [this]() {
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

	/*加载记录文件*/
	this->loadInstructionData(dataDirPath);

	//开始没有就来一页
	if (this->tabWidget->count() == 0)
	{
		ScrollableListWidget* scroll = this->addTabPage();
		// 开始就有 5 行
		for (int i = 0; i < 5; i++) this->addALine(scroll);
	}
}

void MultipleSendWidget::setupUi()
{
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(2);
	verticalLayout->setContentsMargins(2, 2, 2, 2);
	tabWidget = new EditableTabWidget(this);
	tabWidget->setTabPosition(QTabWidget::TabPosition::South);
	tabWidget->setTabBarAutoHide(false);

	verticalLayout->addWidget(tabWidget);

	widget_Button = new QWidget(this);
	widget_Button->setMinimumSize(QSize(0, 32));
	widget_Button->setMaximumSize(QSize(16777215, 64));
	horizontalLayout = new QHBoxLayout(widget_Button);
	horizontalLayout->setSpacing(8);
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	horizontalSpacer_2 = new QSpacerItem(37, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer_2);

	pushButton_Location = new QPushButton(widget_Button);

	horizontalLayout->addWidget(pushButton_Location);

	horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer);

	pushButton_Add = new QPushButton(widget_Button);

	horizontalLayout->addWidget(pushButton_Add);

	pushButton_Delete = new QPushButton(widget_Button);

	horizontalLayout->addWidget(pushButton_Delete);


	verticalLayout->addWidget(widget_Button);



	tabWidget->setCurrentIndex(0);

	pushButton_Location->setText("保存位置");
	pushButton_Add->setText("添加一页");
	pushButton_Delete->setText("删除此页");
}

MultipleSendWidget::~MultipleSendWidget()
{
	/*保存当前数据到记录文件*/
	QString appDirPath = QCoreApplication::applicationDirPath(); // 获取 .exe 所在的目录
	QString dataDirPath = appDirPath + "/multiple_data_files"; // 构造目标文件夹路径
	QDir dataDir(dataDirPath);
	bool result = false;
	if (!dataDir.exists())//文件夹不存在
	{
		result = QDir().mkpath(dataDirPath);//创建文件夹
	}
	else result = true;
	if (result)
		this->saveInstructionData(dataDirPath);//保存数据

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
	for (int i = 0; i < this->tabWidget->count(); i++)
	{
		ScrollableListWidget* scroll = qobject_cast<ScrollableListWidget*>(this->tabWidget->currentWidget());
		if (!scroll) continue;
		for (int j = 0; j < scroll->count(); j++)
		{
			ALineWidget* aLine = qobject_cast<ALineWidget*>(scroll->at(j));
			if (!aLine) continue;
			aLine->setButtonEnable(checked);
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

ScrollableListWidget* MultipleSendWidget::addTabPage(QString tabText)
{
	ScrollableListWidget* scrollWidget = new ScrollableListWidget(this->tabWidget);
	TitleWidget* title = new TitleWidget(scrollWidget);
	scrollWidget->setTitleWidget(title);

	TailWidget* tail = new TailWidget(scrollWidget);
	tail->setRemoveEnable(false);//开始没有，因此删除不可用
	scrollWidget->setTailWidget(tail);

	//加入到 tabWidget 中	
	int pageCount = this->tabWidget->count();
	if (tabText == "") tabText = QString::number(pageCount);//传入空，就用索引的数字
	this->tabWidget->addTab(scrollWidget, tabText);

	//配置连接 添加一行
	connect(tail, &TailWidget::signalAdd, [scrollWidget, this]() {
		this->addALine(scrollWidget);
		});
	//配置连接 删除最后一行
	connect(tail, &TailWidget::signalRemove, [scrollWidget, this]() {
		this->removeLastLine(scrollWidget);
		});

	return scrollWidget;
}

ALineWidget* MultipleSendWidget::addALine(ScrollableListWidget* scroll)
{
	int index = scroll->count();
	ALineWidget* line = new ALineWidget(scroll, QString::number(index));

	line->setButtonEnable(this->allowSending);
	scroll->push_back(line);
	//配置连接 发送
	connect(line, &ALineWidget::signalSend, [this](QString str) {
		QByteArray data = this->getSentContent(str);
		emit this->requestToSend(data);
		});
	//有“行”了
	if (!(scroll->empty()))
	{
		TailWidget* tail = qobject_cast<TailWidget*>(scroll->getTailWidget());
		if (!tail) return nullptr;
		tail->setRemoveEnable(true);//启用删除按钮
	}
	return line;
}

void MultipleSendWidget::removeLastLine(ScrollableListWidget* scroll)
{
	scroll->pop_back();
	//没有“行”了
	if (scroll->empty())
	{
		TailWidget* tail = qobject_cast<TailWidget*>(scroll->getTailWidget());
		if (!tail) return;
		tail->setRemoveEnable(false);//禁用删除按钮
	}
}

void MultipleSendWidget::removeCurrentTabPage(void)
{
	if (this->tabWidget->count() <= 0) return;

	int index = this->tabWidget->currentIndex();
	QWidget* widget = this->tabWidget->widget(index);
	if (widget)
	{
		this->tabWidget->removeTab(index);
		delete widget;
	}
	else
	{
		qDebug() << "错误 空指针 " << __FILE__ << __LINE__;
	}
}

void MultipleSendWidget::loadInstructionData(const QString& dirPath)
{
	QDir dir(dirPath);
	if (!dir.exists()) return;

	//设置过滤器：只列出文件（不含子目录），且以 .bin 结尾（不区分大小写）
	dir.setFilter(QDir::Files);
	dir.setNameFilters(QStringList() << "*.bin");

	//获取所有匹配的文件名（仅文件名，不含路径）
	QFileInfoList fileInfoList = dir.entryInfoList();

	//遍历所有 .bin 文件
	for (const QFileInfo& fileInfo : fileInfoList)
	{
		QString filePath = fileInfo.absoluteFilePath();// 完整路径
		QString baseName = fileInfo.baseName();//文件名主体
		//加载文件
		QStringList stringList = loadQStringList(filePath);
		if (stringList.empty()) continue;
		ScrollableListWidget* scroll = this->addTabPage(baseName);

		ALineWidget* line = nullptr;
		for (int i = 0; i < stringList.size(); i++)//添加行
		{
			if (i % 2 == 0)//偶数索引
			{
				line = this->addALine(scroll);//添加新行
				line->setComment(stringList.at(i));//设置备注字符串
			}
			else// 奇数索引
			{
				if (!line) continue;
				line->setInstruction(stringList.at(i));
			}

		}
	}
}

void MultipleSendWidget::saveInstructionData(const QString& dirPath)
{
	QDir dataDir(dirPath);
	if (!dataDir.exists()) return;

	int scrollCount = this->tabWidget->count();//窗口总数
	if (scrollCount <= 0) return;

	//遍历所有窗口
	for (int i = 0; i < scrollCount; i++)
	{
		ScrollableListWidget* scroll = qobject_cast<ScrollableListWidget*>(this->tabWidget->widget(i));
		if (!scroll) continue;
		int lineCount = scroll->count();
		if (lineCount <= 0) continue;
		QString fileName = this->tabWidget->tabText(i) + ".bin";//文件名为对应页标签+".bin"
		QStringList stringList;//保存本页所有指令
		for (int j = 0; j < lineCount; j++)
		{
			ALineWidget* line = qobject_cast<ALineWidget*>(scroll->at(j));
			if (!line) continue;
			stringList.append(line->getComment());//备注
			stringList.append(line->getInstruction());//指令
		}
		QString filePath = dirPath + "/" + fileName;
		qDebug() << "保存" << this->tabWidget->tabText(i) << "数据到 " << filePath;
		bool saveResult = saveQStringList(filePath, stringList);
		qDebug() << (saveResult ? "成功" : "失败");
	}

}

ALineWidget::ALineWidget(QWidget* parent, const QString& text, const QString& comment, const QString& instruction) : QWidget(parent)
{
	this->setupUi();

	this->label->setText(text);
	this->commentEdit->setText(comment);
	this->instructionEdit->setText(instruction);

	connect(sendButton, &QPushButton::clicked, [this]() {
		emit signalSend(instructionEdit->text());
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

	//索引标签
	label = new QLabel(this);
	horizontalLayout->addWidget(label);

	//备注编辑框
	commentEdit = new QLineEdit(this);

	horizontalLayout->addWidget(commentEdit);

	//指令编辑框
	instructionEdit = new QLineEdit(this);

	horizontalLayout->addWidget(instructionEdit);

	//发送按钮
	sendButton = new QPushButton(this);
	sendButton->setMinimumSize(QSize(16, 16));
	sendButton->setMaximumSize(QSize(24, 24));
	sendButton->setIcon(QIcon(":/icon/image/send.png"));

	horizontalLayout->addWidget(sendButton);
}

void ALineWidget::setLabelText(const QString& text)
{
	this->label->setText(text);
}

QString ALineWidget::getLabelText(void)
{
	return this->label->text();
}

QString ALineWidget::getComment(void) const
{
	return commentEdit->text();
}

void ALineWidget::setComment(QString str)
{
	this->commentEdit->setText(str);
}

QString ALineWidget::getInstruction(void) const
{
	return instructionEdit->text();
}

void ALineWidget::setInstruction(QString str)
{
	this->instructionEdit->setText(str);
}

void ALineWidget::setButtonEnable(bool checked)
{
	sendButton->setEnabled(checked);
}

void ALineWidget::setInstructionEditFocus()
{
	instructionEdit->setFocus();
}



TitleWidget::TitleWidget(QWidget* parent) :QWidget(parent)
{
	setupUi();
}

void TitleWidget::setupUi()
{
	this->resize(275, 32);
	this->setMinimumSize(QSize(128, 32));
	this->setMaximumSize(QSize(512, 64));
	QFont font;
	font.setPointSize(12);
	this->setFont(font);
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(2);
	horizontalLayout->setContentsMargins(2, 2, 2, 2);
	horizontalSpacer = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer);

	label_Comment = new QLabel("备注", this);

	horizontalLayout->addWidget(label_Comment);

	horizontalSpacer_2 = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer_2);

	label_Instruction = new QLabel("指令", this);

	horizontalLayout->addWidget(label_Instruction);

	horizontalSpacer_3 = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer_3);

	label_Send = new QLabel("发送", this);

	horizontalLayout->addWidget(label_Send);
}



TailWidget::TailWidget(QWidget* parent) :QWidget(parent)
{
	this->setupUi();
	connect(this->pushButton_Add, &QPushButton::clicked, [this]() {
		emit this->signalAdd(); });
	connect(this->pushButton_Remove, &QPushButton::clicked, [this]() {
		emit this->signalRemove(); });
}
void TailWidget::setRemoveEnable(bool enabled)
{
	this->pushButton_Remove->setEnabled(enabled);
}
void TailWidget::setupUi()
{
	this->resize(374, 32);
	this->setMinimumSize(QSize(128, 32));
	this->setMaximumSize(QSize(512, 48));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(4);
	horizontalLayout->setContentsMargins(2, 2, 2, 2);
	horizontalSpacer = new QSpacerItem(209, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	horizontalLayout->addItem(horizontalSpacer);

	pushButton_Add = new QPushButton("添加一行", this);

	horizontalLayout->addWidget(pushButton_Add);

	pushButton_Remove = new QPushButton("删除一行", this);

	horizontalLayout->addWidget(pushButton_Remove);
}