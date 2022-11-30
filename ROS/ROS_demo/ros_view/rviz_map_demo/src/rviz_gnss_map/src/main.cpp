// STL
#include <iostream>

// ROS头
#include <ros/ros.h>

// 坐标变换相关
#include <geometry_msgs/PoseStamped.h>
#include "tf2_ros/static_transform_broadcaster.h"
#include <tf/transform_broadcaster.h>
#include "tf2/LinearMath/Quaternion.h"

// 消息相关
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/NavSatStatus.h>

// 导航轨迹
#include <nav_msgs/Path.h>

// Eigen
#include <Eigen/Core>

// utils
#include "rviz_gnss_map/utils.h"

using namespace std;

// GNSS 地图参考坐标发布器
static ros::Publisher RefGnssMapPub;

// 位姿 TF2 发布器
static ros::Publisher PosePub;

// 轨迹发布器
static ros::Publisher PathPub;

// 初始的经纬高坐标(第一帧GNSS信号)
Eigen::Vector3d init_lla_;

// 上一个时刻的位姿
static geometry_msgs::PoseStamped _prev_pose;

//  存储轨迹
nav_msgs::Path nav_path_;

// 偏航
double yaw;

//---------------------------------------------------------------------------------------------

// GNSS信号处理回调函数
static void GnssCallBack(const sensor_msgs::NavSatFixConstPtr &msg)
{

    // 第一帧gnss信号
    static bool first_gnss = true;
    if (first_gnss)
    {
        init_lla_ = Eigen::Vector3d(msg->latitude,
                                    msg->longitude,
                                    msg->altitude);

        // 打印出收到的GNSS信号
        ROS_WARN("ori gnss: %.8f,%.8f,%.8f", init_lla_[0], init_lla_[1], init_lla_[2]);

        // 发布地图的参考GPS坐标
        // 只需要发布一次，在Rviz中订阅这个话题！ref_map_lla
        RefGnssMapPub.publish(msg);

        first_gnss = false;
    }

    // * 计算gnss在ENU系下的pose
    Eigen::Vector3d enu;
    // 把经纬高转换为ENU坐标系下
    // init_lla_为初始ENU坐标系
    ImuGpsLocalization::ConvertLLAToENU(init_lla_, Eigen::Vector3d(msg->latitude, msg->longitude, msg->altitude), &enu);
    // ROS_WARN("enu: %.8f,%.8f,%.8f", enu[0], enu[1], enu[2]);

    // * 计算gnss在ENU系下的pose
    geometry_msgs::PoseStamped pose;

    // 头
    pose.header = msg->header;
    pose.header.frame_id = "map";

    // pose的位置直接给gnss的位置
    pose.pose.position.x = enu[0];
    pose.pose.position.y = enu[1];
    pose.pose.position.z = enu[2];

    double distance = sqrt(pow(pose.pose.position.y - _prev_pose.pose.position.y, 2) +
                           pow(pose.pose.position.x - _prev_pose.pose.position.x, 2));


    // 动了10cm 就药计算一下偏航角
    if (distance > 0.1)
    {
        yaw = atan2(pose.pose.position.y - _prev_pose.pose.position.y, pose.pose.position.x - _prev_pose.pose.position.x);
        pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        _prev_pose = pose;
    }

    // 发布位姿
    PosePub.publish(pose);


    // * 计算gnss在ENU系下的path
    nav_path_.header = pose.header;
    nav_path_.poses.push_back(pose);
    PathPub.publish(nav_path_);


    // * 发布TF变换
    static tf2_ros::StaticTransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped ts;

    //----设置头信息
    ts.header = msg->header;

    //坐标 ID 参考坐标系
    ts.header.frame_id = "map";
    //子坐标系的 id
    ts.child_frame_id = "gnss";

    //----设置子级相对于父级的偏移量
    ts.transform.translation.x = enu[0];
    ts.transform.translation.y = enu[1];
    ts.transform.translation.z = enu[2];
    //----设置四元数:将 欧拉角数据转换成四元数
    tf2::Quaternion qtn;


    qtn.setRPY(0, 0, yaw); //单位是弧度
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();

    // 广播器发布坐标系信息
    broadcaster.sendTransform(ts);

}

int main(int argc, char **argv)
{
    /* 设置编码 */
    setlocale(LC_ALL, "");

    // 初始化ROS节点
    ros::init(argc, argv, "gnss_map");

    // ROS句柄
    ros::NodeHandle nh;

    // 初始化发布对象
    RefGnssMapPub = nh.advertise<sensor_msgs::NavSatFix>("ref_map_lla", 10, true);

    // 位姿发布对象
    PosePub = nh.advertise<geometry_msgs::PoseStamped>("/gnss_pose", 10);

    // 轨迹发布对象
    PathPub = nh.advertise<nav_msgs::Path>("/gnsss_path", 10);


    // 订阅ROSbag的gnss话题
    ros::Subscriber GnssSignalSub = nh.subscribe<sensor_msgs::NavSatFix>("/gnss_fix", 10, GnssCallBack);

    ros::spin();

    return 0;
}