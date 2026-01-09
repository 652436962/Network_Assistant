#include "scrollable_list_widget.h"


ScrollableListWidget::ScrollableListWidget(QWidget* parent)
	: QWidget(parent)
{
	setupUi();
}

void ScrollableListWidget::setTitleWidget(QWidget* title)
{
	// 彻底移除旧标题（包括 layout item）
	if (titleWidget) {		
		QLayoutItem* item = vBoxLayout_Scroll->takeAt(0);
		delete item; //删除 item 不会 delete widget
		delete titleWidget;//删除 窗口
	}

	//添加新的标题窗口
	if (title == nullptr) title = new QWidget();//title为nullptr，新建一个没有内容的窗口
	title->setParent(scrollAreaWidget);

	this->titleWidget = title;
	
	vBoxLayout_Scroll->insertWidget(0, titleWidget);// 插入到最前面（index 0）
}

QWidget* ScrollableListWidget::getTitleWidget(void) const
{
	return this->titleWidget;
}

void ScrollableListWidget::setTailWidget(QWidget* tail)
{
	// 移除旧尾部窗口
	if (this->tailWidget) {
		int index = this->vBoxLayout_Scroll->count() - 1 - 1;
		QLayoutItem* item = vBoxLayout_Scroll->takeAt(index);
		delete item;//删除 item
		delete this->tailWidget;//删除窗口		
	}

	//添加新的结尾窗口
	if (tail == nullptr) tail = new QWidget();// 创建新尾部	
	tail->setParent(scrollAreaWidget);
	
	this->tailWidget = tail;

	// 插入到弹簧之前：即倒数第一个 widget 位置（这时没有尾部）
	// 布局结构：[title][user widgets...][tail][spacer]
	// 所以 tail 应该在 index = count() - 1（因为 spacer 是最后一个 item）
	int insertIndex = vBoxLayout_Scroll->count() - 1; // spacer 在最后，tail 插在它前面
	vBoxLayout_Scroll->insertWidget(insertIndex, tailWidget);
}

QWidget* ScrollableListWidget::getTailWidget(void) const
{
	return this->tailWidget;
}

void ScrollableListWidget::setupUi()
{
	// 滚动区域
	scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	// 滚动内容窗口
	scrollAreaWidget = new QWidget(this);
	vBoxLayout_Scroll = new QVBoxLayout(scrollAreaWidget);
	vBoxLayout_Scroll->setContentsMargins(0, 0, 0, 0);
	vBoxLayout_Scroll->setSpacing(0);

	// 添加标题窗口
	titleWidget = new QWidget(scrollAreaWidget);
	vBoxLayout_Scroll->addWidget(titleWidget);

	//添加结尾窗口
	tailWidget = new QWidget(scrollAreaWidget);
	vBoxLayout_Scroll->addWidget(tailWidget);

	// 添加弹簧 在最底部
	spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	vBoxLayout_Scroll->addItem(spacer);

	// 设置滚动区域内容
	scrollArea->setWidget(scrollAreaWidget);

	// 主布局
	vBoxLayout_This = new QVBoxLayout(this);
	vBoxLayout_This->setContentsMargins(0, 0, 0, 0);
	vBoxLayout_This->setSpacing(0);
	vBoxLayout_This->addWidget(scrollArea);
}

// --- 公共接口实现 ---

size_t ScrollableListWidget::count() const
{
	return widgetsList.size();
}

bool ScrollableListWidget::empty() const
{
	return widgetsList.empty();
}

void ScrollableListWidget::clear()
{
	for (QWidget* w : widgetsList) {
		vBoxLayout_Scroll->removeWidget(w);
		delete w;
	}
	widgetsList.clear();
}

void ScrollableListWidget::push_back(QWidget* val)
{
	if (!val) return;
	val->setParent(scrollAreaWidget);

	// 插入到尾部之前，索引从0开始 最后有尾部和弹簧所以 count()  - 1 -1
	int insertIndex = vBoxLayout_Scroll->count() - 1 - 1;
	vBoxLayout_Scroll->insertWidget(insertIndex, val);
	widgetsList.push_back(val);
}

void ScrollableListWidget::push_front(QWidget* val)
{
	if (!val) return;
	val->setParent(scrollAreaWidget);

	// 插入到 标题之后 索引 1
	vBoxLayout_Scroll->insertWidget(1, val);
	widgetsList.push_front(val);
}

int ScrollableListWidget::insert(int pos, QWidget* val)
{
	if (!val || pos < 0 || pos > widgetsList.count())
		return -1;

	val->setParent(scrollAreaWidget);

	// 插入位置 = index（因为有标题，窗口从1开始）
	vBoxLayout_Scroll->insertWidget(pos + 1, val);
	widgetsList.insert(pos, val);
	return pos;
}

void ScrollableListWidget::pop_back()
{
	if (widgetsList.empty()) return;

	QWidget* w = widgetsList.back();
	int index = vBoxLayout_Scroll->indexOf(w);
	if (index == -1) return;

	this->widgetsList.pop_back();//在记录链表中删除最后一个
	QLayoutItem* item = vBoxLayout_Scroll->takeAt(index);//在 vBoxLayout_Scroll 的记录中链表中移除
	delete item;
	delete w;
}

void ScrollableListWidget::pop_front()
{
	if (widgetsList.empty()) return;

	QWidget* w = widgetsList.front();
	int index = vBoxLayout_Scroll->indexOf(w);
	if (index == -1) return;

	this->widgetsList.pop_front();//在记录链表中删除开头的
	QLayoutItem* item = vBoxLayout_Scroll->takeAt(index);//在 vBoxLayout_Scroll 的记录中链表中移除
	delete item;
	delete w;
	
}

int ScrollableListWidget::erase(int pos)
{
	if (pos < 0 || pos >= widgetsList.size())
		return -1;

	QWidget* w = this->widgetsList.at(pos);//找到对应窗口

	int index = vBoxLayout_Scroll->indexOf(w);
	if (index == -1) return -1;

	this->widgetsList.takeAt(pos);//在记录链表中移除
	QLayoutItem* item = vBoxLayout_Scroll->takeAt(index);//在 vBoxLayout_Scroll 的记录中链表中移除
	delete item;
	delete w;
	return pos;
}

void ScrollableListWidget::remove(QWidget* value)
{
	if (!value) return;

	int listIndex = widgetsList.indexOf(value);
	if (listIndex == -1) return; // not found

	int layoutIndex = vBoxLayout_Scroll->indexOf(value);
	if (layoutIndex == -1) return;

	widgetsList.removeAt(listIndex);//在记录链表中移除
	QLayoutItem* item = vBoxLayout_Scroll->takeAt(layoutIndex);//在 vBoxLayout_Scroll 的记录中链表中移除
	delete item;//删除item
	delete value;//删除窗口
}

QWidget* ScrollableListWidget::front()
{
	return widgetsList.front();
}
QWidget* ScrollableListWidget::back()
{
	return widgetsList.back();
}

QWidget* ScrollableListWidget::at(int index) const
{
	return this->widgetsList.at(index);
}

/*注意
* QLayout::removeWidget() ≠ 从布局中删除！
* layout->removeWidget(w)：仅将 widget 从 layout 的管理中移除，但 layout 中仍然保留一个 空的 QLayoutItem 占位符！
* delete layout->takeAt(index);  // takeAt 返回 QLayoutItem*，delete 它才会彻底移除
* item 和 对应窗口 要分别删除
*/

/*insertWidget
* 核心行为：将新 widget 插入到指定 index 位置，原该位置及之后的所有 widget 向后移动一位。
* 索引范围处理（Qt 的容错机制）：
* 如果 index < 0 → 自动视为 0（插入最前面）
* 如果 index >= count() → 自动视为 count()（插入最后面）
*/

/*关于 QLayout 
* QLayout（包括 QVBoxLayout、QHBoxLayout 等）内部维护一个 QLayoutItem* 的列表
* 
* QLayoutItem* itemAt(int index) const
* 返回索引 index 处的布局项指针，但不改变布局本身。只读访问
* 
* QLayoutItem* takeAt(int index)
* 从布局中移除索引 index 处的布局项，并将所有权转移给你。
* 
*/