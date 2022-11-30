/*
    发布方实现：
        1.包含头文件
        2.初始化 ROS 节点:命名(是唯一的)
        3.创建节点句柄
        4.创建发布者对象
        5.组织被发布的数据，并编写逻辑发布数据

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
    //泛型: 发布的消息类型 std_msgs::String
    //参数1: 要发布到的话题 QiuYue
    //参数2: 队列中最大保存的消息数 10，超出此阀值时，先进的先销毁(时间早的先销毁)
    ros::Publisher pub = nh.advertise<std_msgs::String>("QiuYue",10);

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
        // 字符串拼接
        std::stringstream ss;
        ss<<"hello ---->"<<count;
        msg.data = ss.str();
        
        // 发布消息
        pub.publish(msg);
        count++;

        // 添加日志
        ROS_INFO("发布的数据是:%s",msg.data.c_str());

        //根据前面制定的发送贫频率自动休眠 休眠时间 = 1/频率；
        rate.sleep();

        //回调函数，暂无应用
        ros::spinOnce();
    }
    
    return 0;
}
