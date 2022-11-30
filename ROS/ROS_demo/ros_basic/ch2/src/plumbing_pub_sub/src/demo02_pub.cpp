/*
 * @Author:Divenire
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-07 19:55:59
 * @LastEditors: Please set LastEditors
 * @Description: 
 *  需求: 循环发布人的信息
 *  
 * 
 * @FilePath: /ch2/src/plumbing_pub_sub/src/demo02_pub.cpp
 */

#include "ros/ros.h"
#include "plumbing_pub_sub/person.h"
#include "csignal"


void MySigintHandler(int sig)
{
	//这里主要进行退出前的数据保存、内存清理、告知其他节点等工作
	ROS_INFO("shutting down!");
	ros::shutdown();
    exit(0);
}

int main(int argc, char  *argv[])
{
    /* 设置编码 */
    setlocale(LC_ALL,"");

    // 1. 初始化 节点名称talker_person
    ros::init(argc,argv,"QiuDaShuai");

    // 2.创建 ROS 句柄
    ros::NodeHandle nh;

    // 3.创建发布者对象
    ros::Publisher pub = nh.advertise<plumbing_pub_sub::person>("Pig",10);

    // 4.组织被发布者的信息
    plumbing_pub_sub::person p1;
    p1.name = "LiJia";
    p1.age = 999;
    p1.height = 1.99;

    /* 休眠3秒钟，让publisher 在 roscore 注册完毕后在发消息 */
    ros::Duration(3.0).sleep();

    // 5.设置发布频率
    ros::Rate rate(10);

    //覆盖原来的Ctrl+C中断函数，原来的只会调用ros::shutdown()，按下了Ctrl+C，则会调用MySigintHandler
	//为你关闭节点相关的subscriptions, publications, service calls, and service servers，退出进程
    signal(SIGINT, MySigintHandler);

    // 循环发布
    while (ros::ok)
    {
        /* code */
        pub.publish(p1);
        p1.age+=1;
        ROS_INFO("我叫%s,今年%d岁啦，身高%.2f米",p1.name.c_str(),p1.age,p1.height);

        // 按照设定的频率休眠
        rate.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
