#include "notification_manager.h"


#include <QVBoxLayout>
#include <QScreen>
#include <QGuiApplication>


NotificationManager::NotificationManager(QWidget* parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    m_layout->setContentsMargins(10, 10, 10, 10);
    m_layout->setSpacing(10);
    setLayout(m_layout);

    // 设置最小尺寸，避免 width=0
    setMinimumSize(200, 60);

    // 初始定位：主屏幕右上角
    if (QScreen* screen = QGuiApplication::primaryScreen()) {
        QRect available = screen->availableGeometry();
        move(available.right() - width() - 20, available.top() + 20);
    }

    show();
    qDebug() << "NotificationManager 建立";
}


void NotificationManager::showNotification(const QString& text, int durationMs)
{
    NotificationBubble* bubble = new NotificationBubble(text, durationMs, this);
    connect(bubble, &NotificationBubble::expired, this, [this, bubble]() {
        removeBubble(bubble);
        });

    // 新气泡插入顶部（视觉上最新在最上面）
    m_layout->insertWidget(0, bubble);
    bubblesList.prepend(bubble);

    bubble->show();
    bubble->startTimer();

    adjustSize();
    // ✅ 关键：确保 NotificationManager 自身在最前面
    raise();          // 提升窗口层级
    activateWindow(); // 激活窗口（获取焦点，对置顶有帮助）

    qDebug() << "showNotification";
}

void NotificationManager::removeBubble(NotificationBubble* bubble)
{
    bubblesList.removeOne(bubble);
    m_layout->removeWidget(bubble); // 从布局中移除
    bubble->deleteLater();          // 安全删除
    adjustSize();
}

void NotificationManager::enterEvent(QEnterEvent* event)
{
    for (auto* b : bubblesList) {
        b->pauseTimer();
    }
    QWidget::enterEvent(event);
}

void NotificationManager::leaveEvent(QEvent* event)
{
    for (auto* b : bubblesList) {
        b->resumeTimer();
    }
    QWidget::leaveEvent(event);
}