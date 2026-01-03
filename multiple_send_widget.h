#pragma once

#include <QWidget>
#include <QTimer>
#include <QTableWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "global.h"
#include "sundry_qt.h"

class ALineWidget :public QWidget
{
	Q_OBJECT
public: 
	/**
	 * @brief 构造函数
	 * @param parent 父对象
	 * @param comment 备注字符串
	 * @param instruction 指令字符串
	 */
	explicit ALineWidget(QWidget* parent = nullptr, QString comment = "", QString instruction = "");
private:
	QLineEdit* commentEdit = nullptr;
	QLineEdit* instructionEdit = nullptr;
	QPushButton* sendButton = nullptr;

	QHBoxLayout* horizontalLayout = nullptr;
	void setupUi(void);
public:
	/**
	 * @brief 获取备注字符串
	 * @return 备注字符串
	 */
	QString getComment(void) const;
	/**
	 * @brief 获取指令字符串
	 * @return 指令字符串
	 */
	QString getInstruction(void) const;
	/**
	 * @brief 设置发送按钮能否使用
	 * @param checked 能否使用
	 */
	void setButtonEnable(bool checked);
signals:
	/**
	 * @brief 发送信号
	 * @param data 要发送的数据
	 * @note Qt信号
	 */
	void sendSignal(QString data);
};

class LineTableWidget :public QWidget
{
	Q_OBJECT
public:
	explicit LineTableWidget(QWidget* parent = nullptr);
private:
	QVBoxLayout* verticalLayout;
	QScrollArea* scrollArea;
	QWidget* scrollAreaWidgetContents;
	QVBoxLayout* verticalLayout_Scroll;

	QWidget* widget_Labels;
	QHBoxLayout* horizontalLayout_2;
	QSpacerItem* horizontalSpacer_2;
	QLabel* label_Comment;
	QSpacerItem* horizontalSpacer_3;
	QLabel* label_Instruction;
	QSpacerItem* horizontalSpacer_4;
	QLabel* label_Send;
	QWidget* widget_Buttons;
	QHBoxLayout* horizontalLayout;
	QSpacerItem* horizontalSpacer;
	QPushButton* pushButton_Add;
	QPushButton* pushButton_Remove;
	
	void setupUi(void);
	
public:
	/**
	 * @brief 添加一行
	 * @param comment 备注
	 * @param instruction 指令 
	 */
	void pushBackLine(QString comment = "", QString instruction = "");
	/**
	 * @brief 删除最后一行
	 */
	void popBackLine(void);

	/**
	 * @brief 取得某行
	 * @param index 索引
	 * @return ALineWidget 指针 成功
	 * @return nullptr 失败
	 */
	ALineWidget* getLine(int index);
	/**
	 * @brief 设置所有按钮 enable
	 * @param enabled 是否使用
	 */
	void setAllButtonsEnable(bool enabled);

	/**
	 * @brief 一共多少行
	 * @return 行数
	 */
	int rowCount(void);
	/**
	 * @brief 获取本窗口中所有字符串
	 * @return 本窗口中所有字符串
	 */
	QVector<QString> getAllQStrings(void);
signals:
	void sendSignal(QString comment);
};

namespace Ui {
class MultipleSendWidget;
}

class MultipleSendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleSendWidget(QWidget *parent = nullptr);
    ~MultipleSendWidget();

private:
    Ui::MultipleSendWidget *ui;
private:
	bool text = true;//要发送的是否是文本字符串
	bool append = true;//是否追加内容
	QByteArray appendData = QByteArray("\r\n", 2);//要追加内容
	QTimer* timer;//自动发送定时器
	int currentRow = 0;//自动发送的当前行号
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
	 */
	void addTabPage(void);
	/**
	 * @brief 在TabWidget中移除当前页
	 */
	void removeCurrentTabPage(void);
	/**
	 * @brief 导入.csv表格文件
	 * @param fileName 文件完整路径
	 */
	void ImportCsvFile(QString fileName);
public:
	/**
	 * @brief 要发送的是否是文本字符串
	 * @param t true 是 false 否
	 */
	void setText(bool t);
	/**
	 * @brief 设置追加内容
	 * @param checked true 追加 false 不追加
	 * @param data 要追加的数据
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
	 * @param data 要发送的数据
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

