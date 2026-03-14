//
// Created by comardom on 2026/3/13.
//

#ifndef EMERGIT_SHUTDOWNFOROSINTERFACE_H
#define EMERGIT_SHUTDOWNFOROSINTERFACE_H
#include <QObject>

class Shutdown;
class ShutdownForOSInterface : public QObject{
	Q_OBJECT
public:
	~ShutdownForOSInterface() override = default;
	virtual void schedulePowerOffWithSinglyParaSEC(qint64 fullSecondsToWait) = 0;
	virtual void cancelShutdownWithoutPara() = 0;
protected:
	Shutdown* shutdown = nullptr;
};


#endif //EMERGIT_SHUTDOWNFOROSINTERFACE_H