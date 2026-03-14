//
// Created by comardom on 2026/3/12.
//

#ifndef EMERGIT_WINDOWSEXECSHUTDOWN_H
#define EMERGIT_WINDOWSEXECSHUTDOWN_H

#include "ShutdownForOSInterface.h"

class WindowsExecShutdown
	:ShutdownForOSInterface{

public:
	// 获取全局唯一实例的静态函数
	static WindowsExecShutdown& instance();

	// 这些函数不再是 static，因为我们要通过实例来调用它们
	void schedulePowerOffWithSinglyParaSEC(qint64 fullSecondsToWait) override;
	void cancelShutdownWithoutPara() override;



	// 禁用拷贝，防止产生第二个实例
	WindowsExecShutdown(const WindowsExecShutdown&) = delete;
	void operator=(const WindowsExecShutdown&) = delete;
private:
	// 【修改】构造函数变私有，且不再带参数
	// 这样别人就不能随便 WindowsExecShutdown obj(...) 了
	WindowsExecShutdown();
	bool SetShutdownPrivilege();
};


#endif //EMERGIT_WINDOWSEXECSHUTDOWN_H