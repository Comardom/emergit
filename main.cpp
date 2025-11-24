//main.cpp
//主窗口的头文件
#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QDir>
#include <QThread>
#include <QScreen>
#include <QElapsedTimer> // 引入计时器

#include "splash/FirstSplash.h"

int main(int argc, char *argv[])
{

    // 开启高分屏缩放支持
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    //  创建 QApplication 实例
    // 它是 Qt Widgets 应用程序的控制中心，负责事件处理、设置等。
    QApplication a(argc, argv);

    const QDir dir(":/img");
    qDebug() << "Resources in :/img :" << dir.entryList();


    const auto *pix = new QPixmap(":/img/a");

    // 诊断：打印图片实际大小，确认图片解码是否成功
    qDebug() << "Image loaded size:" << pix->size();
    if (pix->isNull()) {
        qDebug() << "Fatal Error: Image is null!";
    }

    // pix->save("1.jpeg");
    QSplashScreen splash(*pix);
    if(pix->isNull())
    {
        qDebug() << "Failed to load splash image!";
    }
    splash.show();

    // 3. 关键修改：使用 while 循环 + processEvents 代替 msleep
    // 这样可以在等待的同时，让 Qt 继续处理绘图事件，防止界面“假死”
    qDebug() << "Splash shown. Waiting for 2 seconds...";

    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < 2000) // 等待 2000 毫秒
    {
        // 处理积压的事件（比如：操作系统的“请绘制窗口”命令）
        QApplication::processEvents();
    }

    // 让 Splash 立即渲染出来
    qDebug() << "Loading complete.";



    // 实例化并显示主窗口
    MainWindow w;
    // --- 开始：手动居中代码 ---
    // 获取主屏幕
    if (const QScreen *screen = QGuiApplication::primaryScreen())
    {
        const QRect screenGeometry = screen->availableGeometry();
        const int x = (screenGeometry.width() - w.width()) / 2;
        const int y = (screenGeometry.height() - w.height()) / 2;
        w.move(x, y);
    }
    // --- 结束 ---
    w.show();

    // 当主窗口显示后，结束 Splash
    splash.finish(&w);


    // 创建Splash窗口
    // auto *firstSplash = new FirstSplash();
    // 控制是否显示Splash
    // FirstSplashThread::isRejectedToShow=true;
    // firstSplash->show();

    // splash.finish(&w);
    delete pix;

    //  启动应用程序的事件循环
    // 应用程序将在这里等待用户的操作（如点击、键盘输入），

    // 只有当窗口关闭时，exec() 才会返回，程序才会退出。
    return QApplication::exec();
}
