/**
 * @file /src/main_window.cpp
 *
 * @brief 简要qt界面
 *
 * @date 2019.1
 **/
/*****************************************************************************
** 
** 头文件
** <QtGui><QMessageBox><iostream>"main_window.hpp"
** 
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "main_window.hpp"

/*****************************************************************************
**
** 命名空间
**
*****************************************************************************/

namespace qt_ros {

using namespace Qt;

/*****************************************************************************
** 组件[MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
	ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

	/*********************
	** 记录日志
	**********************/
	ui.view_logging->setModel(qnode.loggingModel());
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));

    /*********************
    ** 自动开始
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** 组件 [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * 无论是否单击按钮，这些触发器都会触发
 * 已经检查过。
 */

void MainWindow::on_button_connect_clicked(bool check ) {
	if ( ui.checkbox_use_environment->isChecked() ) {
		if ( !qnode.init() ) {
			showNoMasterMessage();
		} else {
			ui.button_connect->setEnabled(false);
		}
	} else {
		if ( ! qnode.init(ui.line_edit_master->text().toStdString(),
				   ui.line_edit_host->text().toStdString()) ) {
			showNoMasterMessage();
		} else {
			ui.button_connect->setEnabled(false);
			ui.line_edit_master->setReadOnly(true);
			ui.line_edit_host->setReadOnly(true);
			ui.line_edit_topic->setReadOnly(true);
		}
	}
}


void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
	bool enabled;
	if ( state == 0 ) {
		enabled = true;
	} else {
		enabled = false;
	}
	ui.line_edit_master->setEnabled(enabled);
	ui.line_edit_host->setEnabled(enabled);
	ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** 实现 [Slots][manually connected]手动链接
*****************************************************************************/

/**
 * 此函数由基础模型发出信号。 当模型改变时
 * 这会将光标向下移动到QListview中的最后一行以确保
 * 用户始终可以看到最新的日志消息。
 */
void MainWindow::updateLoggingView() {
        ui.view_logging->scrollToBottom();
}

/*****************************************************************************
** 实现 [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2>"));
}

/*****************************************************************************
** 实现 [Configuration]
*****************************************************************************/


/*****************************************************************************
** MainWindow::ReadSettings()
** 设置对象   QSettings 
** |
** |-文本框消息 settings.setValue("master_url",ui.line_edit_master->text());
** |-恢复图像restoreGeometry(settings.value("geometry").toByteArray());
** |-文本流 QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
** |-界面文本ui.line_edit_master->setText(master_url);
** |-判断是否写入bool remember = settings.value("remember_settings", false).toBool();
** |-界面检查ui.checkbox_remember_settings->setChecked(remember);
** |-判断检查bool checked = settings.value("use_environment_variables", false).toBool();
** |-如果检查了 不可设置
*****************************************************************************/
void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "qt_ros");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
    	ui.line_edit_master->setEnabled(false);
    	ui.line_edit_host->setEnabled(false);
    	ui.line_edit_topic->setEnabled(false);
    }
}
/*****************************************************************************
** MainWindow::WriteSettings()
** 设置对象   QSettings 
** |
** |-文本框消息 settings.setValue("master_url",ui.line_edit_master->text());
** 
*****************************************************************************/
void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "qt_ros");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace qt_ros

