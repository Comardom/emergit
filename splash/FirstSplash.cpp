//
// Created by comardom on 2025/11/8.
//


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