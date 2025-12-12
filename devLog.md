窗体使用多语言：<br />
先创建ui文件，继承自QMainWindow，<br />
然后改掉继承，写成这样：<br />
.h：
```
class [类名] final:  public BaseMultilingualWindow
```
.cpp:

```
: BaseMultilingualWindow(parent)
```
继承BaseMultilingualWindow类，<br />
在头文件中加入
```
#include "BaseMultilingualWindow.h"
```
```
protected:
    void changeEvent(QEvent *event) override; 
```
在构造函数中加入
```
createLanguageMenu();
```
并在cpp中加入函数
```
void [类名]::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // 重新翻译 UI
        ui->retranslateUi(this);
    }

    // 调用基类的changeEvent
    BaseMultilingualWindow::changeEvent(event);
}
```
以保证子类窗口的标题不被基类干扰/保证内部文字可以被翻译<br />
此时子类的窗口外观不继承父类，而菜单上的语言按钮为实时生成，对每个子类窗口都适用

---

主窗口在Wayland多屏幕下的显示策略是：<br />
打开程序时，鼠标在哪里，Splash就在哪里，主窗口也在哪里