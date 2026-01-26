//
// Created by chara on 2026/1/26.
//

#ifndef EMERGIT_SHUTDOWN_H
#define EMERGIT_SHUTDOWN_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Shutdown;
}

QT_END_NAMESPACE

class Shutdown : public QMainWindow {
    Q_OBJECT

public:
    explicit Shutdown(QWidget *parent = nullptr);

    void qwerty();

    ~Shutdown() override;

private:
    Ui::Shutdown *ui;
};


#endif //EMERGIT_SHUTDOWN_H