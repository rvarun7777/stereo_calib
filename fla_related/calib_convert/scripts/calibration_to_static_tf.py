#!/usr/bin/python2

from tf.transformations import *
import math
import yaml
import sys
import argparse

# Calibration of monstar to cam0
# d=2017-10-26-12-53-55
# ../src/calibration_to_static_tf.py camchain-moncam-falcam-${d}.yaml static_tf_leftcam_monstar-fla1-${d}.launch leftcam_to_monstar cam1 T_cn_cnm1

# Calibration of cam0 to imu
# d=2017-10-26-12-53-55
# ../src/calibration_to_static_tf.py camchain-imucam-falcam-${d}.yaml static_tf_imu_leftcam-fla1-${d}.launch imu_to_leftcam cam0 T_cam_imu

def write_transform(ofname, T_cn_cnm1, name):
    T = inverse_matrix(T_cn_cnm1)
    yaw, pitch, roll = euler_from_matrix(T, 'rzyx')
    f = open(ofname, 'w')
    f.write('<launch>\n')
    f.write('  <arg name="parent_frame"/>\n')
    f.write('  <arg name="child_frame"/>\n')
    f.write('  <node pkg="tf2_ros" type="static_transform_publisher" name="%s"\n' % (name))
    f.write('      args="%.5f %.5f %.5f   %.6f %.6f %.6f\n' % (T[0][3], T[1][3], T[2][3], yaw, pitch, roll))
    f.write('            $(arg parent_frame) $(arg child_frame)"/>\n')
    f.write('</launch>\n')
    f.close()
    print 'written transform to file: %s' % (ofname)

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description='convert calibration to static transform.')
    parser.add_argument('ifname', metavar='calib_input_file', default=None, help='calibration input file')
    parser.add_argument('ofname', metavar='static_tf_output_file', default=None, help='static tf output file')
    parser.add_argument('pname', metavar='publisher_name', default=None, help='name of publisher')
    parser.add_argument('cname', metavar='camera_name', default=None, help='name of camera')
    parser.add_argument('transname', metavar='transform_name', default=None, help='name of transform')

    args = parser.parse_args()
    cname = args.cname
    tfname = args.transname
    with open(args.ifname, 'r') as stream:
        try:
            params = yaml.load(stream);
            if not params[cname]:
                raise ValueError('cannot find cam in calib file!')
            if not params[cname][tfname]:
                raise ValueError('cannot find %s/%s in calib file!' % (cname, tfname))
            write_transform(args.ofname, params[cname][tfname], args.pname)
        except yaml.YAMLError as exc:
            print(exc)
        except ValueError as exc:
            print(exc)
