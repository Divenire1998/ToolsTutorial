#include "ros/ros.h"
#include "demo04_import_module/hello.h"


int main(int argc,  char *argv[])
{

    /* 设置编码 */
    setlocale(LC_ALL, "");
    /* code */
    ros::init(argc,argv,"hahah");
    hello_ns::hello my;
    my.run();
    return 0;
}
