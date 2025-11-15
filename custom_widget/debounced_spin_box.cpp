#include "debounced_spin_box.h"

DebouncedSpinBox::DebouncedSpinBox(QWidget* parent, int debounceMs):QSpinBox(parent)
{
	this->m_debouncedTimer = new QTimer(this);
	this->m_debouncedTimer->setInterval(debounceMs);
	this->m_debouncedTimer->setTimerType(Qt::TimerType::VeryCoarseTimer);
	this->m_debouncedTimer->setSingleShot(true);//只触发一次

	// 连接原始 valueChanged 信号
	connect(this, &QSpinBox::valueChanged, [this](int value) {
		this->m_lastValue = value;
		this->m_debouncedTimer->start();// 每次值变化就重启定时器
		});

	connect(this->m_debouncedTimer, &QTimer::timeout, [this]() {
		// 定时器超时 → 值已稳定
		emit this->valueSettled(this->m_lastValue);
		});
}

