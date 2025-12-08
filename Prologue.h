//
// Created by comardom on 2025/12/7.
//

#ifndef EMERGIT_PROLOGUE_H
#define EMERGIT_PROLOGUE_H
#include <QPixmap>
#include <QScreen>
#include <QWidget>


class Prologue
{
public:
	explicit Prologue();
	bool setNeedFastestInit();
	bool setNeedFastestInit(bool aBool);
	QPixmap* getScaledSplashPix();
	// QPixmap& createDefaultPixmap();
	QScreen* getScreenPtr() const;
	int getSplashTime() const;
	void computeXYUndMoveWindow(QWidget &w) const;
	~Prologue();
private:
	// 提供选项调整Splash
	bool needFastestInit;
	enum class splashOption;
	int splashTime;
	void initSplashTime();
	//先获取屏幕指针，然后获取像素和像素比信息
	QScreen *screen;
	QRect screenGeometry;
	qreal devicePixelRatio;
	void pullPrimaryScreenInfo();
	// 先根据屏幕信息确定尺寸，再把pix缩放成scaledPix
	QSize splashTargetSize;
	QPixmap pix;
	QPixmap scaledPix;
	void initSplashPicture();


};


#endif //EMERGIT_PROLOGUE_H