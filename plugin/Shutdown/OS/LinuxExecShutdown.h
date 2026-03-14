//
// Created by comardom on 2026/3/12.
//

#ifndef EMERGIT_LINUXEXECSHUTDOWN_H
#define EMERGIT_LINUXEXECSHUTDOWN_H

#include "ShutdownForOSInterface.h"

class LinuxExecShutdown
	:ShutdownForOSInterface{

public:
	// 获取全局唯一实例的静态函数
	static LinuxExecShutdown& instance();

	// 这些函数不再是 static，因为我们要通过实例来调用它们
	void schedulePowerOffWithSinglyParaSEC(qint64 fullSecondsToWait) override;
	void cancelShutdownWithoutPara() override;

	// 禁用拷贝，防止产生第二个实例
	LinuxExecShutdown(const LinuxExecShutdown&) = delete;
	void operator=(const LinuxExecShutdown&) = delete;
private:
	// 【修改】构造函数变私有，且不再带参数
	// 这样别人就不能随便 LinuxExecShutdown obj(...) 了
	LinuxExecShutdown();
};


#endif //EMERGIT_LINUXEXECSHUTDOWN_H