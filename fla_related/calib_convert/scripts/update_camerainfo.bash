#!/bin/bash

OPTIND=1
link_dir=-1
source_name=-1
base_name=-1
cam=-1
function usage {
    echo "usage: update_camerainfo.bash [-h] -d <link_dir> s <source_file_name> -b <base_file_name> -c <camera_name>"
}

while getopts "h?d:s:b:c:" opt; do
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
	c)  cam=$OPTARG
	    ;;
    esac
done

if [ "$link_dir" = "-1" ] || [ "$source_name" = "-1" ] || [ "$base_name" = "-1" ] || [ "$cam" = "-1" ] ; then
    usage
    exit 0
fi

# source_full has name of the file that link is pointing to
source_full=`readlink ${link_dir}/${source_name}`

# extract the date from file_name
d=`echo $source_full | awk -F "." '{ print $(NF-1) }' | awk -F "-" '{printf "%04d-%02d-%02d-%02d-%02d-%02d", $(NF-5),$(NF-4),$(NF-3),$(NF-2),$(NF-1),$(NF)}'`

# convert kalibr to opencv/camerainfo file format
results_prefix="results"
camerainfo_link_name=${link_dir}/${base_name}_camerainfo.yaml
camerainfo_link_target=${results_prefix}/${base_name}_camerainfo-${d}.yaml
camerainfo_file_name=${link_dir}/${camerainfo_link_target}
rosrun fla_calibration kalibr_to_camerainfo.py --input ${link_dir}/$source_name --output $camerainfo_file_name --camera $cam

# update link to new filename
ln -sf $camerainfo_link_target $camerainfo_link_name

