#pragma once

#include <QWidget>
#include <QTimer>
#include <QTableWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCloseEvent>

#include "global.h"
#include "sundry_qt.h"
#include "scrollable_list_widget.h"


namespace Ui {
class MultipleSendWidget;
}

class ALineWidget;

class MultipleSendWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    explicit MultipleSendWidget(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~MultipleSendWidget();

private:
    Ui::MultipleSendWidget *ui;
private:
	bool text = true;//要发送的是否是文本字符串
	bool append = true;//是否追加内容
	QByteArray appendData = QByteArray("\r\n", 2);//要追加内容
	QTimer* timer;//自动发送定时器
	int rowIndex = 0;//自动发送的当前行号
	bool allowSending = false;//是否允许发送

private:
	/**
	 * @brief 根据选项获取要发送的内容
	 * @param dataString 界面中的字符串
	 * @return 要发送的内容
	 */
	QByteArray getSentContent(QString& dataString);
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
	 * @brief 要发送的是否是文本字符串
	 * @param t true 是 false 否
	 */
	void setText(bool t);
	/**
	 * @brief 设置追加内容
	 * @param checked true 追加 false 不追加
	 * @param str 要追加的数据
	 */
	void setAppend(bool a, QByteArray data);
	/**
	 * @brief 设置是否自动发送
	 * @param checked true 是 false 否
	 */
	void setAutoSend(bool a);
	/**
	 * @brief 是否正在自动发送
	 * @return 是否正在自动发送
	 */
	bool isAutoSend(void) const;
	/**
	 * @brief 设置自动发送周期
	 * @param mesc 周期 毫秒
	 */
	void setSendCycle(int mesc);
	/**
	 * @brief 是否允许发送
	 * @param checked 是否
	 */
	void setAllowSending(bool checked);
signals:
	/**
	 * @brief 请求发送
	 * @param str 要发送的数据
	 * @note Qt信号
	 */
	void requestToSend(QByteArray data);
signals:
	/**
	 * @brief 请求通知
	 * @param notification 通知文本
	 * @note Qt 信号
	 */
	void requestToNotification(QString notification);
};




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
