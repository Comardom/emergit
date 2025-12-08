//main.cpp
//主窗口的头文件
#include "mainwindow.h"
#include "Prologue.h"

#include <QApplication> // 负责事件处理
#include <QSplashScreen> // 负责开屏动画
#include <QScreen> // 负责窗体居中逻辑
#include <QElapsedTimer> // 负责计时器
#include <memory>// 负责unique


int main(int argc, char *argv[])
{
    // 开启高分屏缩放支持
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    //  创建 QApplication 实例
    // 它是 Qt Widgets 应用程序的控制中心，负责事件处理、设置等。
    QApplication a(argc, argv);
    // 创建初始化类
    // const auto prologue = new Prologue();
    const auto prologue = std::make_unique<Prologue>();

    //创建开屏窗体
    QSplashScreen splash(*(prologue->getScaledSplashPix()));
    splash.show();

    // 循环 + processEvents 代替 msleep
    // 这样可以在等待的同时，让 Qt 继续处理绘图事件，防止界面“假死”
    const auto timer = std::make_unique<QElapsedTimer>();
    timer->start();
    for(;timer->elapsed() < prologue->getSplashTime();)
    {
        // 处理积压的事件（比如：操作系统的“请绘制窗口”命令）
        QApplication::processEvents();
    }

    // 实例化并显示主窗口
    MainWindow w;
    // 手动居中
    prologue->computeXYUndMoveWindow(w);
    w.show();

    // 当主窗口显示后，结束 Splash
    splash.finish(&w);


    //  启动应用程序的事件循环
    // 应用程序将在这里等待用户的操作（如点击、键盘输入），
    // 只有当窗口关闭时，exec() 才会返回，程序才会退出。
    return QApplication::exec();
}
