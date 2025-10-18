#include "main_window.h"

#include "ui_main_window.h"

#include "led_widget.h"

#include "qdialog.h"
#include "qhostinfo.h"
#include "qtablewidget.h"//表格
#include "qsysinfo.h"//系统信息

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->led->setColor(Qt::green);
    ui->led->setState(true);
    connect(ui->pushButton_Start, &QPushButton::clicked, ui->led, &LED_Widget::toggle);

    //展示主机信息
    connect(ui->action_Info, &QAction::triggered, this, &MainWindow::showLocalIPConfig);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLocalIPConfig(void)
{
    qDebug() << "展示本机信息";
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("本机信息");
    dialog->setMinimumSize(200, 200);
    QTableWidget* table = new QTableWidget(dialog);
    /*table->resize(200, 300);*/
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "属性" << "值");
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);// 禁止编辑
    //table->setSelectionBehavior(QAbstractItemView::SelectRows);// 点击选中行

    int row = 0;
    auto addRow = [&](const QString& key, const QString& value)
        {
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(key));
            table->setItem(row, 1, new QTableWidgetItem(value));
            row++;
        };

    addRow("操作系统", QSysInfo::prettyProductName());
    addRow("内核版本", QSysInfo::kernelVersion());
    addRow(" CPU 架构", QSysInfo::currentCpuArchitecture());

    // 获取主机信息
    addRow("本机名", QHostInfo::localHostName());

    table->resizeColumnsToContents();
    
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(table);
    dialog->setLayout(layout);
    // 设置为非模态对话框
    dialog->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动释放内存
    dialog->show();
}
