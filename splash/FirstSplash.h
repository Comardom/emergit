//
// Created by comardom on 2025/11/8.
//

#ifndef EMERGIT_FIRSTSPLASH_H
#define EMERGIT_FIRSTSPLASH_H

#include <QDialog>
#include "FirstSplashThread.h"
#include <QVBoxLayout>

// #include "../BaseMultilingualWindow.h"

class QLabel;
QT_BEGIN_NAMESPACE

namespace Ui
{
	class FirstSplash;
}

QT_END_NAMESPACE

class FirstSplash: public QDialog{
	Q_OBJECT

public:
	explicit FirstSplash(QWidget *parent = nullptr);

	~FirstSplash() override;

private slots:
	void do_splashFinished();

private:
	Ui::FirstSplash *ui;
	// 这是一个计时用的新线程
	std::unique_ptr<FirstSplashThread> firstSplashThread;
	// 创建主布局（使用布局管理器处理图片）
	QVBoxLayout *mainLayout;
	// 创建并设置图片标签
	QLabel *imageLabel;

};


#endif //EMERGIT_FIRSTSPLASH_H