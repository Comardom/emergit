#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QActionGroup>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : BaseMultilingualWindow(parent)
    , ui(new Ui::MainWindow)
{
    // BaseMultilingualWindow();
    //加载和设置 Designer 创建的界面
    ui->setupUi(this);
    createLanguageMenu(); // 显式调用基类的语言菜单创建方法
    // 实现无边框（取消边框功能）
    // this->setWindowFlags(Qt::FramelessWindowHint);
    // 在这里放置所有 connect() 调用
    connect(ui->pushButton,&QPushButton::clicked,
        this,&MainWindow::do_testButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    // 调用基类的changeEvent
    BaseMultilingualWindow::changeEvent(event);
}

void MainWindow::do_testButton_clicked()
{
    QMessageBox::information(this, tr("哇这个好可爱鸭"), tr("按钮被点击了！"));
}