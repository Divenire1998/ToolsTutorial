/*
 * @Author: Divenire
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-08 15:51:26
 * @LastEditors: Please set LastEditors
 * @Description: 
 * 作用：创建发布者对象
    模板：被发布的消息的类型
    参数
        1.话题名称
        2.队列长度
        3.latch（可选）如果设置为true,会保存发布方的最后一条消息，并且新的订阅对象连接到发布方时，发布方会将这条消息发送给订阅者
    使用：
        Latch设置为true的作用？
        以静态地图发布为例，方案1：可以使用固定频率发送地图数据，但是效率低；
        方案2:可以将地图发布对象的atch设置为true,并且发布方只发送一次数据，每当订阅者连接时
        将地图数据发送给订阅者（只发送一次），这样提高了数据的发送效率。
*/

#include "ros/ros.h"
// 普通类型的数据
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char  *argv[])
{
    /* 设置编码 */
    setlocale(LC_ALL, "");
    
    //2.初始化 ROS 节点:命名(唯一)
    // 参数1和参数2 后期为节点传值会使用
    // 参数3 是节点名称，是一个标识符，需要保证运行后，在 ROS 网络拓扑中唯一
    ros::init(argc,argv,"talker");


    // 3.创建ROS句柄 
    ros::NodeHandle nh; //该类封装了 ROS 中的一些常用功能


    // 4.创建发布者对象 
    /*
    泛型: 发布的消息类型 std_msgs::String
    参数1: 要发布到的话题 QiuYue
    参数2: 队列中最大保存的消息数 10，超出此阀值时，先进的先销毁(时间早的先销毁)
    参数3: latch（可选）如果设置为true,会保存发布方的最后一条消息，并且新的订阅对象连接到发布方时，发布方会将这条消息发送给订阅者
    */
    ros::Publisher pub = nh.advertise<std_msgs::String>("QiuYue",10,true);

    /* 休眠3秒钟，让publisher 在 roscore 注册完毕后在发消息 */
    ros::Duration(3.0).sleep();

    // 5.组织被发布的数据，并编写逻辑发布数据
    std_msgs::String   msg;

    //创建频率对象 要求以10Hz频率发布数据
    ros::Rate rate(10);

    //设置计数器编号
    int count = 0;
    
    // 如果节点还活着
    while(ros::ok())
    {
        count++;
        // 字符串拼接
        std::stringstream ss;
        ss<<"hello ---->"<<count;
        msg.data = ss.str();

        if(count < 10)
        {
            // 发布消息
            pub.publish(msg);

            // 添加日志
            ROS_INFO("发布的数据是:%s",msg.data.c_str());
        }

        //根据前面制定的发送贫频率自动休眠 休眠时间 = 1/频率；
        rate.sleep();

        //回调函数，暂无应用
        ros::spinOnce();
    }
    
    return 0;
}