一些简单的UI设计

Qt 它目前不支持可视化的编辑 QGroupBox 等的子类，只有
Widget  Main Window  Dialog 这些
我希望根对象就是QGroupBox 而不是把它放在一个QWidget中



有些简单的ui设计

将.ui变成.h后，自行调用uic.exe产生对应.h



## ✅ 总结：手动调用命令速查

| 工具          | 命令格式                                         | 示例                                                         |
| ------------- | ------------------------------------------------ | ------------------------------------------------------------ |
| **`uic.exe`** | `uic <input.ui> -o <output.h>`                   | `uic main_window.ui -o ui_main_window.h`                     |
| **`moc.exe`** | `moc -I. -DQT_XXX_LIB <input.h> -o <output.cpp>` | `moc -I. -DQT_WIDGETS_LIB main_window.h -o moc_main_window.cpp` |