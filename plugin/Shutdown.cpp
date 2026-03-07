//
// Created by chara on 2026/1/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Shutdown.h" resolved

#include "Shutdown.h"
#include "ui_Shutdown.h"
#include <QDial>
#include <QLCDNumber>
#include <QFile>
#include <QStyle>


Shutdown::Shutdown(QWidget *parent)
    : BaseMultilingualWindow(parent)
    , ui(new Ui::Shutdown){

    //Qt UI类必要代码
    ui->setupUi(this);
    //多语言
    createLanguageMenu();


    //执行组件属性设定
    dialSettings();
    lcdSettings();
    //信号连接
    connectDialToLcd();


    // 找到 Shutdown 窗口里所有的 QLabel 控件并集中处理QSS
    const auto labels = this->findChildren<QLabel*>();
    for (auto* label : labels)
    {
        label->setProperty("class", "lcdSideStyle");
        label->style()->unpolish(label); // 清除旧属性影响
        label->style()->polish(label);   // 重新应用新样式
    }

    // 加载资源文件中的 QSS
    if (QFile qssFile(":/qss/shutdown"); qssFile.open(QFile::ReadOnly))
    {
        // 直接给当前窗口设置样式
        this->setStyleSheet(qssFile.readAll());
        qssFile.close();
    }
    //改变单复数
    changeSingularUndPluralForDials();
}


void Shutdown::lcdSettings() const
{
    //取消LCD的边框
    const auto lcds = this->findChildren<QLCDNumber*>();
    for(auto* lcd : std::as_const(lcds))//此处as_const用于优化性能
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
    for(auto* dial : std::as_const(dials))//此处as_const用于优化性能
    {
        dial->setNotchesVisible(true);
        dial->setWrapping(false);
    }
}

void Shutdown::connectDialToLcd() const
{
    //对旋钮和LCD显示做连接
    connect(ui->dialSecond,&QDial::valueChanged,ui->lcdSecond,qOverload<int>(&QLCDNumber::display));
    connect(ui->dialMinute,&QDial::valueChanged,ui->lcdMinute,qOverload<int>(&QLCDNumber::display));
    connect(ui->dialHour,&QDial::valueChanged,ui->lcdHour,qOverload<int>(&QLCDNumber::display));
    connect(ui->dialDay,&QDial::valueChanged,ui->lcdDay,qOverload<int>(&QLCDNumber::display));
}

void Shutdown::changeSingularUndPluralForDials()
{
    //一共四个参数，触发信号(第二个参数)时第一个参数(dial对象)会抛出一个值，这个值会传递给第四个参数(lambda)，然后被捕获使用
    connect(ui->dialSecond,&QDial::valueChanged,
        this,[this](const int x) {
            const QString s = (x > 1) ? tr("Seconds") : tr("Second");
            ui->labelSecond->setText(s);
        });
    connect(ui->dialMinute,&QDial::valueChanged,
        this,[this](const int x) {
            const QString s = (x > 1) ? tr("Minutes") : tr("Minute");
            ui->labelMinute->setText(s);
        });
    connect(ui->dialHour,&QDial::valueChanged,
        this,[this](const int x) {
            const QString s = (x > 1) ? tr("Hours") : tr("Hour");
            ui->labelHour->setText(s);
        });
    connect(ui->dialDay,&QDial::valueChanged,
        this,[this](const int x) {
            const QString s = (x > 1) ? tr("Days") : tr("Day");
            ui->labelDay->setText(s);
        });
}

void Shutdown::changeEvent(QEvent *event){
    if (event->type() == QEvent::LanguageChange){
        // 重新翻译 UI
        ui->retranslateUi(this);
    }

    // 调用基类的changeEvent
    BaseMultilingualWindow::changeEvent(event);
}

Shutdown::~Shutdown(){
    delete ui;
}