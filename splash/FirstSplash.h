//
// Created by comardom on 2025/11/8.
//

#ifndef EMERGIT_FIRSTSPLASH_H
#define EMERGIT_FIRSTSPLASH_H

#include <QDialog>


QT_BEGIN_NAMESPACE

namespace Ui
{
	class FirstSplash;
}

QT_END_NAMESPACE

class FirstSplash: public QDialog {
	Q_OBJECT

public:
	explicit FirstSplash(QWidget *parent = nullptr);

	~FirstSplash() override;

private:
	Ui::FirstSplash *ui;
};


#endif //EMERGIT_FIRSTSPLASH_H