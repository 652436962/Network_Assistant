#include "led_widget.h"

#include "qpainter.h"
#include "qpainterpath.h"

LED_Widget::LED_Widget(QWidget* parent):QWidget(parent)
{
	setMinimumSize(16, 16);
}

void LED_Widget::open(void)
{
	this->setState(true);
}

void LED_Widget::close(void)
{
	this->setState(false);
}


void LED_Widget::setState(bool state)
{
	if (this->state != state)
	{
		this->state = state;
		update();// 触发重绘
	}
}

bool LED_Widget::getState(void) const
{
	return this->state;
}

void LED_Widget::toggle(void)
{
	bool newState = !(this->getState());
	this->setState(newState);
}

void LED_Widget::setColor(const QColor& color)
{
	if (this->color != color)
	{
		this->color = color;
		if (this->state == true)// 如果当前是开启状态，需要重绘
		{
			update();// 触发重绘
		}
	}
}

QColor LED_Widget::getColor(void) const
{
	return this->color;
}

void LED_Widget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);// 抗锯齿

	// 计算绘制区域（留出边距）
	QRect rect = this->rect().adjusted(2, 2, -2, -2);

	// 根据状态决定颜色
	QColor ledColor;
	if (this->state)
	{
		ledColor = this->color; // 开启：显示设置的颜色
	}
	else
	{
		ledColor = Qt::transparent;// 关闭：透明
	}

	// 绘制圆形 LED
	int diameter = std::min(rect.width(), rect.height());
	QRect circleRect(
		rect.center().x() - diameter / 2,
		rect.center().y() - diameter / 2,
		diameter, diameter);
	painter.setBrush(ledColor);
	painter.setPen(QPen(Qt::black, 1));// // 黑色边框，宽度为 1
	painter.drawEllipse(circleRect);//绘制椭圆

}
