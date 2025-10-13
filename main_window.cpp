#include "main_window.h"

#include "ui_main_window.h"

#include "led_widget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->led->setColor(Qt::green);
    ui->led->setState(true);

    connect(ui->pushButton_Start, &QPushButton::clicked, ui->led, &LED_Widget::toggle);
}

MainWindow::~MainWindow()
{
    delete ui;
}