#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //加载和设置 Designer 创建的界面
    ui->setupUi(this);
    if constexpr(true)
    {//多语言配置
        // 1. 分组并连接 Designer 创建的 QAction
        langActionGroup = new QActionGroup(this);
        // 设置单选模式
        langActionGroup->setExclusive(true);
        QAction *zhCN = ui->action_zh_CN;
        QAction *zhTW = ui->action_zh_TW;
        QAction *enUS = ui->action_en_US;
        // 将 QAction 加入分组并设置其数据 (Data)
        // Designer 无法设置 data，所以在这里设置
        langActionGroup->addAction(zhCN);
        zhCN->setData("zh_CN");
        zhCN->setChecked(true); // 默认选中简体中文

        langActionGroup->addAction(zhTW);
        zhTW->setData("zh_TW");

        langActionGroup->addAction(enUS);
        enUS->setData("en_US");

        // 2. 将分组的触发事件连接到槽函数
        connect(langActionGroup, &QActionGroup::triggered,
            this, &MainWindow::changeLanguage);
    }//多语言配置
    // 在这里放置所有 connect() 调用
    connect(ui->pushButton,&QPushButton::clicked,
        this,&MainWindow::do_testButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_testButton_clicked()
{
    QMessageBox::information(this, tr("哇这个好可爱鸭"), tr("按钮被点击了！"));
}

// 针对多语言：加载新的翻译文件并更新应用程序
void MainWindow::loadTranslator(const QString &localeName)
{
    // 1. 移除旧的翻译器
    qApp->removeTranslator(&appTranslator);
    // 2. 如果选择的是源语言 (zh_CN)，则不加载任何翻译文件
    if (localeName == "zh_CN")
    {
        // 移除后，应用程序会自动回退到源代码中的 tr() 文本
        return;
    }

    // 3. 构造 QRC 路径并加载新的 .qm 文件
    const QString baseName = "emergit_" + localeName;

    // 假设 .qm 文件已成功嵌入到 QRC 的 :/i18n/ 路径
    if (appTranslator.load(":/i18n/" + baseName))
    {
        qApp->installTranslator(&appTranslator);
    }
    else
    {
        qDebug() << "Warning: Could not load translator for locale:" << localeName;
    }
}

// 针对多语言：处理菜单点击，调用加载函数
void MainWindow::changeLanguage(QAction *action)
{
    // 获取 QAction 中存储的语言代码 (zh_TW, en_US, zh_CN)
    QString localeName = action->data().toString();

    // 加载新的翻译文件
    loadTranslator(localeName);

    // 关键：通知所有 UI 元素进行自我刷新
    // Qt::LanguageChange 事件会触发所有 QWidget 的 changeEvent()
    QEvent event(QEvent::LanguageChange);
    qApp->sendEvent(this, &event);
}

// 针对多语言：重写 changeEvent，确保主窗口的 UI 元素刷新
void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // 当收到语言变更事件时，重新设置所有由 ui->setupUi()
        // 创建的元素（例如 MainWindow 上的标题、菜单文本、按钮文本等）
        ui->retranslateUi(this);
    }
    QMainWindow::changeEvent(event);
}