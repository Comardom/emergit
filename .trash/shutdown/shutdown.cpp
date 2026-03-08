//
// Created by comardom on 2026/3/8.
//
// void Shutdown::changeSingularUndPluralForDials()
// {
// 	//已废弃
// 	//没啥用，单词长短差太多不好看，所以换成缩写，自然也就不需要加s了
// 	//一共四个参数，触发信号(第二个参数)时第一个参数(dial对象)会抛出一个值
// 	//这个值会传递给第四个参数(lambda)，然后被捕获使用
// 	connect(ui->dialSecond,&QDial::valueChanged,
// 		this,[this](const int x) {
// 			const QString s = (x > 1) ? tr("Seconds") : tr("Second");
// 			ui->labelQuantifierSecond->setText(s);
// 		});
// 	connect(ui->dialMinute,&QDial::valueChanged,
// 		this,[this](const int x) {
// 			const QString s = (x > 1) ? tr("Minutes") : tr("Minute");
// 			ui->labelQuantifierMinute->setText(s);
// 		});
// 	connect(ui->dialHour,&QDial::valueChanged,
// 		this,[this](const int x) {
// 			const QString s = (x > 1) ? tr("Hours") : tr("Hour");
// 			ui->labelQuantifierHour->setText(s);
// 		});
// 	connect(ui->dialDay,&QDial::valueChanged,
// 		this,[this](const int x) {
// 			const QString s = (x > 1) ? tr("Days") : tr("Day");
// 			ui->labelQuantifierDay->setText(s);
// 		});
// }