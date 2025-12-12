//main.cpp
//主窗口的头文件
#include "../mainwindow.h"

#include <QApplication> // 负责事件处理
#include <QSplashScreen> // 负责开屏动画
// #include <QDir> // 负责问题诊断
#include <QScreen> // 负责窗体居中逻辑
#include <QElapsedTimer> // 负责计时器


int main(int argc, char *argv[])
{
    // 开启高分屏缩放支持
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    //  创建 QApplication 实例
    // 它是 Qt Widgets 应用程序的控制中心，负责事件处理、设置等。
    QApplication a(argc, argv);
    // 获取主屏幕信息
    const QScreen *screen = QGuiApplication::primaryScreen();
    const QRect screenGeometry = screen->availableGeometry();
    // 获取屏幕像素比信息
    const qreal devicePixelRatio = screen->devicePixelRatio();
    // qDebug() << "Screen geometry:" << screenGeometry;
    // qDebug() << "Device pixel ratio:" << devicePixelRatio;


    // 检查目录是否失效
    // const QDir dir(":/img");
    // qDebug() << "Resources in :/img :" << dir.entryList();

    const auto pix = QPixmap(":/img/a");
    // 根据屏幕尺寸缩放
    QSize splashTargetSize;
    if(devicePixelRatio > 1.5)
    {
        // 高分屏：使用更大尺寸
        splashTargetSize = screenGeometry.size() * 0.8;
    }
    else
    {
        // 普通屏幕：使用适中尺寸
        splashTargetSize = screenGeometry.size() * 0.5;
    }
    // 高质量缩放
    const QPixmap scaledPixmap = pix.scaled(
        splashTargetSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );


    // 诊断：打印图片实际大小，确认图片解码是否成功
    // qDebug() << "Image loaded size:" << pix.size();
    // if(pix.isNull())
    // {
    //     qDebug() << "Failed to load splash image!";
    // }


    //创建开屏窗体
    QSplashScreen splash(scaledPixmap);
    splash.show();

    // 循环 + processEvents 代替 msleep
    // 这样可以在等待的同时，让 Qt 继续处理绘图事件，防止界面“假死”
    // qDebug() << "Splash shown. Waiting for 2 seconds...";
    auto timer = QElapsedTimer();
    for(timer.start();timer.elapsed() < 2000;)
    {
        // 处理积压的事件（比如：操作系统的“请绘制窗口”命令）
        QApplication::processEvents();
    }
    // qDebug() << "Loading complete.";



    // 实例化并显示主窗口
    MainWindow w;
    // 手动居中
    // 获取主屏幕
    if(screen)
    {
        const int x = (screenGeometry.width() - w.width()) / 2;
        const int y = (screenGeometry.height() - w.height()) / 2;
        w.move(x, y);
    }
    w.show();

    // 当主窗口显示后，结束 Splash
    splash.finish(&w);


    //  启动应用程序的事件循环
    // 应用程序将在这里等待用户的操作（如点击、键盘输入），
    // 只有当窗口关闭时，exec() 才会返回，程序才会退出。
    return QApplication::exec();
}
