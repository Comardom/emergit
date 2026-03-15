//
// Created by chara on 2026/1/26.
//

#include "./Shutdown.h"


#include <iostream>

#include "ui_Shutdown.h"

#include <QDial>
#include <QProcess>
#include <QObject>
#include <QLCDNumber>
#include <QFile>
#include <QStyle>
#include <QInputDialog>
#include <QRegularExpression>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>

#include "OS/FreeBSDExecShutdown.h"

//工厂模式
#if defined(Q_OS_WIN)
    #include "OS/WindowsExecShutdown.h"
    #define EmergitShutdownExecManager WindowsExecShutdown::instance()
#elif defined(Q_OS_LINUX)
    #include "OS/LinuxExecShutdown.h"
    #define EmergitShutdownExecManager LinuxExecShutdown::instance()
#elif defined(Q_OS_FREEBSD)
    #include "OS/FreeBSDExecShutdown.h"
    #define EmergitShutdownExecManager FreeBSDExecShutdown::instance()
#else

#endif
//================================================================================
Shutdown::Shutdown(QWidget *parent)
    : BaseMultilingualWindow(parent)
    , ui(new Ui::Shutdown)
    , timerCountdown(new QTimer(this))
    , canCloseItself(true)
{
    //Qt UI类必要代码
    ui->setupUi(this);
    //多语言
    createLanguageMenu();

    //执行组件属性设定
    dialSettings();
    lcdSettings();

    //信号连接
    connectDialToLcd();
    //菜单栏按钮的信号连接
    connectMenuBar();
    //按钮连接
    connectPushBtnToExec();
    //倒计时触发UI变化的连接
    connectTimerToChangeUI();

    //设定label的自定义类
    addLabelClass();
    // 加载资源文件中的 QSS
    loadQSS();
}
//================================================================================
void Shutdown::lcdSettings() const
{
    //取消LCD的边框
    const auto lcds = this->findChildren<QLCDNumber*>();
    for(auto* lcd : lcds)
    {
        lcd->setFrameStyle(QFrame::NoFrame);
    }
}

void Shutdown::dialSettings() const
{
    //刻度
    ui->dialMinute->setRange(0,59);
    ui->dialSecond->setRange(0,59);
    ui->dialHour->setRange(0,23);
    ui->dialDay->setRange(0,31);
    //显示刻度,禁止直接跨越最大值
    const auto dials = this->findChildren<QDial*>();
    for(auto* dial : dials)
    {
        dial->setNotchesVisible(true);
        dial->setWrapping(false);
    }
}
//================================================================================
void Shutdown::connectDialToLcd() const
{
    //对旋钮和LCD显示做连接
    connect(ui->dialSecond,&QDial::valueChanged,
        ui->lcdSecond,qOverload<int>(&QLCDNumber::display));
    connect(ui->dialMinute,&QDial::valueChanged,
        ui->lcdMinute,qOverload<int>(&QLCDNumber::display));
    connect(ui->dialHour,&QDial::valueChanged,
        ui->lcdHour,qOverload<int>(&QLCDNumber::display));
    connect(ui->dialDay,&QDial::valueChanged,
        ui->lcdDay,qOverload<int>(&QLCDNumber::display));
}

void Shutdown::connectMenuBar()
{
    connect(ui->actionChangeDaysLimit,&QAction::triggered,
        this,&Shutdown::changeDaysLimit);
}

void Shutdown::connectPushBtnToExec()
{
    connect(ui->pushBtnStartShutdown,&QPushButton::released,
        this,[this]() {
            ui->pushBtnStartShutdown->setEnabled(false);
            ui->pushBtnCancelShutdown->setEnabled(true);
            const auto dials = this->findChildren<QDial*>();
            for(auto* dial : dials)
            {
                dial->setEnabled(false);
            }
            setTimerShot();
        });
    connect(ui->pushBtnCancelShutdown,&QPushButton::released,
        this,[this]() {
            ui->pushBtnStartShutdown->setEnabled(true);
            ui->pushBtnCancelShutdown->setEnabled(false);
            const auto dials = this->findChildren<QDial*>();
            for(auto* dial : dials)
            {
                dial->setEnabled(true);
            }
            setTimerShot(true);
        });
}

void Shutdown::connectTimerToChangeUI()
{
    connect(timerCountdown, &QTimer::timeout,
        this, &Shutdown::perSecondTimeoutToChangeUI);
}
//================================================================================
void Shutdown::addLabelClass() const
{
    //冒号
    auto labelsColon =
        this->findChildren<QLabel*>(QRegularExpression("labelColon.*"));
    for (auto* label : labelsColon)
    {
        qDebug()<<label;
        if (!label) continue;
        label->setProperty("class", "labelsColon");
        label->style()->unpolish(label); // 清除旧属性影响
        label->style()->polish(label);   // 重新应用新样式
        label->update(); // 触发重绘
    }
    //量词
    auto labelsQuantifier =
        this->findChildren<QLabel*>(QRegularExpression("labelQuantifier.*"));
    for (auto* label : labelsQuantifier)
    {
        qDebug()<<label;
        if (!label) continue;
        label->setProperty("class", "labelsQuantifier");
        label->style()->unpolish(label); // 清除旧属性影响
        label->style()->polish(label);   // 重新应用新样式
        label->update(); // 触发重绘
    }
}

void Shutdown::loadQSS()
{
    QFile qssFile(":/qss/shutdown");
    if (qssFile.open(QFile::ReadOnly))
    {
        // 直接给当前窗口设置样式
        this->setStyleSheet(qssFile.readAll());
        qssFile.close();
    }
}
//================================================================================
void Shutdown::setTimerShot(const bool cancel)
{
    if(cancel && timerCountdown->isActive())
    {
        timerCountdown->stop();
        executeSystemShutdown(0, true);
        qDebug()<<"stop";
    }
    else
    {
        timeSEC = calculateSeconds();
        if (timeSEC <= 0) {return;}
        timerCountdown->start(1000);
        qDebug()<<"start";
    }
    qDebug()<<"exec!";
    executeSystemShutdown(timeSEC,cancel);
}

void Shutdown::changeDaysLimit()
{
    bool ok;
    qDebug()<<"Days Limit";
    const int daysUpperLimit = QInputDialog::getInt(this, tr("天数上限更改"),
    tr("请输入您想设定的天数上限:"), 31, 0, 99, 1, &ok);
    if (ok)
    {
        ui->dialDay->setRange(0,daysUpperLimit);
        //如果天数太多就不要提供刻度了，怕卡死
        if (daysUpperLimit > 99) {ui->dialDay->setNotchesVisible(false);}
    }
}

void Shutdown::executeSystemShutdown(const qint64 fullSecondsToWait, const bool cancel)
{
// TODO : 要加入临时文件存储是否正在定时关机，以便于关闭程序后再打开还能检测到，还要加入每半个小时进行一次时间校准
#if defined(Q_OS_WIN)
    cancel
    ? EmergitShutdownExecManager.cancelShutdownWithoutPara()
    : EmergitShutdownExecManager.schedulePowerOffWithSinglyParaSEC(fullSecondsToWait);
#elif defined(Q_OS_LINUX)
    cancel
    ? EmergitShutdownExecManager.cancelShutdownWithoutPara()
    : EmergitShutdownExecManager.schedulePowerOffWithSinglyParaSEC(fullSecondsToWait);
#elif defined(Q_OS_FREEBSD)
    FreeBSDExecShutdown::instance().initShutdownPointerWithSinglyShutdownPointerOfItself(this);
    cancel
    ? EmergitShutdownExecManager.cancelShutdownWithoutPara()
    : EmergitShutdownExecManager.schedulePowerOffWithSinglyParaSEC(fullSecondsToWait);
#elif defined(Q_OS_SOLARIS) || defined(Q_OS_MAC) || defined(Q_OS_OPENBSD)
    qCritical() << "No adaptation for this OS." <<std::endl;
    return;
#else
    qCritical() << "What OS do you using? What a creep." <<std::endl;
    return;
#endif
}

qint64 Shutdown::calculateSeconds() const
{
    return (static_cast<qint64>(ui->dialDay->value()) * 24 * 60 * 60) +
            (static_cast<qint64>(ui->dialHour->value())  * 60 * 60) +
                (static_cast<qint64>(ui->dialMinute->value()) * 60) +
                    (static_cast<qint64>(ui->dialSecond->value()));
}

void Shutdown::perSecondTimeoutToChangeUI()
{
    if(timeSEC > 0)
    {
        timeSEC--;

        const int d = static_cast<int>(timeSEC / (24 * 3600));
        const int h = static_cast<int>(timeSEC % (24 * 3600)) / 3600;
        const int m = static_cast<int>(timeSEC % 3600) / 60;
        const int s = static_cast<int>(timeSEC % 60);
        ui->dialDay->setValue(d);
        ui->dialHour->setValue(h);
        ui->dialMinute->setValue(m);
        ui->dialSecond->setValue(s);
    }
    else
    {
        timerCountdown->stop();
        qDebug() << "Bye bye";
    }
}


//================================================================================
qint64 Shutdown::getUiDialSecondValueInSEC() const
{
    return ui->dialSecond->value();
}

void Shutdown::setCanCloseItself(const bool aBool)
{
    canCloseItself = aBool;
}

void Shutdown::closeEvent(QCloseEvent *event)
{
    if (canCloseItself)
    {
        // 如果允许关闭，接受事件，窗口正常关闭
        event->accept();
    }
    else
    {
        // 如果不允许关闭，忽略事件
        event->ignore();
        qDebug() << "现在处于定时任务保护期，禁止关闭窗口！";
        QMessageBox::warning(this, "操作受限",
            "受系统限制，请在开始设定时的第一圈秒数走完之后再关闭窗口。或者您可以取消关机任务再关闭窗口。");
    }
}

void Shutdown::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event); // 先调用基类处理

    // 根据窗口宽度计算一个比例（比如窗口宽度的 5%）
    const int newFontSize = this->width() / 20;
    auto labels = this->findChildren<QLabel*>();
    for(auto* label : labels)
    {
        // 注意：这里要直接设置 font，因为 QSS 的优先级很高
        // 如果 QSS 里写死了 pt，这里设置可能会被覆盖，建议把 QSS 里的字号删掉
        QFont f = label->font();
        f.setPointSize(newFontSize);
        label->setFont(f);
    }
}

void Shutdown::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // 重新翻译 UI
        ui->retranslateUi(this);
    }

    // 调用基类的changeEvent
    BaseMultilingualWindow::changeEvent(event);
}
//--------------------------------------------------------------------------------
Shutdown::~Shutdown()
{
    delete ui;
}