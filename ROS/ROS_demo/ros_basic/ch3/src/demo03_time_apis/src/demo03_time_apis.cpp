/*
 * @Author: your name
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-08 16:51:21
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ch3/src/demo03_time_apis/src/demo03_time_apis.cpp
 */
#include "ros/ros.h"

/*
    需求1:  演示时间相关操作(获取当前时刻 设置指定时刻)
    实现：
        1.准备（头文件、节点初始化、 Nodehandle创建
        2.获取当前时刻
        3.设置指定时刻
    需求2:  程序执行中停顿5秒
    实现：
        1.  创建持续时间对象
        2.  休眠
    需求3:  已知程序开始运行的时刻，和程序运行的时间，求运行结束的时刻
    实现:
        1.获取开始执行的时刻
        2.模拟运行时间(N秒)
        3.计算结束时刻=开始持续时间
    注意：
        1.时刻与持续时间可以执行加减
        2.持续时间之间也可以执行加减
        3.时刻之间值可以相减，不可以相加

*/

void timer_callback(const ros::TimerEvent & event)
{
    ROS_INFO("-------------");
    // 输出现在的时间
    ROS_INFO("event:%s",std::to_string(event.current_real.toSec()).c_str());
}

int main(int argc, char  *argv[])
{

    /* 设置编码 */
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"hello_time");

    
    ROS_INFO("-------------时刻---------------");
    ros::NodeHandle nh;//必须创建句柄，否则时间没有初始化，导致后续API调用失败
    ros::Time right_now = ros::Time::now();//将当前时刻封装成对象
    ROS_INFO("当前时刻:%.2f",right_now.toSec());//获取距离 1970年01月01日 00:00:00 的秒数
    ROS_INFO("当前时刻:%d",right_now.sec);//获取距离 1970年01月01日 00:00:00 的秒数

    ros::Time someTime(100,100000000);// 参数1:秒数  参数2:纳秒
    ROS_INFO("时刻:%.2f",someTime.toSec()); //100.10
    ros::Time someTime2(100.3);//直接传入 double 类型的秒数
    ROS_INFO("时刻:%.2f",someTime2.toSec()); //100.30


    ROS_INFO("-------------持续时间---------------");
    ROS_INFO("当前时刻:%.2f",ros::Time::now().toSec());
    ros::Duration du(10);//持续10秒钟,参数是double类型的，以秒为单位
    du.sleep();//按照指定的持续时间休眠
    ROS_INFO("持续时间:%.2f",du.toSec());//将持续时间换算成秒
    ROS_INFO("当前时刻:%.2f",ros::Time::now().toSec());

    ROS_INFO("-------------时间运算---------------");
    ros::Time now = ros::Time::now();
    ros::Duration du1(10);
    ros::Duration du2(20);
    ROS_INFO("当前时刻:%.2f",now.toSec());
    //1.time 与 duration 运算
    ros::Time after_now = now + du1;
    ros::Time before_now = now - du1;
    ROS_INFO("当前时刻之后:%.2f",after_now.toSec());
    ROS_INFO("当前时刻之前:%.2f",before_now.toSec());

    //2.duration 之间相互运算
    ros::Duration du3 = du1 + du2;
    ros::Duration du4 = du1 - du2;
    ROS_INFO("du3 = %.2f",du3.toSec());
    ROS_INFO("du4 = %.2f",du4.toSec());
    //PS: time 与 time 不可以运算
    // ros::Time nn = now + before_now;//异常


    ROS_INFO("-------------定时器---------------");

    /**
    * \brief 创建一个定时器，按照指定频率调用回调函数。
    *
    * \param period 时间间隔
    * \param callback 回调函数
    * \param oneshot 如果设置为 true,只执行一次回调函数，设置为 false,就循环执行。
    * \param autostart 如果为true，返回已经启动的定时器,设置为 false，需要手动启动。
    * 
    */

    ros::Timer timer = nh.createTimer(ros::Duration(1),timer_callback,false,false);

    // 启动定时器
    timer.start();
    // 循环处理定时器的回调函数
    ros::spin();
    return 0;
}
