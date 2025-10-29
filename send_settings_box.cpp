#include "send_settings_box.h"

#include <QPainter>

#include "sundry.h"

SendSettingsBox::SendSettingsBox(QWidget* parent)
	: QGroupBox(parent)
{
	this->setupUi();

	// 添加发送区选项
	comboBox_Option->addItem("单项发送", QVariant::fromValue<SendOptions>(SendOptions::single));
	comboBox_Option->addItem("多项发送", QVariant::fromValue<SendOptions>(SendOptions::multiple));
	int optionIndex = this->comboBox_Option->findData(QVariant::fromValue<SendOptions>(SendOptions::single)); // 默认单项发送
	this->comboBox_Option->setCurrentIndex(optionIndex);
}

SendSettingsBox::~SendSettingsBox()
{
	qDebug() << "发送设置窗口关闭";
}


void SendSettingsBox::setupUi(void)
{
	if (this->objectName().isEmpty())
		this->setObjectName("SendSettingsBox");
	this->resize(200, 180);
	this->setMinimumSize(QSize(200, 180));
	QFont font;
	font.setPointSize(10);
	this->setFont(font);
	gridLayout = new QGridLayout(this);
	gridLayout->setObjectName("gridLayout");
	label_Option = new QLabel(this);
	label_Option->setObjectName("label_Option");
	label_Option->setMaximumSize(QSize(150, 150));
	label_Option->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignTrailing | Qt::AlignmentFlag::AlignVCenter);

	gridLayout->addWidget(label_Option, 0, 0, 1, 1);

	comboBox_Option = new QComboBox(this);
	comboBox_Option->setObjectName("comboBox_Option");
	comboBox_Option->setMaximumSize(QSize(150, 24));

	gridLayout->addWidget(comboBox_Option, 0, 1, 1, 2);

	radioButton_Text = new QRadioButton(this);
	radioButton_Text->setObjectName("radioButton_Text");
	radioButton_Text->setMaximumSize(QSize(150, 32));
	radioButton_Text->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
	radioButton_Text->setChecked(true);

	gridLayout->addWidget(radioButton_Text, 1, 0, 1, 1);

	radioButton_HEX = new QRadioButton(this);
	radioButton_HEX->setObjectName("radioButton_HEX");
	radioButton_HEX->setMaximumSize(QSize(150, 32));
	radioButton_HEX->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

	gridLayout->addWidget(radioButton_HEX, 1, 1, 1, 2);

	checkBox_Append = new QCheckBox(this);
	checkBox_Append->setObjectName("checkBox_Append");
	checkBox_Append->setMaximumSize(QSize(150, 32));
	checkBox_Append->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
	checkBox_Append->setChecked(true);

	gridLayout->addWidget(checkBox_Append, 2, 0, 1, 1);

	comboBox_Append = new QComboBox(this);
	comboBox_Append->addItem(QString());
	comboBox_Append->addItem(QString());
	comboBox_Append->addItem(QString());
	comboBox_Append->setObjectName("comboBox_Append");
	comboBox_Append->setMaximumSize(QSize(150, 24));

	gridLayout->addWidget(comboBox_Append, 2, 1, 1, 2);

	checkBox_AutoSend = new QCheckBox(this);
	checkBox_AutoSend->setObjectName("checkBox_AutoSend");
	checkBox_AutoSend->setEnabled(true);
	checkBox_AutoSend->setMaximumSize(QSize(150, 32));
	checkBox_AutoSend->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

	gridLayout->addWidget(checkBox_AutoSend, 3, 0, 1, 1);

	horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

	gridLayout->addItem(horizontalSpacer, 3, 1, 1, 2);

	label_AutoSendCycle = new QLabel(this);
	label_AutoSendCycle->setObjectName("label_AutoSendCycle");
	label_AutoSendCycle->setEnabled(true);
	label_AutoSendCycle->setMaximumSize(QSize(16777215, 32));

	gridLayout->addWidget(label_AutoSendCycle, 4, 0, 1, 1);

	spinBox_AutoSendCycle = new QSpinBox(this);
	spinBox_AutoSendCycle->setObjectName("spinBox_AutoSendCycle");
	spinBox_AutoSendCycle->setEnabled(true);
	spinBox_AutoSendCycle->setMaximumSize(QSize(16777215, 24));
	spinBox_AutoSendCycle->setMaximum(99999);
	spinBox_AutoSendCycle->setValue(500);

	gridLayout->addWidget(spinBox_AutoSendCycle, 4, 1, 1, 1);

	label_MS = new QLabel(this);
	label_MS->setObjectName("label_MS");
	label_MS->setEnabled(true);
	label_MS->setMaximumSize(QSize(16777215, 32));

	gridLayout->addWidget(label_MS, 4, 2, 1, 1);


	retranslateUi();

	QMetaObject::connectSlotsByName(this);
} // setupUi

void SendSettingsBox::retranslateUi(void)
{
	this->setWindowTitle(QCoreApplication::translate("SendSettingsBox", "Form", nullptr));
	label_Option->setText(QCoreApplication::translate("SendSettingsBox", "\345\217\221\351\200\201\351\200\211\351\241\271", nullptr));
	radioButton_Text->setText(QCoreApplication::translate("SendSettingsBox", "\345\217\221\351\200\201\346\226\207\346\234\254", nullptr));
	radioButton_HEX->setText(QCoreApplication::translate("SendSettingsBox", "\345\217\221\351\200\201HEX", nullptr));
	checkBox_Append->setText(QCoreApplication::translate("SendSettingsBox", "\350\207\252\345\212\250\350\277\275\345\212\240", nullptr));
	comboBox_Append->setItemText(0, QCoreApplication::translate("SendSettingsBox", "\346\215\242\350\241\214 \"\\r\\n\"", nullptr));
	comboBox_Append->setItemText(1, QCoreApplication::translate("SendSettingsBox", "\346\215\242\350\241\214 \"\\n\"", nullptr));
	comboBox_Append->setItemText(2, QCoreApplication::translate("SendSettingsBox", "\347\251\272\345\255\227\347\254\246 \"\\0\"", nullptr));

	checkBox_AutoSend->setText(QCoreApplication::translate("SendSettingsBox", "\350\207\252\345\212\250\345\217\221\351\200\201", nullptr));
	label_AutoSendCycle->setText(QCoreApplication::translate("SendSettingsBox", "\350\207\252\345\212\250\345\217\221\351\200\201\345\221\250\346\234\237", nullptr));
	label_MS->setText(QCoreApplication::translate("SendSettingsBox", "ms", nullptr));
} // retranslateUi



//void SendSettingsWidget::paintEvent(QPaintEvent* event)
//{
//    // 1. 先调用父类的 paintEvent，确保正常绘制背景和子控件
//    QWidget::paintEvent(event);
//    // 2. 使用 QPainter 绘制虚线边框
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, false); // 边框不需要抗锯齿
//
//    // 3. 创建虚线画笔
//    QPen pen;
//    pen.setColor(QColor("#aaaaaa"));  // 灰色
//    pen.setWidth(1);
//    pen.setStyle(Qt::DashLine);       // 虚线样式
//    pen.setDashPattern({ 2, 2 });       // 2像素实线，2像素空隙（可调）
//    painter.setPen(pen);
//
//    // 4. 计算绘制矩形（避开边缘，留出边框空间）
//    QRect rect = this->rect();
//    rect.adjust(1, 1, -1, -1); // 缩小1像素，防止边框被裁剪
//
//    // 5. 绘制矩形边框
//    painter.drawRect(rect);
//}
