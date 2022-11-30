'''
Author: your name
Date: 2021-08-17 23:11:38
LastEditTime: 2021-09-08 17:40:57
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: /ch3/src/demo04_import_module/scripts/useNum.py
'''
import os
import sys
import rospy

#设置临时环境变量
#路径写死，影响了代码的可移植性
#sys. path. insert(0, /home/rosdemo/demo03 ws/src/plumbing pub sub/scripts")

# cd /home/divenire/Divenire_ws/workingProgram/ROS/RosLearn/ch3 不然路径不对找不到tools
# 优化，可以动态获取路径
path = os.path.abspath(".")

# 核心
sys.path.insert(0,path + "/src/demo04_import_module/scripts")

import tools

if __name__ == "__main__":
    # 初始化节点
    rospy.init_node("use_lib")
    rospy.loginfo("执行脚本时的参考路径:%s",path)
    rospy.loginfo("num = %d",tools.num)
