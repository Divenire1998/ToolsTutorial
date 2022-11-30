#! /usr/bin/env python

"""
    消息发布方:
        循环发布信息:HelloWorld--->后缀数字编号

    实现流程:
        1.导包 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 发布者 对象
        4.组织被发布的数据，并编写逻辑发布数据
"""

# 1.导包 
import rospy
from std_msgs.msg import String

if __name__ == "__main__" :
    # 初始化ros节点
    rospy.init_node("talker_py")
    #实例化发布者对象
    pub = rospy.Publisher("QiuYue",String,queue_size=10)
    # 创建发布的数据对象
    message = String()
    counter = 0
    # 设置循环的发布的频率
    rate = rospy.Rate(10)

    # 睡眠1秒
    rospy.sleep(duration=1)

    while not rospy.is_shutdown():
        # 拼接消息
        message.data = "Hello" + str(counter)
        # 发布消息
        pub.publish(message)
        # 日志输出
        rospy.loginfo("发布的数据为:%s",message.data)
        counter +=1
        # 按照设定的频率休眠
        rate.sleep()
