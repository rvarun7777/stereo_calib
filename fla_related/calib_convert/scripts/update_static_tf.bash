#!/bin/bash

OPTIND=1
link_dir=-1
source_name=-1
base_name=-1
tf_pub_name=-1
tf_name=-1
cam=-1
function usage {
    echo "usage: update_static_tf.bash [-h] -d <link_dir> s <source_file_name> -b <base_file_name> -c <camera_name> -t <tf_name> -p <tf_pub_name>"
}

while getopts "h?d:s:b:c:t:p:" opt; do
    case "$opt" in
	h|\?)
	    usage
	    exit 0
	    ;;
	d)  link_dir=$OPTARG
	    ;;
	s)  source_name=$OPTARG
	    ;;
	b)  base_name=$OPTARG
	    ;;
	t)  tf_name=$OPTARG
	    ;;
	p)  tf_pub_name=$OPTARG
	    ;;
	c)  cam=$OPTARG
	    ;;
    esac
done

if [ "$link_dir" = "-1" ] || [ "$source_name" = "-1" ] || [ "$base_name" = "-1" ] || [ "$tf_name" = "-1" ] || [ "$tf_pub_name" = "-1" ] || [ "$cam" = "-1" ] ; then
    usage
    exit 0
fi

# source_full has name of the file that link is pointing to
source_full=`readlink ${link_dir}/${source_name}`

# extract the date from file_name
d=`echo $source_full | awk -F "." '{ print $(NF-1) }' | awk -F "-" '{printf "%04d-%02d-%02d-%02d-%02d-%02d", $(NF-5),$(NF-4),$(NF-3),$(NF-2),$(NF-1),$(NF)}'`

# convert kalibr to static tf
tf_file_dated=${base_name}-${d}.launch

results_prefix="results"
output_file=${link_dir}/${results_prefix}/${tf_file_dated}
rosrun fla_calibration calibration_to_static_tf.py ${link_dir}/${source_name} ${output_file} $tf_pub_name $cam $tf_name

# update link to new filename
ln -sf ${results_prefix}/$tf_file_dated ${link_dir}/${base_name}.launch

