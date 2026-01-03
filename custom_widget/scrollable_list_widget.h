#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QSpacerItem>

/**
 * @brief 滚动链表窗口
 */
class ScrollableListWidget : public QWidget
{
private:
	QVBoxLayout* vBoxLayout_This;//本窗口布局
	QScrollArea* scrollArea;//滚动区类
	QWidget* scrollAreaWidget;//要滚动的窗口
	QVBoxLayout* vBoxLayout_Scroll;//滚动窗口布局

	QWidget* titleWidget_ = nullptr;//标题窗口 不在 widgetesList 中记录
	QList<QWidget*> widgetsList;//保存所有加入的窗口的指针，便于之后处理	
	QWidget* tailWidget_ = nullptr;//结尾窗口 不在 widgetesList 中记录
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
	explicit ScrollableListWidget(QWidget* parent);
	/**
	 * @brief 设置标题窗口
	 * @param titleWidget 标题窗口
	 */
	void setTitleWidget(QWidget* titleWidget);
	/**
	 * @brief 设置结尾窗口
	 * @param tailWidget 结尾窗口
	 */
	void setTailWidget(QWidget* tailWidget);

public:
	/**
	 * @brief 当前加入的窗口的个数
	 * @return 当前加入的窗口的个数
	 */
	size_t size() const;
	/**
	 * @brief 检查“链表窗口”是否为空
	 * @return true 空
	 * @return false 非空
	 */
	bool empty() const;
	/**
	 * @brief 移除所有窗口
	 */
	void clear();
	
	/**
	 * @brief 在尾部插入一个窗口
	 * @param val 要插入的窗口
	 */
	void push_back(QWidget* val);
	/**
	 * @brief 在头部插入一个窗口
	 * @param val 要插入的窗口
	 */
	void push_front(QWidget* val);
	/**
	 * @brief 在 索引 index 前插入一个窗口
	 * @param index 索引
	 * @param val 要插入的窗口
	 * @return 新窗口索引
	 */
	int insert(int index, QWidget* val);
	/**
	 * @brief 删除最后一个窗口
	 */
	void pop_back();
	/**
	 * @brief 删除第一个窗口
	 */
	void pop_front();
	/**
	 * @brief 删除 索引 index 的窗口
	 * @param index 索引
	 * @return 被删除窗口之后窗口的索引 （或-1表示末尾）
	 */
	int erase(int index);

};