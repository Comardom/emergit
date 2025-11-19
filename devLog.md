窗体使用多语言：<br />
继承BaseMultilingualWindow类，<br />
在头文件中加入
```
protected:
    void changeEvent(QEvent *event) override; 
```
在构造函数中加入
```
createLanguageMenu();
```
并加入函数
```
void 【类名】::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // 重新翻译 MainWindow 的 UI
        ui->retranslateUi(this);
        qDebug() << "MainWindow language changed";
    }

    // 调用基类的changeEvent
    BaseMultilingualWindow::changeEvent(event);
}
```
以保证子类窗口的标题不被基类干扰/保证内部文字可以被翻译<br />
此时子类的窗口外观不继承父类，而菜单上的语言按钮为实时生成，对每个子类窗口都适用

---

