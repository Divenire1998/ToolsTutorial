/*
 * @Author: your name
 * @Date: 2021-09-11 17:20:13
 * @LastEditTime: 2021-09-11 17:43:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * 
 * 需求：使用 ragbag向磁盘文件写出数据(话题 消息)
 * 流程
    1.导包
    2.初始化
    3.创建 rosbag对象
    4.打开文件流
    5.写数据；
    6.关闭文件流。
 * @FilePath: /ch5/src/rosbag_use/src/rosbag_write.cpp
 */
#include "ros/ros.h"
#include "rosbag/bag.h"
#include "std_msgs/String.h"

int main(int argc, char  *argv[])
{
    /* code */
       ros::init(argc,argv,"bag_write");
    ros::NodeHandle nh;
    //创建bag对象

    rosbag::Bag bag;
    //打开
    bag.open("./test.bag",rosbag::BagMode::Write);

    //写
    std_msgs::String msg;
    msg.data = "hello world";
    bag.write("/chatter",ros::Time::now(),msg);
    bag.write("/chatter",ros::Time::now(),msg);
    ros::Duration(5).sleep();
    bag.write("/chatter",ros::Time::now(),msg);
    bag.write("/chatter",ros::Time::now(),msg);
    //关闭
    bag.close();

    return 0;
}
