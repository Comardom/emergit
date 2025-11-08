//
// Created by comardom on 2025/11/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FirstSplash.h" resolved

#include "FirstSplash.h"
#include "ui_FirstSplash.h"


FirstSplash::FirstSplash(QWidget *parent) : QDialog(parent), ui(new Ui::FirstSplash)
{
	ui->setupUi(this);
}

FirstSplash::~FirstSplash()
{
	delete ui;
}