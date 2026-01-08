#include "editable_tabwidget.h"

#include <QTabBar>
#include <QKeyEvent>
#include <QApplication>

EditableTabWidget::EditableTabWidget(QWidget* parent)
	: QTabWidget(parent)
{
	// 启用双击编辑
	connect(this->tabBar(), &QTabBar::tabBarDoubleClicked, this, &EditableTabWidget::onTabBarDoubleClicked);
	connect(this, &QTabWidget::currentChanged, this, &EditableTabWidget::onCurrentChanged);
}

void EditableTabWidget::onTabBarDoubleClicked(int index)
{
	if (index < 0 || index >= count()) return;
	/*qDebug() << "双击事件触发  索引 " << index;*/
	startEditing(index);
}

void EditableTabWidget::startEditing(int index)
{
	/*qDebug() << "开始编辑 索引 " << index;*/
	// 如果已在编辑，先提交
	if (m_editLine) {
		finishEditing(true);
	}

	m_editingIndex = index;
	QString currentText = tabText(index);// 获取当前文本

	// 它的标签无法编辑
	// 创建一个行文本框，正好“盖住”要编辑的标签
	// 因此父设为 this（QTabWidget），不是 tabBar()
	m_editLine = new QLineEdit(currentText, this);

	// 设置基本外观（无样式表）
	m_editLine->setFrame(true);//启用 QLineEdit 的边框（frame）。
	m_editLine->setTextMargins(2, 0, 2, 0);//为文本内容设置内边距

	// 将 tabBar 的局部坐标 → 全局坐标 → QTabWidget 的局部坐标
	QRect tabRect = tabBar()->tabRect(index);                     // 相对于 tabBar
	QPoint globalPos = tabBar()->mapToGlobal(tabRect.topLeft());  // 转为全局
	QPoint localPos = mapFromGlobal(globalPos);                   // 转为 this 的局部坐标
	m_editLine->setGeometry(QRect(localPos, tabRect.size()));// 设置几何 位置 大小

	// 强制显示（虽然默认 visible=true，但保险）
	m_editLine->show();

	m_editLine->setFocus();
	m_editLine->selectAll();

	// 连接信号
	connect(m_editLine, &QLineEdit::editingFinished, this, &EditableTabWidget::onEditingFinished);

	// 支持按 Enter 提交，Esc 取消
	m_editLine->installEventFilter(this);
}

void EditableTabWidget::onEditingFinished()
{
	/*qDebug() << "onEditingFinished";*/
	// 注意：editingFinished 可能由失去焦点触发，但我们通过事件过滤器已处理 Enter/Esc
	// 所以这里只做兜底
	if (m_editLine) {
		finishEditing(true);
	}
}

bool EditableTabWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == m_editLine && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Escape) {
			finishEditing(false); // 取消
			return true;
		}
		else if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
			finishEditing(true); // 接受
			return true;
		}
	}
	return QTabWidget::eventFilter(watched, event);
}

void EditableTabWidget::finishEditing(bool accept)
{
	/*qDebug() << "finishEditing" << accept;*/
	if (!m_editLine) return;

	QString newText = m_editLine->text().trimmed();
	/*qDebug() << "newText " << newText;*/
	if (accept && !newText.isEmpty() && m_editingIndex >= 0 && m_editingIndex < count()) {
		setTabText(m_editingIndex, newText);
	}

	// 清理
	m_editLine->deleteLater();
	m_editLine = nullptr;
	m_editingIndex = -1;
}

void EditableTabWidget::onCurrentChanged(int index)
{
	/*qDebug() << "onCurrentChanged";*/
	// 当用户切换到其他标签页时，自动结束当前编辑
	if (m_editLine && index != m_editingIndex) {
		finishEditing(true);
	}
}