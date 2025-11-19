//
// Created by comardom on 2025/11/12.
//

#include "FirstSplashThread.h"
#include <QTimer>
#include <memory>


int FirstSplashThread::firstSplashShow = 3000;
bool FirstSplashThread::isRejectedToShow = false;

FirstSplashThread::FirstSplashThread()
{
    ;
}

void FirstSplashThread::run()
{
    if(isRejectedToShow)
    {
        msleep(0);
    }
    else
    {
        msleep(firstSplashShow);
    }
    emit splashFinished();
}
