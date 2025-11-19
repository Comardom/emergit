//
// Created by comardom on 2025/11/8.
//


#include "ui_FirstSplash.h"
#include "FirstSplash.h"



#include <memory>
#include <QMessageBox>
#include <QApplication>
// #include <QVBoxLayout>
#include <qscreen.h>
#include <QLabel>
#include <QWidget>
#include <QPixmap>

FirstSplash::FirstSplash(QWidget *parent) : QDialog(parent), ui(new Ui::FirstSplash)
{
	// 加载UI
	ui->setupUi(this);
	// 实现无边框（取消边框功能）
	this->setWindowFlags(Qt::FramelessWindowHint);
	// 关闭自动释放内存
	this->setAttribute(Qt::WA_DeleteOnClose);
	// 窗口居中
	// this->move(QApplication::primaryScreen()->geometry().center() - this->rect().center());
	// qDebug("Splash!");



	// 创建主布局
	mainLayout = new QVBoxLayout(this);
	// 创建并设置图片标签
	imageLabel = new QLabel(this);
	if(const QPixmap pixmap(":../img/dyingStarUndMaria.bmp");!pixmap.isNull())
	{
		imageLabel->setPixmap(pixmap.scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else
	{
		imageLabel->setText(tr("藏新芽"));
		imageLabel->setAlignment(Qt::AlignCenter);
		// imageLabel->setStyleSheet("font-size: 18px; color: #333;");
	}
	imageLabel->setAlignment(Qt::AlignCenter);
	// 添加到布局
	mainLayout->addWidget(imageLabel);
	// 设置对话框属性
	setLayout(mainLayout);
	setWindowTitle(tr("藏新芽"));
	setFixedSize(600, 400); // 固定大小适合启动画面



	//线程实例化
	firstSplashThread = std::make_unique<FirstSplashThread>();
	// 启动线程，相当于执行run()
	firstSplashThread->start();

	// 临时关闭窗口按钮
	// connect(ui->pushButton_2,&QPushButton::clicked,this,&FirstSplash::close);

	connect(firstSplashThread.get(), &FirstSplashThread::splashFinished,
			this, &FirstSplash::do_splashFinished);
	firstSplashThread->start();
}

FirstSplash::~FirstSplash()
{
	delete ui;
	delete mainLayout;
	delete imageLabel;
}

void FirstSplash::do_splashFinished()
{
	// 停止线程
	firstSplashThread->quit();
	firstSplashThread->wait();  // 等待线程完全结束

	// emit

	// 智能指针会自动管理内存
	this->close();
}
