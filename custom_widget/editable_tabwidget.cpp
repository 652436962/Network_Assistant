#include "editable_tabwidget.h"

#include <QTabBar>
#include <QKeyEvent>
#include <QApplication>

EditableTabWidget::EditableTabWidget(QWidget* parent)
	: QTabWidget(parent)
{
	//配置连接 双击
	connect(this->tabBar(), &QTabBar::tabBarDoubleClicked, [this](int index) {
		if (index < 0 || index >= count()) return;
		/*qDebug() << "双击事件触发  索引 " << index;*/
		startEditing(index);
		});
	//配置连接 编辑页变化
	connect(this, &QTabWidget::currentChanged, [this](int index) {
		/*qDebug() << "onCurrentChanged";*/
		// 当用户切换到其他标签页时，自动结束当前编辑
		if (m_editLine && index != m_editingIndex) {
			finishEditing(true);
		}
		});
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
		
	m_editLine->show();// 强制显示（虽然默认 visible=true，但保险）
	m_editLine->setFocus();//设置焦点
	m_editLine->selectAll();//全选

	// 配置连接 编辑完成
	connect(m_editLine, &QLineEdit::editingFinished, [this]() {
		// 注意：editingFinished 可能由失去焦点触发，但我们通过事件过滤器已处理 Enter/Esc
		// 所以这里只做兜底
		if (this->m_editLine)
		{
			this->finishEditing(true);
		}
		});

	// 支持按 Enter 提交，Esc 取消
	m_editLine->installEventFilter(this);
}

bool EditableTabWidget::eventFilter(QObject* watched, QEvent* event)
{
	//m_editLine 发来的事件
	if (watched == m_editLine && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		//如果按了 Esc → 取消编辑
		if (keyEvent->key() == Qt::Key_Escape) {
			finishEditing(false); // 取消
			return true;
		}
		//如果按了 Enter/Return → 提交编辑
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

