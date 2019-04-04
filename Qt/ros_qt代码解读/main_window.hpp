/**
 * @file /include/ros_qt/main_window.hpp
 *
 * @brief ros_qt for basic control to start ros.
 *
 * @date 2019.1
 **/
#ifndef ros_qt_MAIN_WINDOW_H
#define ros_qt_MAIN_WINDOW_H

/*****************************************************************************
**
** 头文件                                                                 
**
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
**
** 命名空间                                                                
**
*****************************************************************************/

namespace ros_qt {

/*****************************************************************************
** 
**接口 [MainWindow]                                                   
**
*****************************************************************************/


/**
 *
 * @brief Qt中心，有所有交互操作
 *
**/
 
class MainWindow : public QMainWindow {
Q_OBJECT

public:
  /******************************************
  **
  **
  **
  *******************************************/
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // 开始读取qt程序设置
	void WriteSettings(); // 关闭保存qt程序设置
	void showNoMasterMessage();//显示连接失败
	void closeEvent(QCloseEvent *event); // 重写closeEvent()


public Q_SLOTS://声明信号槽
  /******************************************
  **
  ** 自动连接 (connectSlotsByName())
  **
  *******************************************/
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);

    /******************************************
    **
    ** 手动链接 虽然还是自动了
    **
    *******************************************/
    void updateLoggingView(); 

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}

#endif // ros_qt_MAIN_WINDOW_H
