# 目录

1. [编译环境说明](#编译环境说明br-)
2. [Windows下Clion的配置]()
3. [窗体使用多语言](#窗体使用多语言-br-)
4. [主窗口在Wayland多屏幕下的显示策略](#主窗口在wayland多屏幕下的显示策略br-)
5. [集体设置属性（for-each）](#集体设置属性br-)
6. [connect函数注意事项](#connect函数注意事项br-)
7. [XxExecShutdown-EmergitShutdownExecManager的单例模式、工厂模式](#xxexecshutdown-shutdownexecmanager的单例模式工厂模式)

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

### 其他说明
* Windows也可以使用msvc，但是目前还没有经过测试
* freeBSD请使用Clang，已经过测试
* Mac OS暂时无法测试


---

## Windows下Clion的配置

1. 安装qt
2. 寻找qt所在文件夹，形如“C:\Qt\6.x.x\mingw_64”
3. 在设置-构建、执行、部署-CMake中找到Debug和Release
4. 没有就新建一个
5. 在两个profile的CMake选项中加入这个：
   * “-DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/mingw_64"”
6. 把6.x.x改成你自己的版本
7. 在设置-构建、执行、部署-工具链中找到MinGW
8. 没有就自己新建
9. 把MinGW的路径改成“C:\Qt\Tools\mingwXXXX_64”
10. 把XXXX改成你自己的版本，什么版本自己去找
11. 在右上角的项目名处点击下拉菜单找到编辑配置
12. 点进环境变量
13. 加入一条环境变量如下：
    * Name : PATH
    * Value : C:\Qt\6.x.x\mingw_64\bin;%PATH%
14. 把6.x.x改成你自己的版本

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
量使用这种for-each，用findChildren，也可以加入正则表达式
```
const auto things = this->findChildren<QDial*>(QRegularExpression(".*"));
for(auto* thing : things)
{
    ……
}
```
---
## connect函数注意事项<br />
第三个参数使用this指针然后第四个参数捕获this用lambda可以防止内存泄漏和野指针导致的崩溃

---

## XxExecShutdown-EmergitShutdownExecManager的单例模式、工厂模式
所有系统的关机执行都是放在单独的文件中，所以通过工厂模式制作统一管理器<br />
XxExecShutdown这个类是只能创建一次实例，禁止拷贝，以后每次调用都是调用那个static的实例<br />
使用这个类的方法：ShutdownExecManager.schedulePowerOffWithSinglyParaSEC(60);
和ShutdownExecManager.cancelShutdownWithoutPara();<br />
这里两句话都是同一个实例<br />
创建一个对应系统的类，需要继承ShutdownForOSInterface这个接口，这个接口继承了QObject.<br />
目前有FreeBSD的ExecShutdown较为特殊，
需要先FreeBSDExecShutdown::instance().initShutdownPointerWithSinglyShutdownPointerOfItself(this);
才能正常使用其他功能<br />
至于Emergit这个前缀，是为了防止污染宏定义.
---