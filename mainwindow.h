#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include "BaseMultilingualWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public BaseMultilingualWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void changeEvent(QEvent *event) override;

private slots:
    void do_testButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H