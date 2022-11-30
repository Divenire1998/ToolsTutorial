#! /usr/bin/env python

import rospy
from plumbing_pub_sub.msg import person

def personcallback(p):
    rospy.loginfo("接收到的人的信息:%s, %d, %.2f",p.name, p.age, p.height)

if __name__ == "__main__":
    # 1.节点初始化
    rospy.init_node("listener_person_py")
    # 2.实例化发布的数据对象
    sub = rospy.Subscriber("Person",person,callback=personcallback)
    # 4.循环
    rospy.spin()