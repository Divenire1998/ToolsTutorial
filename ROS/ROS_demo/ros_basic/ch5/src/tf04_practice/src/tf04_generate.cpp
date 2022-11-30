/*
 * @Author: your name
 * @Date: 2021-09-11 15:29:41
 * @LastEditTime: 2021-09-11 15:42:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ch5/src/tf04_practice/src/tf04_generate.cpp
 */
#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char *argv[])
{
    /* code */
    setlocale(LC_ALL,"");

    // 2.初始化 ROS 节点
    ros::init(argc,argv,"create_turtle");

    // 3.创建 ROS 句柄
    ros::NodeHandle nh;

    // 4.创建服务对象
    ros::ServiceClient Client = nh.serviceClient<turtlesim::Spawn>("/spawn");

    ros::service::waitForService("/spawn");


    // 5.请求服务，接收响应
    turtlesim::Spawn spawn;
    spawn.request.name = "turtle2";
    spawn.request.theta = M_PI ;
    spawn.request.x=1;
    spawn.request.y=2;



    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = Client.call(spawn);

    // 7.处理响应
    if (flag)
    {
        ROS_INFO("乌龟%s创建成功",spawn.response.name.c_str());
    }
    else
    {
        ROS_ERROR("乌龟创建失败....");
        return 1;
    }

    return 0;
}
