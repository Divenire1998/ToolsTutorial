#include "ros/ros.h"
#include "demo04_import_module/hello.h"

namespace hello_ns{
    void hello::run()
    {
        ROS_INFO("自定义头文件的使用....");
    }

}
