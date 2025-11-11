//
// Created by comardom on 2025/11/8.
//


#include "ui_FirstSplash.h"
#include "FirstSplash.h"

#include <QMessageBox>




FirstSplash::FirstSplash(QWidget *parent) : QDialog(parent), ui(new Ui::FirstSplash)
{
	// 加载UI
	ui->setupUi(this);
	// 实现无边框（取消边框功能）
	this->setWindowFlags(Qt::FramelessWindowHint);
	// 关闭自动释放内存
	this->setAttribute(Qt::WA_DeleteOnClose);
	qDebug("Splash!");
	// QMessageBox::information(this, tr("哇这个好可爱鸭"), tr("按钮被点击了！"));
	connect(ui->pushButton,&QPushButton::clicked,this,&FirstSplash::close);
}

FirstSplash::~FirstSplash()
{
	delete ui;
}