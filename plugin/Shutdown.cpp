//
// Created by chara on 2026/1/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Shutdown.h" resolved

#include "Shutdown.h"
#include "ui_Shutdown.h"


Shutdown::Shutdown(QWidget *parent) : QMainWindow(parent), ui(new Ui::Shutdown) {
    ui->setupUi(this);
}

Shutdown::~Shutdown() {
    delete ui;
}
void qwerty() {
    ;
}