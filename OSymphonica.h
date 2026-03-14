//
// Created by comardom on 2025/12/10.
//

#ifndef EMERGIT_OSYMPHONICA_H
#define EMERGIT_OSYMPHONICA_H

#include "BaseMultilingualWindow.h"
#include "plugin/Shutdown/Shutdown.h"
#include <QPointer>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class OSymphonica;
}
QT_END_NAMESPACE
// class Shutdown;
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
	QPointer<Shutdown> shutdownWindow;
};


#endif //EMERGIT_OSYMPHONICA_H