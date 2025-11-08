#include "BaseMultilingualWindow.h"
#include "ui_BaseMultilingualWindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QApplication>
#include <QActionGroup>
#include <QDebug>

BaseMultilingualWindow::BaseMultilingualWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::BaseMultilingualWindow)
{
    ui->setupUi(this);

    // 创建并添加语言菜单
    createLanguageMenu();
}

BaseMultilingualWindow::~BaseMultilingualWindow()
{
    delete ui;
}

void BaseMultilingualWindow::createLanguageMenu()
{
    // 创建一个新的菜单项（如果需要）
    QMenu *langMenu = menuBar()->addMenu(tr("语言"));

    // 创建一个 QActionGroup，确保只有一个菜单项被选中
    langActionGroup = new QActionGroup(this);
    langActionGroup->setExclusive(true);

    // 创建语言选择项
    QAction *zhCN = new QAction(tr("简体中文"), this);
    QAction *zhTW = new QAction(tr("繁體中文"), this);
    QAction *enUS = new QAction(tr("English"), this);

    // 设置对应语言的标识
    zhCN->setData("zh_CN");
    zhTW->setData("zh_TW");
    enUS->setData("en_US");

    // 将 QAction 加入到 QActionGroup 中
    langActionGroup->addAction(zhCN);
    langActionGroup->addAction(zhTW);
    langActionGroup->addAction(enUS);

    // 默认选中简体中文
    zhCN->setChecked(true);

    // 将 QAction 添加到菜单中
    langMenu->addAction(zhCN);
    langMenu->addAction(zhTW);
    langMenu->addAction(enUS);

    // 连接语言选择信号到槽函数
    connect(langActionGroup, &QActionGroup::triggered,
        this, &BaseMultilingualWindow::changeLanguage);
}

// 加载新的翻译文件并触发刷新
void BaseMultilingualWindow::loadTranslator(const QString &localeName)
{
    qApp->removeTranslator(&appTranslator); // 移除旧的翻译器

    if (localeName == "zh_CN")
    {
        // 简体中文无需加载翻译文件
        return;
    }

    const QString baseName = "emergit_" + localeName;

    if (appTranslator.load(":/i18n/" + baseName))
    {
        qApp->installTranslator(&appTranslator);
    }
    else
    {
        qDebug() << "Warning: Could not load translator for locale:"
            << localeName;
    }
}

// 多语言切换槽函数
void BaseMultilingualWindow::changeLanguage(QAction *action)
{
    QString localeName = action->data().toString();

    // 加载新的翻译文件
    loadTranslator(localeName);

    // 关键：通知所有 UI 元素进行自我刷新
    QEvent event(QEvent::LanguageChange);
    qApp->sendEvent(this, &event);
}

// 语言改变时，刷新界面
void BaseMultilingualWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this); // 重新翻译 UI
    }

    QMainWindow::changeEvent(event);
}
