#!/usr/bin/env python

import yaml
import argparse
import numpy as np
import cv2
import pdb

def read_yaml(filename):
    with open(filename, 'r') as y:
        try:
            return yaml.load(y)
        except yaml.YAMLError as e:
            print(e)

def write_yaml(ydict, fname):
    with open(fname, 'w') as f:
        try:
	    f.write("%YAML:1.0\n")
	    yaml.dump(ydict, f)
        except yaml.YAMLError as y:
            print("Error:", y)

def kalibr_to_camerainfo(k):
    y = {}
    intr = k['intrinsics']
    intrinsics = np.array([[intr[0], 0, intr[2]],[0, intr[1], intr[3]],[0,0,1]])

    distortion_model = k['distortion_model']
    if (distortion_model == 'radtan'):
        distortion_model = 'plumb_bob'
    
    y['image_width']  = k['resolution'][0]
    y['image_height'] = k['resolution'][1]
    y['camera_name']  = k['rostopic']
    y['camera_matrix'] = {'rows': 3,
                          'cols': 3,
			  'dt': 'd',
                          'data': intrinsics.flatten().tolist()}
    y['distortion_model'] = distortion_model
    y['distortion_coefficients'] = {'rows': 1,
                                    'cols': 4,
				    'dt':'d',
                                    'data': k['distortion_coeffs']}
    
   
    if 'T_cn_cnm1' in k:
        T_01 = np.asarray(k['T_cn_cnm1']).reshape(4,4)
        y['rotation_01'] = {'rows':3,
			    'cols':3,
			    'dt':'d',
			    'data':T_01[0:3,0:3].flatten().tolist()}
	y['translation_01'] = {'rows':3,
			       'cols':1,
			       'dt':'d',
			       'data':T_01[0:3,3].flatten().tolist()}
    return y

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input", required=True, help="input file in Kalibr format")
    parser.add_argument("-l", "--left_output", required=True, help="output file in opencv/camerainfo format for left cam")
    parser.add_argument("-r", "--right_output", required=True, help="output file in opencv/camerainfo format for right cam")
    args = parser.parse_args()
    kalibr_dict = read_yaml(args.input)

    
    camerainfo_dict_0 = kalibr_to_camerainfo(kalibr_dict["cam0"])
    camerainfo_dict_1 = kalibr_to_camerainfo(kalibr_dict["cam1"])

    write_yaml(camerainfo_dict_0, args.left_output)
    write_yaml(camerainfo_dict_1, args.right_output)
    
if __name__=="__main__":
    main()    
