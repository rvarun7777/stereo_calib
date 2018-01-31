#!/bin/bash
link_dir=`rospack find fla_calibration`/calib

rosrun fla_calibration update_camerainfo.bash -d $link_dir -s monstar_intrinsics.yaml -b monstar_intrinsics -c cam0
rosrun fla_calibration update_camerainfo.bash -d $link_dir -s right_left.yaml -b left_intrinsics -c cam0
rosrun fla_calibration update_camerainfo.bash -d $link_dir -s right_left.yaml -b right_intrinsics -c cam1

