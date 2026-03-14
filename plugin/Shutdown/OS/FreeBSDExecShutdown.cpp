//
// Created by comardom on 2026/3/12.
//

#include "FreeBSDExecShutdown.h"

#include <QDateTime>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "../Shutdown.h"

FreeBSDExecShutdown& FreeBSDExecShutdown::instance()
{
	// 只会在第一次执行时创建 _instance
	// 之后无论调用多少次，都直接返回已经创建好的那一个
	static FreeBSDExecShutdown _instance;
	return _instance;
}

FreeBSDExecShutdown::FreeBSDExecShutdown()
{
	qDebug() << "FreeBSDExecShutdown实例已创建";
}

void FreeBSDExecShutdown::schedulePowerOffWithSinglyParaSEC(const qint64 fullSecondsToWait)
{
	QDateTime target = QDateTime::currentDateTime().addSecs(
		fullSecondsToWait-(shutdown->getUiDialSecondValueInSEC())
		);
	QString timeStr = target.toString("hh:mm");
	QString cmd = QString("echo \"/sbin/shutdown -p now\" | at %1").arg(timeStr);

	QTimer::singleShot((shutdown->getUiDialSecondValueInSEC()*1000),Qt::PreciseTimer,
			this,[cmd]() {
				QProcess::execute("sh", {"-c", cmd});
			});
}

void FreeBSDExecShutdown::cancelShutdownWithoutPara()
{
	// 取消 at 任务比较复杂（需要获取 job id），
	// 简单暴力的方法是杀死所有 shutdown 进程并清除 at 队列
	QProcess::execute("atrm", {"all"});
}

void FreeBSDExecShutdown::initShutdownPointerWithSinglyShutdownPointerOfItself(Shutdown* shutdown)
{
	this->shutdown = shutdown;

	if(shutdown)
	{
		qDebug()<<"获取shutdown的this指针："<<shutdown;
	}
	else
	{
		qDebug()<<"出问题了，"<<"FreeBSDExecShutdown::"
		<<"initShutdownPointerWithSinglyShutdownPointerOfItself"
		<<"单例调用获取Shutdown的this指针失败";
	}
}