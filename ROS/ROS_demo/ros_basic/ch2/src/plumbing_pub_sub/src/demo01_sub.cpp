/*
    消息订阅方:
        订阅话题并打印接收到的消息

    实现流程:
        1.包含头文件 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 ROS 句柄
        4.实例化 订阅者 对象
        5.处理订阅的消息(回调函数)
        6.设置循环调用回调函数

*/
#include "ros/ros.h"
// 普通类型的数据
#include "std_msgs/String.h"

// 5.处理订阅的消息(回调函数)
// 定义了一个指向常量的常量指针 message
void msg_recall(const std_msgs::String::ConstPtr& message)
{
    // 输出接受到的信息
    // 指针指向的char *数据 转换为Str
    ROS_INFO("我听见 %s",message->data.c_str());
}



int main(int argc, char  *argv[])
{
    /* 设置编码 */
    setlocale(LC_ALL, "");

    //2.初始化 ROS 节点:命名(唯一)
    // 参数1和参数2 后期为节点传值会使用
    // 参数3 是节点名称，是一个标识符，需要保证运行后，在 ROS 网络拓扑中唯一
    ros::init(argc,argv,"listener");

    // 3.创建ROS句柄 
    ros::NodeHandle nh; //该类封装了 ROS 中的一些常用功能

    // 4.创建接收者对象 
    //泛型: 发布的消息类型 std_msgs::String
    //参数1: 要发布到的话题 QiuYue
    //参数2: 队列中最大保存的消息数 10，超出此阀值时，先进的先销毁(时间早的先销毁)
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("QiuYue",10,msg_recall);

    // 6.设置循环调用回调函数
    ros::spin();//循环读取接收的数据，并调用回调函数处理


    return 0;
}
