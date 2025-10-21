#pragma once

#include <QObject>
#include <QWidget>

#include <QPlainTextEdit>

class ReceiveWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ReceiveWidget(QWidget* parent = nullptr);


signals:
};


