目录
|-官网
|-开源项目demo
|-指南
|-安装环境中遇到的问题
|-需要的库文件
|-Qt基本类别


【官网】
https://account.qt.io/
https://www.qt.io/offline-installers

【开源项目demo】
https://blog.csdn.net/zx249388847/article/details/79894025
http://c.biancheng.net/view/1802.html

ros-qt linux环境.pro配置
https://blog.csdn.net/qq_38260691/article/details/79590206

【指南】
https://qtguide.ustclug.org/
Doxygen注释格式
https://blog.csdn.net/jeamywu/article/details/5730006
控件指南
https://blog.csdn.net/hiwoshixiaoyu/article/details/70859879

【安装环境中遇到的问题】
Q:1）QtCreator: No valid kits found

A:
https://blog.csdn.net/liang19890820/article/details/49894691
https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/index

全选安装

【需要的库文件】
boost
resources
rosconsole
std_msgs
转换%(package)s为合法

<QtGui/QMainWindow>   ->  分开声明5.1.12

boost/qt4 问题解决方案
https://bugreports.qt.io/browse/QTBUG-22829

2【Qt基本类别】
Q_OBJECT
凡是QObject类（不管是直接子类还是间接子类），都应该在第一行代码写上Q_OBJECT。【moc 宏展开】使得多出来一些机制
Q_SIGNALS，Q_SLOTS， Q_EMIT
它告诉QT不要定义moc关键字signals,slots和emit，因为这些名字可能将被用于第三方库，例如Boost。

explicit关键字
https://blog.csdn.net/ma_nong/article/details/7696690 可以禁止隐式转换

2-1【QWidget】
QWidget类是所有用户界面对象的基类。
Widget是用户界面的基本单元：它从窗口系统接收鼠标，键盘和其他事件，并在屏幕上绘制自己。
每个Widget都是矩形的，它们按照Z-order进行排序。 
https://www.cnblogs.com/billxyd/p/6924229.html

