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
f = os.path.join(parent, "resources", "big_superposition3.txt")

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

for path in bhandari.shortest_paths:
	path.draw(color.blue)
n_ants = []
for i in range(len(bhandari.shortest_paths)):
	n_ants.append(50)
ants = DisplayAnts(n_ants, bhandari.shortest_paths)