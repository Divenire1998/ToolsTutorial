#! /bin/bash

###
 # @Author       : Yue
 # @Date         : 2022-01-25 18:21:49
 # @LastEditTime: 2022-11-30 21:04:08
 # @LastEditors: Please set LastEditors
 # @Description  : Ubuntu 18.04常用软件与环境配置
 # @FilePath     : \undefinedc:\Users\Diven\Desktop\Untitled-1.sh
 # 佛祖保佑 BUG FREE


#更换软件源
function changeSource()
{
sudo mv /etc/apt/sources.list /etc/apt/sources.list.back
sudo touch /etc/apt/sources.list
sudo chmod 777 /etc/apt/*
sudo cat>>/etc/apt/sources.list<<EOF    #多行输入
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
EOF
sudo apt-get update -y
sudo apt-get upgrade -y
menu
}

# 更换HOSTS
function changeHosts()
{
sudo cat >> /etc/hosts <<EOF
# GitHub520 Host Start
140.82.114.25                 alive.github.com
140.82.113.25                 live.github.com
185.199.108.154               github.githubassets.com
140.82.112.21                 central.github.com
185.199.108.133               desktop.githubusercontent.com
185.199.108.153               assets-cdn.github.com
185.199.108.133               camo.githubusercontent.com
185.199.108.133               github.map.fastly.net
199.232.69.194                github.global.ssl.fastly.net
140.82.114.3                  gist.github.com
185.199.111.153               github.io
140.82.114.3                  github.com
192.0.66.2                    github.blog
140.82.112.6                  api.github.com
185.199.108.133               raw.githubusercontent.com
185.199.108.133               user-images.githubusercontent.com
185.199.108.133               favicons.githubusercontent.com
185.199.108.133               avatars5.githubusercontent.com
185.199.108.133               avatars4.githubusercontent.com
185.199.108.133               avatars3.githubusercontent.com
185.199.108.133               avatars2.githubusercontent.com
185.199.108.133               avatars1.githubusercontent.com
185.199.108.133               avatars0.githubusercontent.com
185.199.108.133               avatars.githubusercontent.com
140.82.112.9                  codeload.github.com
52.216.29.20                  github-cloud.s3.amazonaws.com
52.216.113.91                 github-com.s3.amazonaws.com
52.217.41.164                 github-production-release-asset-2e65be.s3.amazonaws.com
52.217.10.132                 github-production-user-asset-6210df.s3.amazonaws.com
52.217.205.217                github-production-repository-file-5c1aeb.s3.amazonaws.com
185.199.108.153               githubstatus.com
64.71.144.202                 github.community
23.100.27.125                 github.dev
185.199.108.133               media.githubusercontent.com
# Update time: 2021-12-04T16:06:04+08:00
# Update url: https://raw.hellogithub.com/hosts
# Star me: https://github.com/521xueweihan/GitHub520
# GitHub520 Host End
EOF

sudo /etc/init.d/network-manager restart

menu
}




function softwareInstall()
{

#安装git vim ssh 远程桌面
echo "#################################################"
echo "                   安装git vim ssh               "
echo "#################################################"
sudo apt-get install -y vim

sudo apt-get install -y git
sudo apt install gitk -y


sudo apt install openssh-server -y
sudo apt-get install dconf-editor -y

gsettings set org.gnome.Vino enabled true
gsettings set org.gnome.Vino require-encryption false
gsettings set org.gnome.Vino prompt-enabled false
echo "#################################################"
echo "                   git vim ssh安装完毕           "      
echo "#################################################"



#安装nemo zsh cloc locate htop
echo "#################################################"
echo "                   安装nemo zsh cloc locate htop               "
echo "#################################################"
sudo apt install zsh -y
chsh -s /bin/zsh
wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
sudo cat>> ~/.zshrc <<EOF    #多行输入
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> my settings >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
##ROS相关路径
#source /opt/ros/melodic/setup.zsh
#source ~/catkin_ws/devel/setup.zsh
#source /home/divenire/Divenire_ws/libstore/ws_livox/devel/setup.zsh
#export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/divenire/Divenire_ws/workingProgram/ORB_SLAM/m_ORB_SLAM2_detailed_comments/Examples/ROS

# zsh不兼容的坑-zsh:no matches found
setopt no_nomatch

#ulimit -c unlimited

#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> my settings >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
EOF



sudo apt install nemo -y
# 禁用 Nautilus 绘制桌面图标 把 Nemo 设置成默认的文件管理器
gsettings set org.gnome.desktop.background show-desktop-icons true
xdg-mime default nemo.desktop inode/directory application/x-gnome-saved-search

sudo apt install cloc -y

sudo apt install mlocate -y

sudo apt install htop -y
echo "#################################################"
echo "                   nemo zsh cloc locate htop安装完毕              "
echo "#################################################"



#安装gdebi unar tree terminator ipconfig
echo "#################################################"
echo "                   安装gdebi unar tree terminator ipconfig           "
echo "#################################################"
sudo apt install gdebi -y
sudo apt install unar -y
sudo apt install tree -y
sudo apt install terminator -y
sudo apt install net-tools -y
echo "#################################################"
echo "                   gdebi unar tree terminator ipconfig安装完毕               "
echo "#################################################"


#Python环境配置
echo "#################################################"
echo "                   Python环境配置           "
echo "#################################################"
sudo ln -s /usr/bin/python3.6 /usr/bin/python
sudo apt install python3-pip -y
echo "#################################################"
echo "                   Python环境配置完毕               "
echo "#################################################"


#vscode cutecom cmake fcitx Clion Pycharm
echo "#################################################"
echo "                   安装typora vscode cutecom cmake fcitx Clion Pycharm           "
echo "#################################################"
sudo snap install typora --classic &

sudo snap install code --classic &

sudo snap install cmake --classic &

sudo apt install cutecom -y

sudo apt-get install fcitx -y

sudo snap install clion --classic &
sudo snap install pycharm-professional --classic &
echo "#################################################"
echo "                   vscode cutecom cmake fcitx Clion Pycharm安装完毕               "
echo "#################################################"



menu
}




function createDir()
{
	mkdir -p ~/0_myWorkSpace/Divenire_ws/workingProgram
	mkdir -p ~/0_myWorkSpace/Divenire_ws/libstore
	mkdir -p ~/0_myWorkSpace/Divenire_ws/demo
	mkdir -p ~/0_myWorkSpace/Datasets
	mkdir -p ~/0_myWorkSpace/Applications
}

#
function rosInstall_melodic()
{
	# 清华源
	sudo sh -c '. /etc/lsb-release && echo "deb http://mirrors.tuna.tsinghua.edu.cn/ros/ubuntu/ `lsb_release -cs` main" > /etc/apt/sources.list.d/ros-latest.list'
	# Set up your keys
	sudo apt install curl -y # if you haven't already installed curl
	curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
	# 安装Melodic
	sudo apt update
	sudo apt install ros-melodic-desktop-full -y
	# source
	echo "source /opt/ros/melodic/setup.zsh" >> ~/.zshrc
	source ~/.zshrc
	# Dependencies for building packages
	sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential -y	
	sudo apt install python-rosdep -y
	sudo rosdep init
	rosdep update
}


menu()
{
source ~/.bashrc


# 走代理服务器
git config --global http.proxy 'http://192.168.50.3:10809' 
git config --global https.proxy 'http://192.168.50.3:10809'

export http_proxy=http://192.168.50.3:10809
export https_proxy=$http_proxy


echo "################################################"
echo "#              Ubuntu1804常用软件安装           #"
echo "#              Please enter your choise:       #"
echo "#              (0) 更换源为清华源               #"
echo "#              (1) 修改HOSTS                   #"
echo "#              (2) 安装系统常用软件             #"
echo "#              (3) 安装rosInstall_melodic      #"
echo "#              (4) 新建个人常用目录             #"
echo "#              (q) Exit Menu                   #"
echo "################################################"

read input
 
case $input in
	    0)
	    changeSource;;
        1)
		changeHosts;;
	    2)
		softwareInstall;;
	    3)
		rosInstall_melodic;;
		4)
		createDir;;
	    q)
                exit;;
esac
}

#执行menu函数
menu

