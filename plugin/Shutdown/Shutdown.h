//
// Created by chara on 2026/1/26.
//

#ifndef EMERGIT_SHUTDOWN_H
#define EMERGIT_SHUTDOWN_H

#include "../../BaseMultilingualWindow.h"

class FreeBSDExecShutdown;
class LinuxExecShutdown;

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
    [[nodiscard]] qint64 getUiDialSecondValueInSEC() const;
    void setCanCloseItself(bool aBool);

protected:
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void changeDaysLimit();
    void perSecondTimeoutToChangeUI();
    void setTimerShot(bool cancel = false);

private:
    bool canCloseItself;
    Ui::Shutdown *ui;
    QTimer *timerCountdown;
    qint64 timeSEC{};
    void dialSettings() const;
    void lcdSettings() const;
    void connectDialToLcd() const;
    void connectMenuBar();
    void addLabelClass() const;
    void loadQSS();
    void connectTimerToChangeUI();
    void connectPushBtnToExec();
    void executeSystemShutdown(qint64 fullSecondsToWait,bool cancel=false);
    [[nodiscard]] qint64 calculateSeconds() const;
};


#endif //EMERGIT_SHUTDOWN_H