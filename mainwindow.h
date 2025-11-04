#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 重写 changeEvent，确保主窗口能在语言变更时自我刷新
    void changeEvent(QEvent *event) override;

private slots:
    void do_testButton_clicked();
    void changeLanguage(QAction* action);

private:
    Ui::MainWindow *ui;
    QTranslator appTranslator; // 用于管理当前加载的翻译器
    QActionGroup *langActionGroup; // 用于管理菜单项的互斥选择
    // 加载新的翻译文件并触发刷新
    void loadTranslator(const QString &localeName);
};
#endif // MAINWINDOW_H
