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
f = os.path.join(parent, "resources", "big2.txt")

if system() == 'Darwin':
	d = os.path.join(parent, "resources", "generator")
	os.popen(d + " --big > " + f)

input = open(f, 'r').read()

#print(input)
rtree, nbAnts, Tools.start_name, Tools.end_name = read_input(input)

bhandari = Bhandari(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name), rtree)
#Tools.start_name = bhandari.s_sroom.name
#Tools.end_name = bhandari.e_sroom.name

config = Config()

#visu = Floor([bhandari.s_sroom])
visu = Floor([bhandari.s_room])
visu.draw()

cg = ColorGenerator(bhandari.shortest_paths)
#for path in bhandari.shortest_spaths:
for path in bhandari.shortest_paths:
	path.draw(cg.color(path.cost))
n_ants = []
#for i in range(len(bhandari.shortest_spaths)):
for i in range(len(bhandari.shortest_paths)):
	n_ants.append(50)
#ants = DisplayAnts(n_ants, bhandari.shortest_spaths)
ants = DisplayAnts(n_ants, bhandari.shortest_paths)