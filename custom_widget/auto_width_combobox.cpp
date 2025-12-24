#include "auto_width_combobox.h"

#include <QStyle>
#include <QFontMetrics>
#include <QAbstractItemView>
#include <QScrollBar>

AutoWidthCombobox::AutoWidthCombobox(QWidget* parent) :QComboBox(parent)
{
}

void AutoWidthCombobox::showPopup(void)
{
	//获取当前 view （下拉列表）
	QAbstractItemView* view = this->view();
	QStyleOptionComboBox opt;
	initStyleOption(&opt);

	//计算所有项的最大宽度
	int maxWidth = 0;
	QFontMetrics fm(this->font());
	for (int i = 0; i < this->count(); ++i)
	{
		QString text = this->itemText(i);
		int textWidth = fm.horizontalAdvance(text) + 16;
		if (textWidth > maxWidth) maxWidth = textWidth;
	}

	// 考虑样式边框、箭头等
	int scrollBarWidth = view->verticalScrollBar()->isVisible() ?
		view->verticalScrollBar()->width() : 0;
	int frameWidth = this->style()->pixelMetric(QStyle::PM_ComboBoxFrameWidth, &opt, this);
	int totalWidth = maxWidth + scrollBarWidth + frameWidth;

	//设置下拉列表最小宽度 （不能小于 combo 本身）
	int minWidth = qMax(totalWidth, this->width());
	view->setMinimumWidth(minWidth);

	//调用父类正常弹出
	QComboBox::showPopup();
}
