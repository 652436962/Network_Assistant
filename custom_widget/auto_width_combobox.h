#pragma once

#include <QComboBox>

/**
 * @brief 自动调节下拉列表框宽度的下拉列表框
 */
class AutoWidthCombobox : public QComboBox
{
	Q_OBJECT
public:
	explicit AutoWidthCombobox(QWidget* parent = nullptr);
protected:
	void showPopup(void) override;
};