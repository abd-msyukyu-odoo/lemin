import os

from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *

input = os.popen("./../resources/generator --big").read()

print(input)
rtree, nbAnts, Tools.start_name, Tools.end_name = read_input(input)

config = Config()

visu = Floor([rtree.get_data(Tools.start_name)])
visu.draw()

bfs = Bfs(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name))
bfs.draw()

ants = DisplayAnts([5], [bfs.start_path])