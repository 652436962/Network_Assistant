#pragma once

#include <QSpinBox>
#include <QTimer>

/**
 * @brief 防抖的整数调整框
 */
class DebouncedSpinBox : public QSpinBox
{
	Q_OBJECT
private:
	QTimer* m_debouncedTimer;
	int m_lastValue;
public:
	explicit DebouncedSpinBox(QWidget* parent = nullptr, int debounceMs = 300);
signals:
	/**
	 * @brief 防抖后的值稳定信号
	 * @param 稳定的值
	 * @note Qt 信号
	 */
	void valueSettled(int value);
};
