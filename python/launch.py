from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *
from os.path import dirname, abspath
import os
from platform import system

parent = dirname(dirname(os.path.abspath(__file__)))
f = os.path.join(parent, "resources", "map.txt")

if system() == 'Darwin':
	d = os.path.join(parent, "resources", "generator")
	os.popen(d + " --big > " + f)

input = open(f, 'r').read()

rtree, nbAnts, Tools.start_name, Tools.end_name = read_input(input)

config = Config()

visu = Floor([rtree.get_data(Tools.start_name)])
visu.draw()

bfs = Bfs(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name))

if bfs.start_path is not None:
	bfs.start_path.draw(color.blue)
	ants = DisplayAnts([50], [bfs.start_path])
else:
	print("bfs failed")