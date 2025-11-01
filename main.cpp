//main.cpp
//主窗口的头文件
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    //  创建 QApplication 实例
    // 它是 Qt Widgets 应用程序的控制中心，负责事件处理、设置等。
    QApplication a(argc, argv);

    /*
    //创建一个 QTranslator 对象，用于加载 .qm 翻译文件
    QTranslator translator;
    //获取系统当前的用户界面语言列表（可能包含多个语言偏好，例如 ["zh-CN", "en-US"]）
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    // 我们只关心需要翻译的目标语言
    const QSet<QString> targetLocales = {"en_US", "zh_TW"};
    // 遍历这些语言偏好
    for (const QString &locale : uiLanguages) {
        const QString normalizedLocale = QLocale(locale).name();

        // 1. 检查是否为目标翻译语言
        if (targetLocales.contains(normalizedLocale)) {
            const QString baseName = "emergit_" + normalizedLocale;

            // 2. 尝试从 QRC 资源路径加载 .qm 文件
            if (translator.load(":/i18n/" + baseName)) { // :i18n/ 是 app.qrc 中定义的虚拟路径
                a.installTranslator(&translator);
                qDebug() << "Loaded translator for:" << normalizedLocale;
                break; // 成功加载后退出循环
            }
        }
    }
*/
    // 注意：这里的 QLocale::system().uiLanguages() 仍然用于设置系统的默认 QLocale，
    // 但不再需要在这里加载和安装 QTranslator。

    // 实例化并显示主窗口
    MainWindow w;
    // 让窗口可见
    w.show();
    //  启动应用程序的事件循环
    // 应用程序将在这里等待用户的操作（如点击、键盘输入），
    // 只有当窗口关闭时，exec() 才会返回，程序才会退出。
    return a.exec();
}
