import os
from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *
from suurballe import *

input = os.popen("./../resources/generator --big").read()

print(input)
rtree, nbAnts, Tools.start_name, Tools.end_name = read_input(input)

surb = Suurballe(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name), rtree)

config = Config()

visu = Floor([surb.srTree.get_data(Tools.start_name + "#OUT")])
visu.draw()