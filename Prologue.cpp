//
// Created by comardom on 2025/12/7.
//

#include "Prologue.h"

#include <iostream>
#include <optional>

Prologue::Prologue() : needFastestInit(false)
{
	initSplashTime();
	pullPrimaryScreenInfo();
	if(needFastestInit)
	{
		std::cout<<"skip splash picture"<<std::endl;
	}
	else
	{
		initSplashPicture();
	}
}

// TODO : 需要写入文件保存

bool Prologue::setNeedFastestInit()
{
	needFastestInit =! needFastestInit;
	return needFastestInit;
}

bool Prologue::setNeedFastestInit(const bool aBool = false)
{
	needFastestInit = aBool;
	return needFastestInit;
}

void Prologue::pullPrimaryScreenInfo()
{
	// 获取主屏幕
	if((screen = QGuiApplication::primaryScreen()))
	{
		// 获取可用屏幕空间
		screenGeometry = screen->availableGeometry();
		// 获取像素比信息
		devicePixelRatio = screen->devicePixelRatio();
	}
	else
	{
		std::cerr<<"prologue: screen null"<<std::endl;
	}
}

void Prologue::initSplashPicture()
{
	// TODO : 需要svg读取
	pix = QPixmap(":/img/b");

	if(devicePixelRatio > 1.5)
	{
		// 高分屏：使用更大尺寸
		splashTargetSize = screenGeometry.size() * 0.8;
	}
	else
	{
		// 普通屏幕：使用适中尺寸
		splashTargetSize = screenGeometry.size() * 0.5;
	}

	// 高质量缩放
	scaledPix = pix.scaled(
		//目标尺寸
		splashTargetSize,
		//保持长宽比
		Qt::KeepAspectRatio,
		// 这里可以用Qt::FastTransformation快速缩放，
		// 但是因为开屏展示需要两秒以上的延迟，
		// 所以fast的时间可以忽略
		Qt::SmoothTransformation
	);
}

void Prologue::initSplashTime()
{
	splashTime = 2000;
}

int Prologue::getSplashTime() const
{
	return splashTime;
}

void Prologue::computeXYUndMoveWindow(QWidget &w) const
{
	if(screen)
	{
		const int x = (screenGeometry.width() - w.width()) / 2;
		const int y = (screenGeometry.height() - w.height()) / 2;
		w.move(x, y);
	}
	else
	{
		std::cerr<<"screen null"<<std::endl;
	}
}


QPixmap* Prologue::getScaledSplashPix()
{
	if(!needFastestInit && !scaledPix.isNull())
	{
		return &scaledPix;

	}
	else
	{
		std::cerr<<"No scaled pixmap"<<std::endl;
		return nullptr;
	}
}

QScreen* Prologue::getScreenPtr() const
{
	return screen;
}

Prologue::~Prologue()
=default;

