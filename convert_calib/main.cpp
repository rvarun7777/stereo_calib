#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <sys/time.h>

using namespace std;
using namespace cv;

#include "configuration.h"


int main(int argc, char **argv)
{
  cv::Size image_size;
  image_size.height = IMG_HEIGHT;
  image_size.width = IMG_WIDTH;
  cv::Vec3d T;
  cv::Vec4d D1,D2;
  cv::Mat R1, R2, P1, P2, Q, K1, K2, R;

  cv::FileStorage fs(stereo_parameters,cv::FileStorage::READ);
  if (!fs.isOpened()) {
      std::cerr << "Failed to open calibration parameter file." << std::endl;
  	return 0;
  }

  fs["K1"] >> K1;
  fs["K2"] >> K2;
  fs["R"] >> R;
  fs["T"] >> T;
  fs["D1"] >> D1;
  fs["D2"] >> D2;

  fs.release();

  cout << "Camera 0 Intrinsics:" << endl;
  cout << K1 << endl;

  cout << "Camera 1 Intrinsics:" << endl;
  cout << K2 << endl;

  cout << "Camera 0 Distortion Parameters:" << endl;
  cout << D1 << endl;

  cout << "Camera 1 Distortion Parameters:" << endl;
  cout << D2 << endl;

  cout << "Rotation Matrix:" << endl;
  cout << R << endl;
  
  cout << "Translation Matrix:" << endl;
  cout << T << endl;

  cv::fisheye::stereoRectify(K1, D1, K2, D2, image_size, R, T, R1, R2, 
				P1, P2, Q, CV_CALIB_ZERO_DISPARITY, image_size, 0.0, 1.0);

  cout << "R1:" << endl;
  cout << R1 << endl;

  cout << "R2:" << endl;
  cout << R2 << endl;

  cout << "P1:" << endl;
  cout << P1 << endl;
  
  cout << "P2:" << endl;
  cout << P2 << endl;

  cout << "Q" << endl;
  cout << Q << endl;

  // Create parameter file
  cv::FileStorage fs1(new_parameters, cv::FileStorage::WRITE);
  fs1 << "K1" << cv::Mat(K1);
  fs1 << "K2" << cv::Mat(K2);
  fs1 << "D1" << D1;
  fs1 << "D2" << D2;
  fs1 << "R" << cv::Mat(R);
  fs1 << "T" << T;
  fs1 << "R1" << R1;
  fs1 << "R2" << R2;
  fs1 << "P1" << P1;
  fs1 << "P2" << P2;
  fs1 << "Q" << Q;
  fs1.release();
  std::cout << "Saved converted parameter file." << std::endl << std::endl;

}
