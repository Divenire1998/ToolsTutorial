/*
 * @Author: Divenire
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-07 19:55:51
 * @LastEditors: Please set LastEditors
 * @Description: 需求: 订阅人的信息
 * @FilePath: /ch2/src/plumbing_pub_sub/src/demo02_sub.cpp
 */

#include "ros/ros.h"
#include "plumbing_pub_sub/person.h"


void person_callback(const plumbing_pub_sub::person::ConstPtr &p1)
{
    ROS_INFO("我叫%s,今年%d岁啦，身高%.2f米",p1->name.c_str(),p1->age,p1->height);
}

int main(int argc, char  *argv[])
{
    /* 设置编码 */
    setlocale(LC_ALL,"");

    // 1. 初始化
    ros::init(argc,argv,"LiJia");

    // 2.创建 ROS 句柄
    ros::NodeHandle nh;

    // 3.创建订阅者对象
    ros::Subscriber sub = nh.subscribe<plumbing_pub_sub::person>("Pig",10,person_callback);

    // 4.回调函数中处理信息

    // 5.
    ros::spin();

    return 0;
}
