//
// Created by comardom on 2025/12/10.
//

#ifndef EMERGIT_OSYMPHONICA_H
#define EMERGIT_OSYMPHONICA_H

#include "BaseMultilingualWindow.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
	class OSymphonica;
}

QT_END_NAMESPACE

class OSymphonica final:  public BaseMultilingualWindow
{
	Q_OBJECT

public:
	explicit OSymphonica(QWidget *parent = nullptr);

	~OSymphonica() override;

protected:
	void changeEvent(QEvent *event) override;

private:
	Ui::OSymphonica *ui;
};


#endif //EMERGIT_OSYMPHONICA_H