#pragma once

#include "qmainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
public:
    /**
     * @brief 创建对话框展示本机网络信息
     */
    void showLocalIPConfig(void);
};
