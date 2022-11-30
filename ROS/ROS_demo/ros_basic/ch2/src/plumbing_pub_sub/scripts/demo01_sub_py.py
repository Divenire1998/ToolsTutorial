#! usr/bin/env python

"""
消息订阅方:
        订阅话题并打印接收到的消息

    实现流程:
        1.导包 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 订阅者 对象
        4.处理订阅的消息(回调函数)
        5.设置循环调用回调函数

"""

import rospy
from std_msgs.msg import String

# 处理订阅的消息
def masg_callback(msg):
    rospy.loginfo("I heared :%s",msg.data)

if __name__ == "__main__" :
    # 初始化 ROS 节点:命名(唯一)
    rospy.init_node("listener_py")
    # 实例化 订阅者 对象
    sub = rospy.Subscriber("QiuYue",String,callback=masg_callback,queue_size=10)
    # 设置循环回调函数
    rospy.spin()

    


