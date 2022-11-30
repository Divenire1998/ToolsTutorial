## demo04

- demo01_init_apis
  - 实现一个节点的重复启动，启动两次相同节点后，使用`rosnode list`进行查看
- demo2_topic_apis
  - latch选项的使用，当话题发布结束时，如果有订阅者链接上，则会将发布者会将最后一条消息发布给订阅者。
- demo3_time_apis
  - 计算程序的运行时间
  - 获取当前时刻和指定时刻
  - 创建时间对象进行休眠
  - 定时器相关操作(ROS的定时器不是很准确)
- demo04_import_module
  - 自定义C++和Python库文件的导入与使用
  - 解决`catkin_make`找不到Pyhton包的问题

