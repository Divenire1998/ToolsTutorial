/*
    注意命名空间的使用。

*/
#include "ros/ros.h"


int main(int argc, char *argv[])
{
    ros::init(argc,argv,"set_myTurtle_param");


// 使用nh命名空间
    // ros::NodeHandle nh("turtlesim");
    // nh.setParam("background_r",0);
    // nh.setParam("background_g",0);
    // nh.setParam("background_b",0);

// 不使用nh命名空间
    ros::NodeHandle nh;
    nh.setParam("/turtlesim/background_r",0);
    nh.setParam("/turtlesim/background_g",0);
    nh.setParam("/turtlesim/background_b",0);

// 使用param::set
    // ros::param::set("/turtlesim/background_r",0);
    // ros::param::set("/turtlesim/background_g",0);
    // ros::param::set("/turtlesim/background_b",0);




    return 0;
}
