#include "toggle_button.h"

void ToggleButton::changeText(void)
{
	if (this->state) this->setText(this->text_on);
	else this->setText(this->text_off);
}

ToggleButton::ToggleButton(QWidget* parent) :QPushButton(parent)
{
}

void ToggleButton::setTexts(const QString& textOff, const QString& textOn)
{
	this->text_off = textOff;
	this->text_on = textOn;	
	this->changeText();
}

void ToggleButton::setCheckedState(bool checked)
{
	if (this->state != checked)
	{
		this->state = checked;
		this->changeText();
	}
}

bool ToggleButton::getCheckedState(void) const
{
	return this->state;
}
