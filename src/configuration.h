#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <stdio.h>

#define IMG_WIDTH	1280
#define IMG_HEIGHT	1024
#define FLIP_FLAG	0

#define START_OFFSET	100
#define END_OFFSET	100
#define FRAME_SKIP	20

#define BOARD_WIDTH	9
#define BOARD_HEIGHT	6
#define SQUARE_SIZE	0.0225
#define VERBOSITY_FLAG	1

std::string paramFile = "/home/nvidia/stereo_calib/data/calibration_file.yml";

#endif
