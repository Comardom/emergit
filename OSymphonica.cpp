//
// Created by comardom on 2025/12/10.
//


#include "OSymphonica.h"

#include "BaseMultilingualWindow.h"
#include "ui_OSymphonica.h"


#include <QDial>
#include <QLCDNumber>

OSymphonica::OSymphonica(QWidget *parent)
	: BaseMultilingualWindow(parent)
	, ui(new Ui::OSymphonica)// 实例化 UI 类
{
	// 将所有的组件实例化并摆放到窗口上
	ui->setupUi(this);
	createLanguageMenu();

	//刻度从0到59
	ui->dialMinute->setRange(0,59);
	ui->dialSecond->setRange(0,59);
	ui->dialHour->setRange(0,23);
	ui->dialDay->setRange(0,31);
	//显示刻度
	ui->dialMinute->setNotchesVisible(true);
	ui->dialSecond->setNotchesVisible(true);
	ui->dialHour->setNotchesVisible(true);
	ui->dialDay->setNotchesVisible(true);
	//禁止直接跨越最大值
	ui->dialMinute->setWrapping(false);
	ui->dialSecond->setWrapping(false);
	ui->dialHour->setWrapping(false);
	ui->dialDay->setWrapping(false);
	//对旋钮和LCD显示做连接
	connect(ui->dialSecond,&QDial::valueChanged,ui->lcdSecond,qOverload<int>(&QLCDNumber::display));
	connect(ui->dialMinute,&QDial::valueChanged,ui->lcdMinute,qOverload<int>(&QLCDNumber::display));
	connect(ui->dialHour,&QDial::valueChanged,ui->lcdHour,qOverload<int>(&QLCDNumber::display));
	connect(ui->dialDay,&QDial::valueChanged,ui->lcdDay,qOverload<int>(&QLCDNumber::display));

}

OSymphonica::~OSymphonica()
{
	delete ui;
}
void OSymphonica::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		// 重新翻译 UI
		ui->retranslateUi(this);
		qDebug() << "osym language changed";
	}

	// 调用基类的changeEvent
	BaseMultilingualWindow::changeEvent(event);
}