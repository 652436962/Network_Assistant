#pragma once

#include <QGroupBox>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class TargetBox: public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout* verticalLayout;
    QLabel* label_LocalAddress;
    QLineEdit* lineEdit_TargetAddress;
    QLabel* label_LocalPort;
    QSpinBox* spinBox_LocalPort;

    void setupUi(void);

public:
    TargetBox(QWidget* parent);
    QString getTargetAddress(void);
    uint16_t getPortValue(void);
};
