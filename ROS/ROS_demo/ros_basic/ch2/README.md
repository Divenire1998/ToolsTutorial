功能：几种常见的ROS通信机制的C++与Python实现

- 话题通信
  - **demo01:字符串msg的话题发布和订阅**

1. ```bash
   #编译
   catkin_make
   
   #添加环境变量
   source ./devel/setup.zsh
   
   #启动ros核心
   roscore
   ```

2. ```bash
   ## demo01_pub
   
   #C++
   rosrun plumbing_pub_sub demo01_pub
   
   #Python 
   rosrun plumbing_pub_sub demo01_pub_py.py
   ```

   ```bash
   ## demo01_sub
   #C++
   rosrun plumbing_pub_sub demo01_sub
   
   #Python 
   rosrun plumbing_pub_sub demo01_sub_py.py
   ```

   - **demo02:自定义的Msg的话题发布和订阅**

1. ```bash
   #编译
   catkin_make
   
   #添加环境变量
   source ./devel/setup.zsh
   
   #启动ros核心
   roscore
   ```

2. ```bash
   ## demo02_pub
   
   #C++
   rosrun plumbing_pub_sub demo02_pub
   
   #Python 
   rosrun plumbing_pub_sub demo02_pub_py.py

3. ```bash
   ## demo02_sub
   #C++
   rosrun plumbing_pub_sub demo02_sub
   
   #Python 
   rosrun plumbing_pub_sub demo02_sub_py.py
   ```

- 服务器通信
  - **demo03:字符串msg的话题发布和订阅** 

1. ```bash
   # demo03_server
   roscore
   source ./devel/setup.zsh
   
   #C++
   rosrun plumbing_server_client demo03_server_node 
   
   #Python
   rosrun plumbing_server_client demo03_server_p.py
   ```
   
   ```bash
   # demo03_server 测试
   source ./devel/setup.zsh
   #执行下面的语句 服务器端会输出接收到的数据
   rosservice call /AddInts "num1: 0 num2: 2"
   ```
   
   ```bash
   # demo03_client
   source ./devel/setup.zsh
   #启动服务后 执行以下语句服务器返回199
   #C++
   rosrun plumbing_server_client demo03_client_node 99 100
   #Python
   rosrun plumbing_server_client demo03_client_p.py 99 12121
   ```
   
   需要先启动服务:`rosrun 包名 服务`
   
   然后再调用客户端 :`rosrun 包名 客户端 参数1 参数2`

- 参数服务器

  - **demo01:参数设置**

  1. ```bash
     # demo01_param_set
     roscore
     source ./devel/setup.zsh
     
     #C++
     rosrun plumbing_param_server param_set_node 
     #Python
     rosrun plumbing_param_server demo01_param_set_p.py
     
     #测试
     rosparam get /p_bool
     ```

  - **demo02:参数读取**

  1. ```bash
     # demo02_param_get
     roscore
     source ./devel/setup.zsh
     #C++
     rosrun plumbing_param_server param_get_node 
     #Python
     rosrun plumbing_param_server demo02_param_get_p.py
     ```

  - **demo03参数删除**

  1. ```bash
     # demo03_param_del
     roscore
     source ./devel/setup.zsh
     #C++
     rosrun plumbing_param_server param_del_node 
     #Python
     rosrun plumbing_param_server demo03_param_del_p.py
     ```

- 小乌龟通信示例

  - 首先启动小乌龟节点

  ```bash
  roscore
  source ./devel/setup.zsh
  rosrun turtlesim turtlesim_node 
  ```

  - **demo01_topic_pub  发布控制信息给小乌龟**

  ```bash
  # demo01_topic_pub
  #C++
  rosrun my_turtle_test demo01_topic_pub
  #Python
  rosrun my_turtle_test demo01_topic_pub_p.py
  
  #小乌龟做圆周运动
  ```

  - **demo02_topic_sub  获取小乌龟的状态信息**

  ```bash
  # demo02_topic_sub  
  #C++
  rosrun my_turtle_test demo02_topic_sub  
  #Python
  rosrun my_turtle_test demo02_topic_sub_p.py
  
  #输出小乌龟的位姿和速度
  ```

  - **demo03_server  通过服务请求的方式 告诉小乌龟节点生成一个新的小乌龟**

  ```bash
  # demo03_server
  #C++
  rosrun my_turtle_test demo03_server
  #Python
  rosrun my_turtle_test demo03_server_p.py
  
  #生成新的小乌龟
  ```

  - **demo04_param_set 设置小乌龟节点的param参数(背景颜色)**

  ```bash
  # demo04_param_set
  #C++
  rosrun my_turtle_test demo04_param_set
  #Python
  rosrun my_turtle_test demo04_param_set_p.py
  
  #重启小乌龟节点 背景颜色改变
  ```

  

