// CMakeProjectTest.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <QApplication>
#include "main_window.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
