#!/bin/bash

echo "enter name of robot [fla1 or ip address]"
read robot

if [ "$robot" = "" ]; then
    echo "not setting ROS_MASTER_URI"
else
    url=http://${robot}:11311
    echo "setting ROS_MASTER_URI=$url"
    export ROS_MASTER_URI=$url
fi

pfile=`rospack find fla_calibration`/config/calib_gui.perspective
rosrun rqt_gui rqt_gui --perspective-file=${pfile}
