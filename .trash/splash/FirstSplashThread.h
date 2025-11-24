//
// Created by comardom on 2025/11/12.
//

#ifndef EMERGIT_FIRSTSPLASHTHREAD_H
#define EMERGIT_FIRSTSPLASHTHREAD_H
#include <cmath>
#include <QThread>


class FirstSplashThread final: public QThread
{
	Q_OBJECT
public:
	static int firstSplashShow;
	static bool isRejectedToShow;
	explicit FirstSplashThread();

	signals:
		void splashFinished();
protected:
	void run() override;
private:
};


#endif //EMERGIT_FIRSTSPLASHTHREAD_H