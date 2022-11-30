#! /usr/bin/env python

#现象：当不配置 Cmakelists.txt执行 python文件抛出异常：
#/usr/bin/env:" python":没有那个文件或目录
#原因：当前 noetic使用的是 python3
#解决：
#   1.直接声明解释器为 python3（不建议）
#   2.通过软链接将 python链接到 python3（建议）： sudo Ln-s/usr/bin/ python3

"""
    Python 版本的 HelloVScode，
    实现:
    1.导包
    2.初始化 ROS 节点
    3.日志输出 HelloWorld

"""

import rospy # 1.导包

if __name__ == "__main__":

    rospy.init_node("Hello_Vscode_p2")  # 2.初始化 ROS 节点
    rospy.loginfo("Hello VScode，而且我没有在CMakelists里做配置")  #3.日志输出 HelloWorld
