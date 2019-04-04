/**
 * @file /include/qt_ros/qnode.hpp
 *
 * @brief 交流中心
 *
 * @date 2019.1
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_ros_QNODE_HPP_
#define qt_ros_QNODE_HPP_

/*****************************************************************************
** 
**头文件
**
*****************************************************************************/


#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>


/*****************************************************************************
** 命名空间
*****************************************************************************/

namespace qt_ros {

/*****************************************************************************
** 
**公类 继承QThread，1日志获取2注销3初始化4初始化服务器详细参数5运行 枚举ros等级 对接
**QStringListModel* loggingModel(){} log()记录等级与数据流
**
**私类 等级，字符流，发布者，数据流
**
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	**
  ** 日志
  **
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
    QStringListModel logging_model;
};

}

#endif /* qt_ros_QNODE_HPP_ */
