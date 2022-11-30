/*
 * @Author: your name
 * @Date: 2021-09-11 15:55:09
 * @LastEditTime: 2021-09-11 16:40:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ch5/src/tf04_practice/src/tf04_pub.cpp
 * 
 * 
 *     该文件实现:需要订阅 turtle1 和 turtle2 的 pose，然后广播相对 world 的坐标系信息

    注意: 订阅的两只 turtle,除了命名空间(turtle1 和 turtle2)不同外,
          其他的话题名称和实现逻辑都是一样的，
          所以我们可以将所需的命名空间通过 args 动态传入

    实现流程:
        1.包含头文件
        2.初始化 ros 节点
        3.解析传入的命名空间
        4.创建 ros 句柄
        5.创建订阅对象
        6.回调函数处理订阅的 pose 信息
            6-1.创建 TF 广播器
            6-2.将 pose 信息转换成 TransFormStamped
            6-3.发布
        7.spin
 */
#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"


std::string turtle_name;

void dopose(const turtlesim::Pose::ConstPtr& pose)
{
    // 6-1.创建 TF 广播器
    //防止每次进入都重新创建一下broadcaster，设置为静态的，加快速度。
    static tf2_ros::TransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped tfs;

    //  |----头设置
    tfs.header.frame_id = "world";
    tfs.header.stamp = ros::Time::now();

    //  |----坐标系 ID
    tfs.child_frame_id = turtle_name;

    //  |----坐标系相对信息设置
    tfs.transform.translation.x = pose->x;
    tfs.transform.translation.y = pose->y;
    tfs.transform.translation.z = 0.0; // 二维实现，pose 中没有z，z 是 0
    //  |--------- 四元数设置
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,pose->theta);
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();


    //  5-3.广播器发布数据
    broadcaster.sendTransform(tfs);
}



int main(int argc, char  *argv[])
{

    /* code */
    setlocale(LC_ALL,"");

    // 2.初始化 ROS 节点
    ros::init(argc,argv,"pub_tf");
    
    if (argc != 2)
    {
         ROS_ERROR("请传入正确的参数");
        /* code */
    }else
    {
        turtle_name = argv[1];
        // 第一个参数是第一个启动参数是/home/divenire/Divenire_ws/workingProgram/ROS/RosLearn/ch5/devel/lib/tf04_practice/tf04_pub_node
        // std::string param1 = argv[0];
        // ROS_INFO("第一个启动参数是%s",param1.c_str());
        ROS_INFO("乌龟 s%s 坐标发送启动",turtle_name.c_str());
    }

    // 3.创建 ROS 句柄
    ros::NodeHandle nh;

    // 4.创建订阅对象
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>(turtle_name+ "/pose",1000,dopose);

    // 6.回调函数处理订阅的 pose 信息
    // 6-1.创建 TF 广播器
    // 6-2.将 pose 信息转换成 TransFormStamped
    // 6-3.发布

    // 7.spin
    ros::spin();
    return 0;
}
