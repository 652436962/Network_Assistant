#include "send_area_box.h"

SendAreaBox::SendAreaBox(QWidget* parent) : QGroupBox(parent)
{
    this->setupUi();
}

void SendAreaBox::setupUi()
{
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(2, 2, 2, 2);
    widget = new QWidget(this);

    verticalLayout->addWidget(widget);

    widget_2 = new QWidget(this);

    verticalLayout->addWidget(widget_2);
}