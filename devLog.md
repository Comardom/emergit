窗体使用多语言：<br />
继承BaseMultilingualWindow类，并在构造函数中加入
```
createLanguageMenu();
```
以保证子类窗口的标题等不被干扰<br />
此时子类的窗口外观不继承父类，而菜单上的语言按钮为实时生成，对每个子类窗口都适用

---

