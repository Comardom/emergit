//
// Created by comardom on 2026/3/12.
//

#ifndef EMERGIT_FREEBSDEXECSHUTDOWN_H
#define EMERGIT_FREEBSDEXECSHUTDOWN_H

#include "ShutdownForOSInterface.h"

//前向声明
class Shutdown;

class FreeBSDExecShutdown
	:ShutdownForOSInterface{

public:
	// 获取全局唯一实例的静态函数
	static FreeBSDExecShutdown& instance();


	// 这些函数不再是 static，因为我们要通过实例来调用它们
	void schedulePowerOffWithSinglyParaSEC(qint64 fullSecondsToWait) override;
	void cancelShutdownWithoutPara() override;
	void initShutdownPointerWithSinglyShutdownPointerOfItself(Shutdown *shutdown);

	~FreeBSDExecShutdown() override;

	// 禁用拷贝，防止产生第二个实例
	FreeBSDExecShutdown(const FreeBSDExecShutdown&) = delete;
	void operator=(const FreeBSDExecShutdown&) = delete;
private:
	// 【修改】构造函数变私有，且不再带参数
	// 这样别人就不能随便 FreeBSDExecShutdown obj(...) 了
	FreeBSDExecShutdown();
	QTimer *timer;
	QStringList arguments;
	QString program;
};


#endif //EMERGIT_FREEBSDEXECSHUTDOWN_H