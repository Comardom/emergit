//
// Created by comardom on 2026/3/13.
//

// linux:
// if(cancel)
	// {
	//     arguments << "-c";
	// }
	// else
	// {
	//     arguments << "-h" << QString("+%1").arg(timeSecondsJustRemoveSeconds / 60);
	// }




//freebsd:
// if(cancel)
// {
// 	// FreeBSD 取消关机通常需要 kill 掉那个 shutdown 进程
// 	system("pkill shutdown");
// 	return;
// }
// else
// {
// 	arguments << "-p" << QString("+%1").arg(timeSecondsJustRemoveSeconds / 60)
// 		<< "Timed shutdown by Emergit";
// }



//windows：
// QString program = "shutdown";
// QStringList arguments;
// if(cancel) arguments << "-a";
// else arguments << "-s" << "-t" << QString::number(fullSecondsToWait);
// if (cancel)
// {
// 	if(!QProcess::execute(program, arguments))
// 	{
// 		qWarning() << "Failed to cancel shutdown";
// 		QMessageBox::warning(this, tr("错误"),
// 			tr("无法执行取消命令"));
// 	}// 取消操作同步执行即可
// }
// else
// {
// 	if(!QProcess::startDetached(program, arguments))
// 	{
// 		qWarning() << "Failed to start shutdown process";
// 		QMessageBox::warning(this, tr("错误"),
// 			tr("无法执行关机命令"));
// 	} // 关机操作必须异步/分离执行
// }