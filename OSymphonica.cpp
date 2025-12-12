//
// Created by comardom on 2025/12/10.
//


#include "OSymphonica.h"

#include "BaseMultilingualWindow.h"
#include "ui_OSymphonica.h"


OSymphonica::OSymphonica(QWidget *parent)
	: BaseMultilingualWindow(parent)
	, ui(new Ui::OSymphonica)
{
	ui->setupUi(this);
	createLanguageMenu();
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