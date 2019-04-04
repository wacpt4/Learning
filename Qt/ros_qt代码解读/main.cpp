/**
 * @file /src/main.cpp
 *
 * @brief 图形化界面.
 *
 * @date 2019.1
 **/
/*****************************************************************************
**
** 头文件<QtGui><QApplication>，以及主窗口头文件main_window.hpp
**
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "main_window.hpp"

/*****************************************************************************
** 
**主函数
**
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** qt，ros，主窗口，链接，结果
    **********************/
    QApplication app(argc, argv);
    ros_qt::MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
