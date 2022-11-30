/*
 * @Author: Divenire
 * @Date: 2021-08-17 23:11:38
 * @LastEditTime: 2021-09-08 15:17:00
 * @LastEditors: Please set LastEditors
 * @Description: 
 * // 1.argc与argv的使用
//     如果技照ROS中的特定格式传入实，那么ROS可以加以使用，比如用来设置全局参数、给节点重命名
// 2.options的使用
//     节点名称需要保证唯一，会导致一个问题：同一个节点不能重复启动
//     结果：ROS中当有重名的节点启动时，之前的节点会被关闭
//     需求：特定场景下，需要一个节点多次启动且能正常运行，怎么办？
//     解决：设重启动项ros::init_options::AnonymousName
//      当创建R0S节点时，会在用户自定义的节点名称后随机数，从而避免里名问题
 * @FilePath: /ch3/src/demo01_init_apis/src/demo01_init_apis.cpp
 */
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>


int main(int argc, char *argv[])
{

    setlocale(LC_ALL,"");


    /** @brief ROS初始化函数。
     *
     * 该函数可以解析并使用节点启动时传入的参数(通过参数设置节点名称、命名空间...) 
     *
     * 该函数有多个重载版本，如果使用NodeHandle建议调用该版本。 
     *
     * \param argc 参数个数
     * \param argv 参数列表
     * \param name 节点名称，需要保证其唯一性，不允许包含命名空间
     * \param options 节点启动选项，被封装进了ros::init_options
     *
     */
    // 每次节点启动后，节点后缀加一个随机数，这样就可以重复启动一个节点了
    ros::init(argc,argv,"erGouZi",ros::init_options::AnonymousName);

    ros::NodeHandle nh;


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
