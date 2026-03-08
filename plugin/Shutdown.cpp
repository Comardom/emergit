//
// Created by chara on 2026/1/26.
//


#include "Shutdown.h"
#include "ui_Shutdown.h"
#include <QDial>
#include <QLCDNumber>
#include <QFile>
#include <QStyle>
#include <QInputDialog>
#include <QRegularExpression>
#include <QResizeEvent>

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
    //菜单栏按钮的信号连接
    connectMenuBar();

    //设定label的自定义类
    addLabelClass();
    // 加载资源文件中的 QSS
    loadQSS();
}


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

void Shutdown::changeDaysLimit()
{
    bool ok;
    qDebug()<<"Days Limit";
    const int i = QInputDialog::getInt(this, tr("天数上限更改"),
    tr("请输入您想设定的天数上限:"), 31, 0, 99, 1, &ok);
    if (ok)
    {
        ui->dialDay->setRange(0,i);
        //如果天数太多就不要提供刻度了，怕卡死
        if (i > 1000) {ui->dialDay->setNotchesVisible(false);}
    }
}

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
    // const auto labels = this->findChildren<QLabel*>();
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