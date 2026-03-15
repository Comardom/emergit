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
	: timer(new QTimer())
{
	timer->setSingleShot(true); // 设置为单次触发模式
	connect(timer, &QTimer::timeout,
		this, [this]() {
			if(!shutdown) return;
			//归还窗口关闭权力
			shutdown->setCanCloseItself(true);
			qint64 pid = 0;
			if(QProcess::startDetached(program, arguments, QString(), &pid))
			{
				qDebug() << "系统关机进程已分离，PID:" << pid;
			}
			else
			{
				qCritical() << "启动 shutdown 失败！请检查当前用户是否属于 operator 组。";
				QMessageBox::warning(shutdown, "操作受限",
					"启动 shutdown 失败！请检查当前用户是否属于 operator 组。");
			}
	});
	qDebug() << "FreeBSDExecShutdown实例已创建，timer指针已创建";
}

void FreeBSDExecShutdown::schedulePowerOffWithSinglyParaSEC(const qint64 fullSecondsToWait)
{
	cancelShutdownWithoutPara();
	//禁止关闭窗口
	shutdown->setCanCloseItself(false);

	const qint64 targetSEC = fullSecondsToWait-(shutdown->getUiDialSecondValueInSEC());
	//这是向上取整的意思
	const qint64 targetMIN = (targetSEC + 59)/60LL;
	//相对时间
	QString timeParam = QString("+%1").arg(targetMIN);
	program = "/sbin/shutdown";
	//先清空参数列表，防止参数叠加
	arguments.clear();
	arguments << "-p" << timeParam;
	qDebug() << "提交系统级关机任务:" << program << arguments.join(" ");
	timer->stop();

	timer->start(shutdown->getUiDialSecondValueInSEC()*1000);
}

void FreeBSDExecShutdown::cancelShutdownWithoutPara()
{
	shutdown->setCanCloseItself(true);
	// 停止正在倒计时的 Timer
	if(timer->isActive()) {timer->stop();}
	// 在 FreeBSD 中取消正在进行的倒计时关机，需要杀死 shutdown 进程
	// 或者执行 shutdown -c (如果系统版本支持)
	// 最通用的做法是 killall
	qDebug() << "正在取消所有后台关机任务...";
	QProcess::execute("killall", {"shutdown"});
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

FreeBSDExecShutdown::~FreeBSDExecShutdown()
{
	delete timer; timer = nullptr;
}