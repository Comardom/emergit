//main.cpp
//主窗口的头文件
#include "mainwindow.h"

#include <QApplication>

#include "splash/FirstSplash.h"

int main(int argc, char *argv[])
{
    //  创建 QApplication 实例
    // 它是 Qt Widgets 应用程序的控制中心，负责事件处理、设置等。
    QApplication a(argc, argv);

    // 实例化并显示主窗口
    MainWindow w;
    w.show();

    // 创建Splash窗口
    auto *firstSplash = new FirstSplash();
    // 控制是否显示Splash
    // FirstSplashThread::isRejectedToShow=true;
    firstSplash->show();



    //  启动应用程序的事件循环
    // 应用程序将在这里等待用户的操作（如点击、键盘输入），

    // 只有当窗口关闭时，exec() 才会返回，程序才会退出。
    return a.exec();
}
