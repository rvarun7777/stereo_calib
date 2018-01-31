#!/bin/bash
link_dir=`rospack find fla_calibration`/calib
output_dir=$link_dir/results

right_left_fname=${link_dir}/right_left.yaml
monstar_fname=${link_dir}/monstar_intrinsics.yaml
file_name=`readlink ${monstar_fname}`
d=`echo $file_name | awk -F "." '{ print $(NF-1) }' | awk -F "-" '{printf "%04d-%02d-%02d-%02d-%02d-%02d", $(NF-5),$(NF-4),$(NF-3),$(NF-2),$(NF-1),$(NF)}'`

monstar_left_init=monstar_left_initial-${d}.yaml
monstar_left_fname=${output_dir}/$monstar_left_init
monstar_left_init_tf=${link_dir}/monstar_left_init_transform.yaml

echo "cam0:" > $monstar_left_fname
head -12 $right_left_fname | tail -n +7 >> $monstar_left_fname
cat $monstar_left_init_tf >> $monstar_left_fname
tail -n +2 $monstar_fname >> $monstar_left_fname

ln -sf results/$monstar_left_init ${link_dir}/monstar_left-initial.yaml

