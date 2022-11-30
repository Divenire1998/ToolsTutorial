功能：创建ROS节点，并输出"Hello CPP"到终端。

`C++`实现

1. ```bash
   roscore
   ```

2. ```
   source ./devel/setup.zsh
   rosrun helloworld hello_cpp_node
   ```

>[ INFO] [1620629140.014430754]: hello world! in cpp

`Python`实现

1. ```
   roscore
   ```

2. ```
   source ./devel/setup.zsh
   rosrun helloworld hello_py.py
   ```

>[INFO] [1620629241.627853]: Hello World in python





功能：使用vscode进行开发，同时实现使用Launch文件的方式同时启动多个节点。

使用方式：

1. ```bash
   #编译
   catkin_make
   
   #添加环境变量
   source ./devel/setup.zsh
   
   #启动ros核心
   roscore
   ```

2. ```
   roslaunch hello_vscode start_node.launch
   ```

聚焦于命令行可以使用方向键控制小乌龟移动
