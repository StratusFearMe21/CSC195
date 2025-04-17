import os
import subprocess
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('fluid_exe')
parser.add_argument("c_file")
parser.add_argument("header_file")
parser.add_argument("fluid_file")

args = parser.parse_args()
fluid_file = os.path.abspath(args.fluid_file)
h_file = os.path.abspath(args.header_file)
pwd = os.path.dirname(args.c_file)
os.chdir(pwd)

c_file = os.path.basename(args.c_file)
h_file = os.path.relpath(h_file)

subprocess.run([args.fluid_exe, '-c', '-o', c_file, '-h', h_file, fluid_file])
