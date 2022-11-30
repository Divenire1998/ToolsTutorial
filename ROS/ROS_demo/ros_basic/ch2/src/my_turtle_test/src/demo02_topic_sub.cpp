/*
 * @Author: your name
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-08 13:56:26
 * @LastEditors: Please set LastEditors
 * @Description: 
 *  //泛型: 发布的消息类型 std_msgs::String
    //参数1: 要发布到的话题 QiuYue
    //参数2: 队列中最大保存的消息数 10，超出此阀值时，先进的先销毁(时间早的先销毁)
 * @FilePath: /ch2/src/my_turtle_test/src/demo02_topic_sub.cpp
 */


#include "ros/ros.h"
#include "turtlesim/Pose.h"

void doPose(const turtlesim::Pose::ConstPtr& p){
    ROS_INFO("乌龟位姿信息:x=%.2f,y=%.2f,theta=%.2f,lv=%.2f,av=%.2f",
        p->x,p->y,p->theta,p->linear_velocity,p->angular_velocity
    );
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"sub_pose");
    // 3.创建 ROS 句柄
    ros::NodeHandle nh;
    // 4.创建订阅者对象
    //泛型: 接收的消息类型 turtlesim::Pose
    //参数1: 要发布到的话题 QiuYue
    //参数2: 队列中最大保存的消息数 10，超出此阀值时，先进的先销毁(时间早的先销毁)
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose",1000,doPose);
    // 5.回调函数处理订阅的数据
    // 6.spin
    ros::spin();
    return 0;


}
