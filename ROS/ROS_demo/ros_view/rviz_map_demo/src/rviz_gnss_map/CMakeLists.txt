cmake_minimum_required(VERSION 3.0.2)
project(rviz_gnss_map)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)




## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  tf2
  tf2_geometry_msgs
  tf2_ros
)


# Add Eigen3 
find_package(Eigen3  REQUIRED)
# Add GeographicLib.
add_subdirectory(third_party/GeographicLib)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rviz_gnss_map
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs tf2 tf2_geometry_msgs tf2_ros
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  third_party/GeographicLib/include
)


add_executable(rviz_gnss_map_loco
	src/main.cpp
)

target_link_libraries(rviz_gnss_map_loco
  ${catkin_LIBRARIES}
	${EIGEN3_LIBS}
  libGeographiccc
)