#pragma once

#include <QGroupBox>

#include <QWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QGridLayout>
#include <QTimer>
#include <QByteArray>

#include "sundry.h"


class SendAreaBox : public QGroupBox
{
private:
	QVBoxLayout* verticalLayout;
	QWidget* widget;
	QWidget* widget_2;

	void setupUi();

public:
	SendAreaBox(QWidget* parent);

};



