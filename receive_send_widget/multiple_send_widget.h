#pragma once

#include <QWidget>
#include "scrollable_list_widget.h"
namespace Ui {
	class MultipleSendWidget;
}

class ALineWidget;

/**
 * @brief 多项发送窗口
 */
class MultipleSendWidget : public QWidget
{
	Q_OBJECT
private:
	Ui::MultipleSendWidget* ui;

public:
	/**
	 * @brief 构造函数
	 * @param parent 父对象
	 */
	explicit MultipleSendWidget(QWidget* parent = nullptr);
	/**
	 * @brief 析构函数
	 */
	~MultipleSendWidget();

private:
	int rowIndex = 0;//自动发送的当前行号
	bool allowSending = false;//是否允许发送

private:
	/**
	 * @brief 在TabWidget中添加一页
	 * @param tabText 这页标题
	 * @return 添加的 滚动链表窗口
	 */
	ScrollableListWidget* addTabPage(QString tabText = "");
	/**
	 * @brief 在某页中添加一行
	 * @param scroll 对应页的滚动窗口
	 * @return 添加的行
	 */
	ALineWidget* addALine(ScrollableListWidget* scroll);
	/**
	 * @brief 在某页中删除最后一行
	 * @param scroll 对应页的滚动窗口
	 */
	void removeLastLine(ScrollableListWidget* scroll);
	/**
	 * @brief 在TabWidget中移除当前页
	 */
	void removeCurrentTabPage(void);
	/**
	 * @brief 加载所有指令数据文件
	 * @param dirPath 文件夹路径
	 */
	void loadInstructionData(const QString& dirPath);
	/**
	 * @brief 保存所有指令数据到对应文件
	 * @param dirPath 文件夹路径
	 */
	void saveInstructionData(const QString& dirPath);

public:
	/**
	 * @brief 是否允许发送
	 * @param checked 是否
	 */
	void setAllowSending(bool checked);
	/**
	 * @brief 获取用户输入的字符串
	 * @return 用户输入的字符串
	 * @note 用于自动发送
	 */
	QString getUserString();

signals:
	/**
	 * @brief 发送信号
	 * @param str 用户输入的字符串
	 * @note Qt信号
	 */
	void signal_Send(QString str);
signals:
	/**
	 * @brief 请求通知
	 * @param notification 通知文本
	 * @note Qt 信号
	 */
	void signal_Notification(QString notification);
};

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


class TitleWidget : public QWidget
{
	Q_OBJECT
private:
	QHBoxLayout* horizontalLayout;
	QSpacerItem* horizontalSpacer;
	QLabel* label_Comment;
	QSpacerItem* horizontalSpacer_2;
	QLabel* label_Instruction;
	QSpacerItem* horizontalSpacer_3;
	QLabel* label_Send;

	void setupUi();
public:
	TitleWidget(QWidget* parent);
};


class ALineWidget :public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief 构造函数
	 * @param parent 父对象
	 * @param text 标签文本
	 * @param comment 备注字符串
	 * @param instruction 指令字符串
	 */
	explicit ALineWidget(QWidget* parent = nullptr, const QString& text = "", const QString& comment = "", const QString& instruction = "");
private:
	QLabel* label = nullptr;
	QLineEdit* commentEdit = nullptr;
	QLineEdit* instructionEdit = nullptr;
	QPushButton* sendButton = nullptr;

	QHBoxLayout* horizontalLayout = nullptr;
	void setupUi(void);
public:
	/**
	 * @brief 设置标签文本
	 * @param text 标签
	 */
	void setLabelText(const QString& text);
	/**
	 * @brief 获取标签文本
	 * @return 标签文本
	 */
	QString getLabelText(void);
	/**
	 * @brief 获取备注字符串
	 * @return 备注字符串
	 */
	QString getComment(void) const;
	/**
	 * @brief 设置备注
	 * @param 备注字符串
	 */
	void setComment(QString str);
	/**
	 * @brief 获取指令字符串
	 * @return 指令字符串
	 */
	QString getInstruction(void) const;
	/**
	 * @brief 设置指令
	 * @param str 指令字符串
	 */
	void setInstruction(QString str);
	/**
	 * @brief 设置发送按钮能否使用
	 * @param checked 能否使用
	 */
	void setButtonEnable(bool checked);
	/**
	 * @brief 设置指令编辑行的焦点
	 */
	void setInstructionEditFocus();
signals:
	/**
	 * @brief 发送信号
	 * @param str 要发送的字符串
	 * @note Qt信号
	 */
	void signalSend(QString str);
};


class TailWidget :public QWidget
{
	Q_OBJECT
private:
	QHBoxLayout* horizontalLayout;
	QSpacerItem* horizontalSpacer;
	QPushButton* pushButton_Add;
	QPushButton* pushButton_Remove;
	void setupUi();
public:
	TailWidget(QWidget* parent);
	/**
	 * @brief 删除是否可用
	 * @param enabled true 是  false 否
	 */
	void setRemoveEnable(bool enabled);
signals:
	void signalAdd();
signals:
	void signalRemove();
};
