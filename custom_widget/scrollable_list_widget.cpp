#include "scrollable_list_widget.h"


ScrollableListWidget::ScrollableListWidget(QWidget* parent)
	: QWidget(parent)
{
	setupUi();
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

	// 添加弹簧（始终在最底部）
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
	return widgetsList.count();
}

bool ScrollableListWidget::empty() const
{
	return widgetsList.isEmpty();
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

	// 插入到弹簧之前（即布局末尾 - 1）
	int insertIndex = vBoxLayout_Scroll->count() - 1;
	vBoxLayout_Scroll->insertWidget(insertIndex, val);
	widgetsList.push_back(val);
}

void ScrollableListWidget::push_front(QWidget* val)
{
	if (!val) return;
	val->setParent(scrollAreaWidget);

	// 插入到最前面（索引 0）
	vBoxLayout_Scroll->insertWidget(0, val);
	widgetsList.push_front(val);
}

int ScrollableListWidget::insert(int pos, QWidget* val)
{
	if (!val || pos < 0 || pos > widgetsList.count())
		return -1;

	val->setParent(scrollAreaWidget);

	// 插入位置 = index（因为无标题，窗口从0开始）
	vBoxLayout_Scroll->insertWidget(pos, val);
	widgetsList.insert(pos, val);
	return pos;
}

void ScrollableListWidget::pop_back()
{
	if (widgetsList.isEmpty()) return;

	QWidget* w = widgetsList.takeLast();
	vBoxLayout_Scroll->removeWidget(w);
	delete w;
}

void ScrollableListWidget::pop_front()
{
	if (widgetsList.isEmpty()) return;

	QWidget* w = widgetsList.takeFirst();
	vBoxLayout_Scroll->removeWidget(w);
	delete w;
}

int ScrollableListWidget::erase(int pos)
{
	if (pos < 0 || pos >= static_cast<int>(widgetsList.count()))
		return -1;

	QWidget* w = widgetsList.takeAt(pos);
	vBoxLayout_Scroll->removeWidget(w);
	delete w;

	return (pos >= widgetsList.count()) ? -1 : pos;
}

void ScrollableListWidget::remove(QWidget* value)
{
	if (!value) return;

	int index = widgetsList.indexOf(value);
	if (index == -1) return; // not found

	widgetsList.removeAt(index);
	vBoxLayout_Scroll->removeWidget(value);
	delete value;
}

QWidget* ScrollableListWidget::front()
{
	return widgetsList.front();
}
QWidget* ScrollableListWidget::back()
{
	return widgetsList.back();
}