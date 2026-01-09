#pragma once

#include <QTabWidget>
#include <QLineEdit>

class EditableTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit EditableTabWidget(QWidget* parent = nullptr);

private:
    QLineEdit* m_editLine = nullptr;//编辑行窗口
    int m_editingIndex = -1;//正在编辑的索引

private:
    /**
     * @brief 开始编辑
     * @param index 索引
     */
    void startEditing(int index);
    /**
     * @brief 编辑完成
     * @param accept 
     */
    void finishEditing(bool accept = true);

protected:
    /**
     * @brief 事件过滤器
     * @param watched 被监视的对象
     * @param 发生的事件 
     * @return true 已处理，不要再传给 watched
     * @return false 未处理，继续交给 watched
     */
    bool eventFilter(QObject* watched, QEvent* event) override;
};