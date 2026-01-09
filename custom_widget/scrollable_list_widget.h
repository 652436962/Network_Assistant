#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QSpacerItem>

/**
 * @brief 滚动链表窗口
 */
class ScrollableListWidget : public QWidget
{
	Q_OBJECT
private:
	QVBoxLayout* vBoxLayout_This;//本窗口布局
	QScrollArea* scrollArea;//滚动区类
	QWidget* scrollAreaWidget;//要滚动的窗口
	QVBoxLayout* vBoxLayout_Scroll;//滚动窗口布局

	QWidget* titleWidget;//标题窗口
	QList<QWidget*> widgetsList;//保存所有加入的窗口的指针的链表，便于之后处理
	QWidget* tailWidget;//尾部窗口
	QSpacerItem* spacer;//最底下的弹簧
private:
	/**
	 * @brief 设置 Ui
	 */
	void setupUi();
public:
	/**
	 * @brief 构造函数
	 * @param parent 父对象
	 */
	explicit ScrollableListWidget(QWidget* parent = nullptr);
	/**
	 * @brief 设置标题窗口
	 * @param title 标题 传入 nullptr 设置标题为空的窗口 
	 */
	void setTitleWidget(QWidget* title = nullptr);
	/**
	 * @brief 获取标题窗口
	 * @return 标题窗口
	 */
	QWidget* getTitleWidget(void) const;
	/**
	 * @brief 设置结尾窗口
	 * @param tail 结尾 传入 nullptr 设置结尾为空的窗口
	 */
	void setTailWidget(QWidget* tail = nullptr);
	/**
	 * @brief 获取结尾窗口
	 * @return 结尾窗口
	 */
	QWidget* getTailWidget(void) const;
public:
	// 容量与大小
	/**
	 * @brief 当前加入的窗口的个数
	 * @return 当前加入的窗口的个数
	 */
	size_t count() const;
	/**
	 * @brief 检查“链表窗口”是否为空
	 * @return true 空
	 * @return false 非空
	 */
	bool empty() const;

	//元素访问

	/**
	 * @brief 返回第一个窗口
	 * @return 第一个窗口
	 */
	QWidget* front();
	/**
	 * @brief 返回最后一个窗口
	 * @return 最后一个窗口
	 */
	QWidget* back();
	/**
	 * @brief 按索引取得窗口
	 * @param index 索引
	 * @return 窗口
	 * @note std::list 中没有
	 */
	QWidget* at(int index) const;

	// 修改器
	/**
	 * @brief 在尾部插入一个窗口
	 * @param val 要插入的窗口
	 */
	void push_back(QWidget* val);
	/**
	 * @brief 删除最后一个窗口
	 */
	void pop_back();
	/**
	 * @brief 在头部插入一个窗口
	 * @param val 要插入的窗口
	 */
	void push_front(QWidget* val);
	/**
	 * @brief 删除第一个窗口
	 */
	void pop_front();
	/**
	 * @brief 在 索引 pos 前插入一个窗口
	 * @param pos 索引
	 * @param val 要插入的窗口
	 * @return 新窗口索引
	 */
	int insert(int pos, QWidget* val);	
	/**
	 * @brief 删除 索引 index 的窗口
	 * @param pos 索引
	 * @return 被删除窗口之后窗口的索引
	 */
	int erase(int pos);
	/**
	 * @brief 移除所有窗口
	 */
	void clear();

	// 链表特有

	/**
	 * @brief 移除窗口
	 * @param value 要移除的窗口
	 */
	void remove(QWidget* value);	
};