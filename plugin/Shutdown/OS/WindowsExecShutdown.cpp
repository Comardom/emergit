//
// Created by comardom on 2026/3/12.
//
#include "WindowsExecShutdown.h"
#include <QDebug>
//致看到这行注释的人：我不懂WindowAPI开发，具体问题请咨询搜索引擎与AI，欢迎提issue
#if defined(Q_OS_WIN)
#include <windows.h>
#include <cstdint>


WindowsExecShutdown& WindowsExecShutdown::instance()
{
	// 只会在第一次执行时创建 _instance
	// 之后无论调用多少次，都直接返回已经创建好的那一个
	static WindowsExecShutdown _instance;
	return _instance;
}

WindowsExecShutdown::WindowsExecShutdown()
{
	qDebug() << "WindowsExecShutdown实例已创建";
}

void WindowsExecShutdown::schedulePowerOffWithSinglyParaSEC(const qint64 fullSecondsToWait)
{
	cancelShutdownWithoutPara();
	if (!SetShutdownPrivilege())
	{
		qCritical() << "权限提升失败！请尝试以管理员身份运行";
	}
	// Windows API 的 InitiateSystemShutdownEx 支持倒计时
	// 参数含义：计算机名, 提示语, 倒计时秒数, 强制关闭, 重启(false为关机)
	BOOL result = InitiateSystemShutdownEx(
		NULL,                       // 本地机器
		const_cast<LPWSTR>(L"系统即将在倒计时结束后关闭。请保存所有工作文件。"),
		static_cast<DWORD>(fullSecondsToWait),             // 倒计时
		TRUE,                       // 强制关闭所有应用
		FALSE,                      // 不重启，执行关机
		SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_FLAG_PLANNED    // 关机原因
	);
	if (result)
	{
		qDebug() << "Windows 关机计划成功：" << fullSecondsToWait << "秒后";
	}
	else
	{
		qWarning() << "错误代码：" << GetLastError();
	}
}

void WindowsExecShutdown::cancelShutdownWithoutPara()
{
	SetShutdownPrivilege();
	if (AbortSystemShutdown(NULL))
	{
		qDebug() << "Windows 关机计划已成功取消";
	}
	else
	{
		qDebug()<<"关机取消失败";
	}
}

// 辅助函数：用来提升程序权限
bool WindowsExecShutdown::SetShutdownPrivilege() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// 1. 获取当前进程的令牌
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	// 2. 查找关机权限的 LUID
	// LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
	{
		CloseHandle(hToken);
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 重点：必须重置错误代码再检查
	SetLastError(ERROR_SUCCESS);
	// 3. 提升权限
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	bool success = (GetLastError() == ERROR_SUCCESS);
	CloseHandle(hToken); // 记得关闭句柄！
	return success;
}

#endif