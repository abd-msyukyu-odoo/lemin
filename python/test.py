from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *
from bhandari import *
from os.path import dirname, abspath
import os
from platform import system

parent = dirname(dirname(os.path.abspath(__file__)))
f = os.path.join(parent, "resources", "map.txt")

if system() == 'Darwin':
	d = os.path.join(parent, "resources", "generator")
	os.popen(d + " --big > " + f)

input = open(f, 'r').read()

#print(input)
rtree, nbAnts, Tools.start_name, Tools.end_name = read_input(input)

bhandari = Bhandari(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name), rtree)

config = Config()

visu = Floor([bhandari.srTree.get_data(Tools.start_name + "#OUT")])
visu.draw()

if bhandari.bfs.start_path is not None and hasattr(bhandari.bfs.start_path.room, 'visu'):
	bhandari.bfs.start_path.draw(color.blue)
	bhandari.bellmanford.start_path.draw(color.purple)
	ants = DisplayAnts([50, 50], [bhandari.bfs.start_path, bhandari.bellmanford.start_path])