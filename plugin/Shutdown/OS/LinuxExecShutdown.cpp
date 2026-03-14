//
// Created by comardom on 2026/3/12.
//

#include <QCoreApplication>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QDateTime>
#include <QDebug>

#include "LinuxExecShutdown.h"


LinuxExecShutdown& LinuxExecShutdown::instance()
{
	// 只会在第一次执行时创建 _instance
	// 之后无论调用多少次，都直接返回已经创建好的那一个
	static LinuxExecShutdown _instance;
	return _instance;
}

LinuxExecShutdown::LinuxExecShutdown()
{
	qDebug() << "LinuxExecShutdown实例已创建";
}

void LinuxExecShutdown::schedulePowerOffWithSinglyParaSEC(const qint64 fullSecondsToWait)
{
	//建立 DBus 接口连接 (系统总线)
	QDBusInterface manager(
		"org.freedesktop.login1",
		"/org/freedesktop/login1",
		"org.freedesktop.login1.Manager",
		QDBusConnection::systemBus()
		);
	if (!manager.isValid())
	{
		qCritical() << "无法连接到 logind DBus 接口:"
		<< QDBusConnection::systemBus().lastError().message();
		return;
	}
	//先获取目前系统的毫秒级时间，然后换成微秒
	const qulonglong nowtUSEC =
		static_cast<qulonglong>(QDateTime::currentMSecsSinceEpoch()) * 1000LLU;
	//然后把目标关机时间戳算出来
	const qulonglong targetUSEC =
		nowtUSEC + static_cast<qulonglong>(fullSecondsToWait) * 1000LLU * 1000LLU;
	//call的时候就执行了，返回信息只是为了看看情况
	const QDBusMessage msg = manager.call("ScheduleShutdown", "poweroff", targetUSEC);
	if (msg.type() == QDBusMessage::ErrorMessage)
	{
		qWarning() << "DBus 错误:" << msg.errorMessage();
	}
	else
	{
		qDebug() << "定时关机设置成功，将在" << fullSecondsToWait << "秒后关机。";
	}
}

void LinuxExecShutdown::cancelShutdownWithoutPara()
{
	//连接总线
	QDBusInterface manager(
		"org.freedesktop.login1",
		"/org/freedesktop/login1",
		"org.freedesktop.login1.Manager",
		QDBusConnection::systemBus()
		);

	//表示是否有任务被取消
	const QDBusReply<bool> reply = manager.call("CancelScheduledShutdown");

	if (reply.isValid() && reply.value())
	{
		qDebug() << "已成功取消定时关机任务。";
	}
	else
	{
		qDebug() << "没有正在运行的定时关机任务。";
	}
}