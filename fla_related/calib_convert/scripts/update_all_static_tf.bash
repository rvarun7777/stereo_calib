#!/bin/bash
calib_dir=`rospack find fla_calibration`/calib

rosrun fla_calibration update_static_tf.bash -d $calib_dir -s monstar_left.yaml -b static_tf_leftcam_monstar -c cam1 -t T_cn_cnm1 -p leftcam_to_monstar
rosrun fla_calibration update_static_tf.bash -d $calib_dir -s right_left.yaml -b static_tf_leftcam_rightcam -c cam1 -t T_cn_cnm1 -p leftcam_to_rightcam
rosrun fla_calibration update_static_tf.bash -d $calib_dir -s right_left.yaml -b static_tf_imu_leftcam -c cam0 -t T_cam_imu -p imu_to_leftcam

