#小学期 Qt 大作业

##特性

* 使用`openGL`进行绘图
* 使用`QThread`进行多线程异步计算
* 算法复杂度优化到了`O(NlogN)`，支持实时100W个点的计算

##实现

一共有5个窗口类，2个openGL窗口类

* AskWidget

  从`QWidget`继承，用于获得用户输入

* calcKernel

  从`QThread`继承，用于多线程计算

* GetTree

  使用`O(NlogN)`的曼哈顿距离最小生成树算法和`O(N)`的树形动态规划算法

* MainWidget

  从`QWidget`继承，主窗口，控制openGL部件和工具栏等部件的交互

* Mini

  从`QGLWidget`继承，负责小地图的显示

* ToolBar

  从`QWidget`继承，负责工具条的显示

* Widget

  从`QGLWidget`继承，负责主窗口的绘制
