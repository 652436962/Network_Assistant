#pragma once

#include <QCombobox.h>

class AutoWidthCombobox : public QComboBox
{
	Q_OBJECT
public:
	explicit AutoWidthCombobox(QWidget* parent = nullptr);
protected:
	void showPopup(void) override;
};