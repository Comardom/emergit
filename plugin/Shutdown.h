//
// Created by chara on 2026/1/26.
//

#ifndef EMERGIT_SHUTDOWN_H
#define EMERGIT_SHUTDOWN_H

#include <QMainWindow>
#include "../BaseMultilingualWindow.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class Shutdown;
}

QT_END_NAMESPACE

class Shutdown final:  public BaseMultilingualWindow {
    Q_OBJECT

public:
    explicit Shutdown(QWidget *parent = nullptr);

    void lcdSettings() const;

    ~Shutdown() override;

protected:
    void changeEvent(QEvent *event) override;

private:
    Ui::Shutdown *ui;
    void dialSettings() const;

    void connectDialToLcd() const;

    void changeSingularUndPluralForDials();
};


#endif //EMERGIT_SHUTDOWN_H