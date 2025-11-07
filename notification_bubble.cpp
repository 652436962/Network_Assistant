#include "notification_bubble.h"

#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QPainter>
#include <QPainterPath>

NotificationBubble::NotificationBubble(const QString& text, QWidget* parent, int duration)
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

    this->setMinimumSize(196, 48);
    this->setMaximumSize(196, 48);

    this->timer_Close = new QTimer(this);
    this->timer_Close->setTimerType(Qt::TimerType::CoarseTimer);
    this->timer_Close->setSingleShot(true);//只触发一次
    //配置连接 定时结束关闭本窗口
    connect(this->timer_Close, &QTimer::timeout, this, &NotificationBubble::close);


    this->hide();// 隐藏窗口

    this->startSlideInAnimation();//滑入

    this->timer_Close->start(duration);//启动定时器

    qDebug() << "NotificationBubble 建立";
}

void NotificationBubble::startSlideInAnimation()
{
    QWidget* mainWindow = window(); // 获取顶层窗口（通常是主窗口）
    if (!mainWindow) return;

    // 计算目标位置：主窗口右上角内侧（留 12px 边距）
    int x = mainWindow->x() + mainWindow->width() - this->width() - 12;
    int y = mainWindow->y() + 32; // 从顶部下方 32px 开始（避开标题栏）

    // 将窗口移动到初始位置：从右方滑入（X 在窗口外）
    this->move(x+this->width()+12, y); // 起点在目标位置右方

    // 显示窗口（但还在外面）
    this->show();

    // 设置动画
    //滑入动画
    QPropertyAnimation* slideIn = new QPropertyAnimation(this, "pos", this);
    slideIn->setDuration(1000); // 1000ms
    slideIn->setStartValue(QPoint(x + this->width() + 12, y));
    slideIn->setEndValue(QPoint(x, y));// 目标位置
    slideIn->setEasingCurve(QEasingCurve::OutCubic); // 缓动效果更自然

    slideIn->start();
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
    qDebug() << "通知气泡关闭";
}

