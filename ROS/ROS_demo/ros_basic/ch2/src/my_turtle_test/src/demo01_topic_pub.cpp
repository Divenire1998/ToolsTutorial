/*
 * @Author: Divenire
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-08 13:51:36
 * @LastEditors: Divenire
 * @Description: 
 * 
    编写 ROS 节点，控制小乌龟画圆

    准备工作:
        1.获取topic(已知: /turtle1/cmd_vel)
        2.获取消息类型(已知: geometry_msgs/Twist)
        3.运行前，注意先启动 turtlesim_node 节点

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建发布者对象
        4.循环发布运动控制消息
 * @FilePath: /ch2/src/my_turtle_test/src/demo01_topic_pub.cpp
 */


#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char  *argv[])
{
    /* code */
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"my_turtle_control");
    ros::NodeHandle nh;

    // 3.创建发布者对象
    //泛型: 发布的消息类型 geometry_msgs::Twist
    //参数1: 要发布到的话题 /turtle1/cmd_vel
    //参数2: 队列中最大保存的消息数 10，超出此阀值时，先进的先销毁(时间早的先销毁)
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    
    // 4.循环发布运动控制消息
    //4-1.组织消息
    geometry_msgs::Twist msg;
    msg.linear.x = 1.0;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;

    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = 2.0;
    //4-2.设置发送频率  
    ros::Rate r(10);
    ROS_INFO("话题发布服务已启动");
    //4-3.循环发送
    while (ros::ok())
    {
        /* code */
        pub.publish(msg);
        // 休眠
        r.sleep();
        // 回头
        ros::spinOnce();
    }
    
    return 0;
}
