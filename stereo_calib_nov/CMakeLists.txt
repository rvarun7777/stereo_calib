set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread")
cmake_minimum_required(VERSION 2.8.3)
project(stereo_calib_nov)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg cv_bridge sensor_msgs image_transport)
find_package(Boost REQUIRED)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

# To enable pkg-config usage
INCLUDE(FindPkgConfig)
# Find and add OpenCV to libraries
pkg_check_modules(OpenCV REQUIRED opencv)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})


# Include CATKIN packages
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(generate_calib_data src/generate_calib_data.cpp)

target_link_libraries(generate_calib_data ${catkin_LIBRARIES} 
			       ${OpenCV_LIBRARIES})
