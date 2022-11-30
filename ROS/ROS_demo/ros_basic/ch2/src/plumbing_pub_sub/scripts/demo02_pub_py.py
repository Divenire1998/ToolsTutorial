#! /usr/bin/env python

import rospy
from plumbing_pub_sub.msg import person

if __name__ == "__main__":
    # 1.节点初始化
    rospy.init_node("talker_person_py")
    # 2.实例化发布的数据对象
    pub = rospy.Publisher("Person",person,queue_size=100)
    # 3.组织消息
    p = person()
    p.name = "葫芦瓦"
    p.age = 18
    p.height = 0.75

    # 4.编写消息发布逻辑
    counter = 0
    rate  = rospy.Rate(10)
    rospy.sleep(1)

    while not rospy.is_shutdown():
        pub.publish(p)
        # 频率
        rate.sleep()
        rospy.loginfo("姓名:%s, 年龄:%d, 身高:%.2f",p.name, p.age, p.height)