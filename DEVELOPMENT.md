# 目录

1. [编译环境说明](#编译环境说明br-)
2. [窗体使用多语言](#窗体使用多语言-br-)
2. [主窗口在Wayland多屏幕下的显示策略](#主窗口在wayland多屏幕下的显示策略br-)
3. [集体设置属性（for-each）](#集体设置属性br-)
4. [connect函数注意事项](#connect函数注意事项br-)

---
## 编译环境说明<br />


### 目标编译环境
* Qt版本 6.5.0+
* C++版本 23
* CMake版本 4.2.3+

### 开发机环境
* Manjaro Linux  6.18.12
* KDE Plasma 6.5.5
* Wayland
* Qt Framework 6.10.2
* gcc(g++) 15.2.1
* ninja  1.13.2


---

## 窗体使用多语言 <br />
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

## 主窗口在Wayland多屏幕下的显示策略<br />
打开程序时，鼠标在哪里，Splash就在哪里，主窗口也在哪里

---
## 集体设置属性<br />
量使用这种for-each，用findChildren，记得冒号后面要加as-const优化性能
```
const auto dials = this->findChildren<QDial*>();
for(auto* dial : std::as_const(dials))
{
    ……
}
```
---
## connect函数注意事项<br />
第三个参数使用this指针然后第四个参数捕获this用lambda可以防止内存泄漏和野指针导致的崩溃

---