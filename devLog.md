其他窗口使用多语言：<br />
```cpp
#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "LanguageManager.h"

SecondWindow::SecondWindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::SecondWindow)
{
ui->setupUi(this);

    // 获取 LanguageManager 实例，假设你通过单例或全局对象来管理它
    LanguageManager *languageManager = qApp->findChild<LanguageManager*>();

    // 连接语言切换信号
    connect(languageManager, &LanguageManager::languageChanged, this, [=]() {
        QAction *action = languageManager->languageActionGroup()->checkedAction();
        if (action) {
            QString localeName = action->data().toString();
            languageManager->loadTranslator(localeName);

            // 刷新当前窗口的 UI
            QEvent event(QEvent::LanguageChange);
            qApp->sendEvent(this, &event);
        }
    });

    // 默认设置语言
    languageManager->languageActionGroup()->actions().at(0)->setChecked(true);
}

SecondWindow::~SecondWindow()
{
delete ui;
}

// 重写 changeEvent，以便在语言变更时刷新 UI
void SecondWindow::changeEvent(QEvent *event)
{
if (event->type() == QEvent::LanguageChange) {
ui->retranslateUi(this);
}
QDialog::changeEvent(event);
}
```