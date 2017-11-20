// ROS LIBRARIES
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <stereo_msgs/DisparityImage.h>

#include <message_filters/time_synchronizer.h>
#include <message_filters/subscriber.h>

// OPENCV LIBRARIES
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// OTHER INCLUDED LIBRARIES
#include <stdio.h>
#include <iostream> 
#include <fstream> 
#include <ctime> 
#include <cstdio> 
#include <stdlib.h> 
#include <sys/time.h> 
#include <numeric> 
#include <vector>
#include <typeinfo> 
#include <stdint.h> 
#include <linux/limits.h> 
#include <dirent.h> 
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <sys/time.h>

int global_frame_ctr = 0;
std::string save_directory = "/home/nvidia/nov15_calib/";

void syncStereoCallBack(const sensor_msgs::ImageConstPtr& cam1_msg, 
                        const sensor_msgs::ImageConstPtr& cam2_msg)
{

  cv_bridge::CvImagePtr cv_ptr_1;
  cv_bridge::CvImagePtr cv_ptr_2;

  cv_ptr_1 = cv_bridge::toCvCopy(cam1_msg, sensor_msgs::image_encodings::MONO8);
  cv_ptr_2 = cv_bridge::toCvCopy(cam2_msg, sensor_msgs::image_encodings::MONO8);

  cv::Mat img_1,img_2;
  img_1 = cv_ptr_1->image;
  img_2 = cv_ptr_2->image;

  boost::format l_fname = boost::format("%sleft/left_img%05d.png") % save_directory % global_frame_ctr;
  boost::format r_fname = boost::format("%sright/right_img%05d.png") % save_directory % global_frame_ctr;
  global_frame_ctr++;
  // Camera 0 - Img_1 - RIGHT CAMERA
  // Camera 2 - Img_2 - LEFT CAMERA
  cv::imwrite(r_fname.str(),img_1);
  cv::imwrite(l_fname.str(),img_2);

}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;

  cv::startWindowThread();

  image_transport::ImageTransport it(nh);

  message_filters::Subscriber<sensor_msgs::Image> image_sub_1(nh, "/image_0",1);
  message_filters::Subscriber<sensor_msgs::Image> image_sub_2(nh, "/image_2",1);
  message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> sync(image_sub_1, image_sub_2, 10);
  sync.registerCallback(boost::bind(&syncStereoCallBack, _1, _2));

  ros::spin();
}
