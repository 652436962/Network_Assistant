#pragma once

#include <QTabWidget>
#include <QLineEdit>

class EditableTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit EditableTabWidget(QWidget* parent = nullptr);

private:
    void onTabBarDoubleClicked(int index);
    void onEditingFinished();
    void onCurrentChanged(int index); // 切换标签时自动结束编辑

private:
    QLineEdit* m_editLine = nullptr;
    int m_editingIndex = -1;

    void startEditing(int index);
    void finishEditing(bool accept = true);

protected:
    /**
     * @brief 事件过滤器
     * @param watched 被监视的对象
     * @param 发生的事件 
     * @return true 我已处理，不要再传给 watched
     * @return false 我不处理，请继续交给 watched
     */
    bool eventFilter(QObject* watched, QEvent* event) override;
};