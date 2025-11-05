#include "notification_bubble.h"

#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStyle>

NotificationBubble::NotificationBubble(const QString& text, int durationMs, QWidget* parent)
    : QFrame(parent), m_duration(durationMs)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    // 样式：深灰背景、白字、圆角
    setStyleSheet(R"(
        NotificationBubble {
            background-color: #2e2e2e;
            color: white;
            border-radius: 8px;
            padding: 10px;
        }
    )");

    label_Text = new QLabel(text, this);
    label_Text->setWordWrap(true);
    label_Text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    toolButton_Close = new QToolButton(this);
    toolButton_Close->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    toolButton_Close->setAutoRaise(true);
    toolButton_Close->setToolTip("关闭");
    connect(toolButton_Close, &QToolButton::clicked, this, [this]() {
        emit expired();
        deleteLater();
        });

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label_Text);
    layout->addWidget(toolButton_Close);
    layout->setContentsMargins(8, 6, 8, 6);
    layout->setSpacing(6);

    setLayout(layout);

    setMinimumSize(200, 60);


    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &NotificationBubble::onTimeout);

    /*show();*/
    qDebug() << "NotificationBubble 建立";
}

void NotificationBubble::startTimer()
{
    m_timer->start(m_duration);
}

void NotificationBubble::pauseTimer()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void NotificationBubble::resumeTimer()
{
    if (!m_timer->isActive()) {
        // 注意：QTimer 没有 remainingTime() 在 inactive 时返回 -1
        // 所以我们重新启动完整时长（或可记录剩余时间，此处简化）
        m_timer->start(m_duration);
    }
}

void NotificationBubble::onTimeout()
{
    emit expired();
    deleteLater();
}