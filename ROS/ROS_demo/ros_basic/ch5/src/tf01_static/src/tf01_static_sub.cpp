/*
 * @Author: your name
 * @Date: 2021-09-10 14:43:24
 * @LastEditTime: 2021-09-10 15:14:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ch5/src/tf01_static/src/tf01_static_sub.cpp
 */
/*
    订阅坐标系信息，生成一个相对于子级坐标系的坐标点数据，转换成父级坐标系中的坐标点

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 TF 订阅节点
        4.生成一个坐标点(相对于子级坐标系)
        5.转换坐标点(相对于父级坐标系)
        6.spin()
*/
// 1.包含头文件
#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h" //注意: 调用 transform 必须包含该头文件

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 2.初始化 ROS 节点
    ros::init(argc, argv, "tf_sub");
    ros::NodeHandle nh;
    // 3.创建 TF 订阅节点
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    // 休眠一秒钟，防止没有订阅到发布方的订阅信息
    ros::Rate r(1);

    //"base_link" passed to lookupTransform argument target_frame does not exist.
    // r.sleep();
    while (ros::ok())
    {
        // 4.生成一个坐标点(相对于子级坐标系)
        geometry_msgs::PointStamped point_laser;
        point_laser.header.frame_id = "laser";
        point_laser.header.stamp = ros::Time::now();
        point_laser.point.x = 1;
        point_laser.point.y = 2;
        point_laser.point.z = 7.3;

        // 5.转换坐标点(相对于父级坐标系)
        //新建一个坐标点，用于接收转换结果
        /*
            调用了 buffer的转换函数 trans form参数1:被转换的坐标点参数2;目标坐标系返回值：输出的坐标点
            Ps1:调用时必须包含头文件"tf2_geometry_msgs/tf2_geometry_msgs.h"
            Ps2:运行时存在的问题：施出一个异常 base link不存在
                原因：订阅数据是一个耗时操作，可能再调用 trans form转换函数时，坐标系的
                相对关系还没有订阅到，因此出现异常解决：
                    方案1:在调用转换函数前，执行休眠
                    方案2:进行异常处理
        */
        //--------------使用 try 语句或休眠，否则可能由于缓存接收延迟而导致坐标转换失败------------------------
        try
        {
            geometry_msgs::PointStamped point_base;
            point_base = buffer.transform(point_laser, "base_link");
            ROS_INFO("转换后的数据:(%.2f,%.2f,%.2f),参考的坐标系是:%s",
                     point_base.point.x, point_base.point.y, point_base.point.z, point_base.header.frame_id.c_str());
        }
        catch (const std::exception &e)
        {
            ROS_INFO("程序异常.....:%s", e.what());
        }

        r.sleep();
        ros::spinOnce();
    }

    return 0;
}