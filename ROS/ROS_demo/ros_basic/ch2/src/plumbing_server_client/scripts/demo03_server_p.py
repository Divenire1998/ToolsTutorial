#! /usr/bin/env python

import rospy

"""
    需求: 
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器.
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    服务器端实现:
        1.导包
        2.初始化 ROS 节点
        3.创建服务对象
        4.回调函数处理请求并产生响应
        5.spin 函数

"""
        # 1.导包
from plumbing_server_client.srv import AddInts,AddIntsRequest,AddIntsResponse
# from plumbing_server_client.srv import *
# 回调函数的参数是请求对象，返回值是响应对象
def doMsg(req):
    num1 = req.num1
    num2 = req.num2

    sum  = num1 +num2
    rospy.loginfo("提交的数据:num1 = %d, num2 = %d, sum = %d",req.num1, req.num2, sum)

    response = AddIntsResponse()
    response.sum = sum
    return response


if __name__ == "__main__":
    # 2.初始化 ROS 节点
    rospy.init_node("AddInts_Server_p")
    # 3.创建服务对象 话题名称、消息类型 回调函数
    server = rospy.Service("AddInts",AddInts,doMsg)
    rospy.loginfo("服务器已经启动")

    # 4.回调函数处理请求并产生响应

    # 5.spin 函数
    rospy.spin()
    pass
