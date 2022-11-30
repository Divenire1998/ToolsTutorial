/*
 * @Author: your name
 * @Date: 2021-09-11 16:17:26
 * @LastEditTime: 2021-09-11 16:58:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ch5/src/tf04_practice/src/tf04_sub.cpp
 */
#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"sub_tf");
    ros::NodeHandle nh;
    // 3.创建 TF 订阅节点
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    // 需要创建发布的 /turtle2/cmd_vel 的 publisher 对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",1000);
    ros::Rate r(100);
    while (ros::ok())
    {
        try
        {
            //获取两个乌龟的相对位姿ds
            //计算turtle1相对于turtle2的相对关系，偏移量和四元数都可以获得。
            //如果以turtle1为参考坐标系的话，turtle1旋转时turtle2的坐标也会变化。
            geometry_msgs::TransformStamped tfs = buffer.lookupTransform("turtle2","turtle1",ros::Time(0));
            ROS_INFO("turtle1相对于 turtle2 的坐标关系:父坐标系ID=%s",tfs.header.frame_id.c_str()); //turtle2
            ROS_INFO("turtle1相对于 turtle2 的坐标关系:子坐标系ID=%s",tfs.child_frame_id.c_str());  //turtle1
            ROS_INFO("turtle1相对于 turtle2 的坐标关系:x=%.2f,y=%.2f,z=%.2f",
                    tfs.transform.translation.x,
                    tfs.transform.translation.y,
                    tfs.transform.translation.z
                    );

            ///组织发布消息格式
            geometry_msgs::Twist twist;
            twist.linear.x = 0.5 * sqrt(pow(tfs.transform.translation.x,2) + pow(tfs.transform.translation.y,2));
            twist.angular.z = 4 * atan2(tfs.transform.translation.y,tfs.transform.translation.x);

            pub.publish(twist);
        }
        catch(const std::exception& e)
        {
            ROS_ERROR("错误提示:%s",e.what());
        }
        
        r.sleep();  
        ros::spinOnce();
    }


    return 0;
}