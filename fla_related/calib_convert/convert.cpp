#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace cv;
using namespace std;



int main(void)
{
std::string cam0_param_url;
std::string cam1_param_url;

cam0_param_url = "/home/shreyas/code_repositories/stereo_calib/fla_related/calib_convert/scripts/cam0.yaml";
cam1_param_url = "/home/shreyas/code_repositories/stereo_calib/fla_related/calib_convert/scripts/cam1.yaml";

cv::FileStorage fs1(cam0_param_url,cv::FileStorage::READ);
if (!fs1.isOpened())
{
  std::cerr << "Failed to open calibration parameter file." << std::endl;
  return 0;
}

cv::FileStorage fs2(cam1_param_url,cv::FileStorage::READ);
if (!fs2.isOpened())
{
  std::cerr << "Failed to open calibration parameter file." << std::endl;
  return 0;
}


cv::Mat R1,R2,P1,P2,Q,K1,K2,R;
cv::Mat D1,D2,T;
cv::Size img_size;

fs1["camera_matrix"] >> K1;
fs2["camera_matrix"] >> K2;
fs1["distortion_coefficients"] >> D1;
fs2["distortion_coefficients"] >> D2;
fs2["rotation_01"] >> R;
fs2["translation_01"] >> T;
fs1["image_height"] >> img_size.height;
fs1["image_width"] >> img_size.width;

cv::fisheye::stereoRectify(K1,D1,K2,D2,img_size,R,T,R1,R2,P1,P2,Q,CV_CALIB_ZERO_DISPARITY,img_size,0.0,1.0);

cout << "Calculated R1" << endl << R1 << endl;
cout << "Calculated R2" << endl << R2 << endl;
cout << "Calculated P1" << endl << P1 << endl;
cout << "Calculated P2" << endl << P2 << endl;
cout << "Calculated Q" << endl << Q << endl;


cout << "End of Rectification Parameter Generation!\n" << endl;
return 0;
}
