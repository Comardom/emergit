//
// Created by comardom on 2025/12/10.
//


#include "OSymphonica.h"

// #include "BaseMultilingualWindow.h"
#include "ui_OSymphonica.h"
#include "plugin/Shutdown/Shutdown.h"

#include <memory>

OSymphonica::OSymphonica(QWidget *parent)
	: BaseMultilingualWindow(parent)
	, ui(new Ui::OSymphonica)// 实例化 UI 类
{
	// 将所有的组件实例化并摆放到窗口上
	ui->setupUi(this);
	createLanguageMenu();

	connect(
		ui->pushBtnShutdown,
		&QPushButton::clicked,
		this,
		[this](){
			if (!shutdownWindow)
			{
				shutdownWindow = new Shutdown();
				shutdownWindow->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
			}
			shutdownWindow->show();
			shutdownWindow->raise();  // 确保在最前面
			shutdownWindow->activateWindow(); // 激活
			}
	);
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
