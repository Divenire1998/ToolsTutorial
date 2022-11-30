#! /usr/bin/env python

import rospy
import sys
"""
    需求: 
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    客户端实现:
        1.导包
        2.初始化 ROS 节点
        3.创建请求对象
        4.发送请求
        5.接收并处理响应

    优化:
        加入数据的动态获取，等待服务端启动，防止服务端没启动时 客户端抛出异常


"""

    # 1.导包
from plumbing_server_client.srv import AddInts,AddIntsRequest,AddIntsResponse
# from plumbing_server_client.srv import *

if __name__ == "__main__":

    #优化实现
    if len(sys.argv) != 3:
        rospy.logerr("请正确提交参数")
        sys.exit(1)

    # 2.初始化 ROS 节点
    rospy.init_node("demo03_client_p")
    # 3.创建请求对象
    client = rospy.ServiceProxy("AddInts",AddInts)
    rospy.loginfo("客户端已经创建")
    # 请求前，等待服务已经就绪
    # 方式1:
    # rospy.wait_for_service("AddInts")
    # 方式2
    client.wait_for_service()

    # 4.发送请求,接收并处理响应
    # 方式1
    # resp = client(3,4)
    # 方式2
    # resp = client(AddIntsRequest(1,5))
    # 方式3
    req = AddIntsRequest()
    # req.num1 = 100
    # req.num2 = 200 

    #优化
    req.num1 = int(sys.argv[1])
    req.num2 = int(sys.argv[2]) 

    # 发送数据并接受相应
    resp = client.call(req)

    rospy.loginfo("响应结果:%d",resp.sum)

    # 5.接收并处理响应
    pass