#pragma once
#include <QPushButton>

class ToggleButton: public QPushButton
{
	Q_OBJECT
private:
	QString text_off;
	QString text_on;	
	bool state = false;//通常开始应当是关闭的
	/**
	 * @brief 根据当前状态调整文本
	 */
	void changeText(void);
public:
	explicit ToggleButton(QWidget* parent);
	/**
	 * @brief 设置两种状态的文本
	 * @param textOff 关闭状态文本
	 * @param textOn 打开状态文本
	 */
	void setTexts(const QString& textOff, const QString& textOn);
	/**
	 * @brief 设置按钮状态
	 * @param checked 
	 */
	void setCheckedState(bool checked);
	/**
	 * @brief 获取按钮状态 
	 * @return 按钮状态 
	 */
	bool getCheckedState(void) const;
};
