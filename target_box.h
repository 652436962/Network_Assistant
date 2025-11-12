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
    QLabel* label_Address;
    QLineEdit* lineEdit_Address;
    QLabel* label_Port;
    QSpinBox* spinBox_Port;

    void setupUi(void);

public:
    TargetBox(QWidget* parent);
    QString getAddress(void);
    uint16_t getPortValue(void);
};
