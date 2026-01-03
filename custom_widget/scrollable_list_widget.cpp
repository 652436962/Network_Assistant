#include "scrollable_list_widget.h"


ScrollableListWidget::ScrollableListWidget(QWidget* parent)
	: QWidget(parent)
{
	setupUi();
}

void ScrollableListWidget::setupUi()
{
	// 创建滚动区域
	scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	// 创建滚动内容窗口
	scrollAreaWidget = new QWidget;
	vBoxLayout_Scroll = new QVBoxLayout(scrollAreaWidget);
	vBoxLayout_Scroll->setContentsMargins(0, 0, 0, 0);
	vBoxLayout_Scroll->setSpacing(0);

	// 添加弹簧（始终在最底部）
	spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	vBoxLayout_Scroll->addItem(spacer);

	// 设置滚动区域的内容
	scrollArea->setWidget(scrollAreaWidget);

	// 本窗口布局
	vBoxLayout_This = new QVBoxLayout(this);
	vBoxLayout_This->setContentsMargins(0, 0, 0, 0);
	vBoxLayout_This->setSpacing(0);
	vBoxLayout_This->addWidget(scrollArea);
}

void ScrollableListWidget::setTitleWidget(QWidget* titleWidget)
{
	// 移除旧标题
	if (titleWidget_) {
		vBoxLayout_Scroll->removeWidget(titleWidget_);
		titleWidget_->deleteLater();
	}
	titleWidget_ = titleWidget;

	// 添加新标题（如果存在）
	if (titleWidget) {
		titleWidget->setParent(scrollAreaWidget);
		vBoxLayout_Scroll->insertWidget(0, titleWidget);
	}
}

void ScrollableListWidget::setTailWidget(QWidget* tailWidget)
{
	// 移除旧尾部
	if (tailWidget_) {
		vBoxLayout_Scroll->removeWidget(tailWidget_);
		tailWidget_->deleteLater();
	}
	tailWidget_ = tailWidget;

	// 添加新尾部（如果存在）
	if (tailWidget) {
		tailWidget->setParent(scrollAreaWidget);
		// 在弹簧之前插入尾部
		int insertIndex = vBoxLayout_Scroll->count() - 2; // 弹簧前一个位置
		vBoxLayout_Scroll->insertWidget(insertIndex, tailWidget);
	}
}

size_t ScrollableListWidget::size() const
{
	return widgetsList.size();
}

bool ScrollableListWidget::empty() const
{
	return widgetsList.isEmpty();
}

void ScrollableListWidget::clear()
{
	for (QWidget* widget : widgetsList) {
		vBoxLayout_Scroll->removeWidget(widget);
		widget->deleteLater();
	}
	widgetsList.clear();
}

void ScrollableListWidget::push_back(QWidget* val)
{
	if (!val) return;

	val->setParent(scrollAreaWidget);

	// 确定插入位置：在尾部之前（如果存在尾部）或弹簧之前
	int insertIndex;
	if (tailWidget_) {
		insertIndex = vBoxLayout_Scroll->indexOf(tailWidget_);
	}
	else {
		insertIndex = vBoxLayout_Scroll->count() - 2; // 弹簧前一个位置
	}

	vBoxLayout_Scroll->insertWidget(insertIndex, val);
	widgetsList.append(val);
}

void ScrollableListWidget::push_front(QWidget* val)
{
	if (!val) return;

	val->setParent(scrollAreaWidget);

	// 插入到标题之后（如果有标题）或最顶部（如果没有标题）
	int insertIndex = (titleWidget_) ? 1 : 0;
	vBoxLayout_Scroll->insertWidget(insertIndex, val);
	widgetsList.prepend(val);
}

int ScrollableListWidget::insert(int index, QWidget* val)
{
	if (!val || index < 0 || index > widgetsList.size())
		return -1;

	val->setParent(scrollAreaWidget);

	// 计算实际插入位置
	int insertIndex;
	if (titleWidget_) {
		// 有标题时，窗口列表从索引1开始
		insertIndex = index + 1;
	}
	else {
		// 无标题时，窗口列表从索引0开始
		insertIndex = index;
	}

	// 如果有尾部，插入位置在尾部之前
	if (tailWidget_) {
		insertIndex = qMin(insertIndex, vBoxLayout_Scroll->indexOf(tailWidget_));
	}

	vBoxLayout_Scroll->insertWidget(insertIndex, val);
	widgetsList.insert(index, val);
	return index;
}

void ScrollableListWidget::pop_back()
{
	if (widgetsList.isEmpty()) return;

	QWidget* last = widgetsList.last();
	vBoxLayout_Scroll->removeWidget(last);
	last->deleteLater();
	widgetsList.removeLast();
}

void ScrollableListWidget::pop_front()
{
	if (widgetsList.isEmpty()) return;

	QWidget* first = widgetsList.first();
	vBoxLayout_Scroll->removeWidget(first);
	first->deleteLater();
	widgetsList.removeFirst();
}

int ScrollableListWidget::erase(int index)
{
	if (index < 0 || index >= widgetsList.size())
		return -1;

	QWidget* widget = widgetsList[index];
	vBoxLayout_Scroll->removeWidget(widget);
	widget->deleteLater();
	widgetsList.removeAt(index);

	// 返回删除后下一个窗口的索引（或-1表示末尾）
	return (index >= widgetsList.size()) ? -1 : index;
}