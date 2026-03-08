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
    ~Shutdown() override;


protected:
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void changeDaysLimit();

private:
    Ui::Shutdown *ui;
    void dialSettings() const;
    void lcdSettings() const;
    void connectDialToLcd() const;
    void changeSingularUndPluralForDials();
    void connectMenuBar();
    void addLabelClass() const;
    void loadQSS();
};


#endif //EMERGIT_SHUTDOWN_H