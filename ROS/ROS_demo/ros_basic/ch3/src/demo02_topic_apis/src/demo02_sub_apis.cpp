/*
 * @Author: your name
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-08 17:36:01
 * @LastEditors: Please set LastEditors
 * @Description: 
 * 
 * /**
   * \brief 生成某个话题的订阅对象
   *
   * 该函数将根据给定的话题在ROS master 注册，并自动连接相同主题的发布方，每接收到一条消息，都会调用回调
   * 函数，并且传入该消息的共享指针，该消息不能被修改，因为可能其他订阅对象也会使用该消息。
   * 
   * 使用示例如下:

void callback(const std_msgs::Empty::ConstPtr& message)
{
}

ros::Subscriber sub = handle.subscribe("my_topic", 1, callback);

   *
* \param M [template] M 是指消息类型
* \param topic 订阅的话题
* \param queue_size 消息队列长度，超出长度时，头部的消息将被弃用
* \param fp 当订阅到一条消息时，需要执行的回调函数
* \return 调用成功时，返回一个订阅者对象，失败时，返回空对象
* 

void callback(const std_msgs::Empty::ConstPtr& message){...}
ros::NodeHandle nodeHandle;
ros::Subscriber sub = nodeHandle.subscribe("my_topic", 1, callback);
if (sub) // Enter if subscriber is valid
{
...
}

template<class M>
Subscriber subscribe(const std::string& topic, uint32_t queue_size, void(*fp)(const boost::shared_ptr<M const>&), const TransportHints& transport_hints = TransportHints())

* @FilePath: /ch3/src/demo02_topic_apis/src/demo02_sub_apis.cpp
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

