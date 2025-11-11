#include "notification_bubble.h"

#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QPainter>
#include <QPainterPath>

NotificationBubble::NotificationBubble(const QString text, int duration, QWidget* parent)
    : QFrame(parent)
{   
    if (this->objectName().isEmpty()) this->setObjectName("notification_bubble");
    setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除

    label_Text = new QLabel(this);
    label_Text->setObjectName("label_Text");
    QFont font = label_Text->font();
    font.setPointSize(10);
    label_Text->setFont(font);
    label_Text->setWordWrap(true);
    label_Text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    label_Text->setText(text);

    toolButton_Close = new QToolButton(this);
    toolButton_Close->setObjectName("toolButton_Closs");
    toolButton_Close->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    toolButton_Close->setAutoRaise(true);
    toolButton_Close->setToolTip("关闭");
    connect(toolButton_Close, &QToolButton::clicked, this, &NotificationBubble::close);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label_Text);
    layout->addWidget(toolButton_Close);
    layout->setContentsMargins(8, 6, 8, 6);
    layout->setSpacing(6);

    this->setLayout(layout);

    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);

    this->timer_Close = new QTimer(this);
    this->timer_Close->setTimerType(Qt::TimerType::CoarseTimer);
    this->timer_Close->setSingleShot(true);//只触发一次
    this->timer_Close->setInterval(duration);//设置时间
    //配置连接 定时结束关闭本窗口
    connect(this->timer_Close, &QTimer::timeout, this, &NotificationBubble::close);


    this->hide();// 隐藏窗口

    /*qDebug() << "有气泡建立";*/
}

void NotificationBubble::movePositionLeft(void)
{    
    QPoint startPoint = this->pos();
    QPoint endPoint = startPoint - QPoint(this->width(), 0);
    
    // 设置动画
    QPropertyAnimation* slideLift = new QPropertyAnimation(this, "pos", this);
    slideLift->setDuration(1000);//1000ms
    slideLift->setStartValue(startPoint);
    slideLift->setEndValue(endPoint);
    slideLift->setEasingCurve(QEasingCurve::OutCubic);// 缓动效果更自然

    slideLift->start();//播放动画    
}

void NotificationBubble::movePositionUp(void)
{
    QPoint startPoint = this->pos();
    QPoint endPoint = startPoint - QPoint(0, this->height() + 8);
    // 设置动画
    QPropertyAnimation* slideUP = new QPropertyAnimation(this, "pos", this);
    slideUP->setDuration(1000);//1000ms
    slideUP->setStartValue(startPoint);
    slideUP->setEndValue(endPoint);
    slideUP->setEasingCurve(QEasingCurve::OutCubic);// 缓动效果更自然

    slideUP->start();//播放动画
}

void NotificationBubble::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿，让圆角平滑

    QColor backgroundColor = QColor("#F8F9FA"); // 浅灰色背景
    QColor borderColor = QColor("#E0E0E0");     // 边框颜色
    int borderRadius = 8;                       // 圆角半径

    // 创建圆角矩形路径
    QRect rect = this->rect();
    QPainterPath path;
    path.addRoundedRect(rect, borderRadius, borderRadius);

    // 1. 填充背景色
    painter.fillPath(path, backgroundColor);

    // 2. 绘制边框
    QPen pen(borderColor, 1); // 1px 宽度
    painter.setPen(pen);
    painter.drawPath(path);
}

void NotificationBubble::closeEvent(QCloseEvent* event)
{
    emit this->bubbleColsed(this);
    QFrame::closeEvent(event);// 继续默认关闭流程
}

NotificationBubble::~NotificationBubble()
{
    /*qDebug() << "有气泡关闭";*/
}

void NotificationBubble::startTimer(void)
{
    this->timer_Close->start();
}

