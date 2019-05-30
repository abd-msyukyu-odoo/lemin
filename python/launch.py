import os

from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *
from os.path import dirname, abspath

#input = os.popen("./../resources/generator --big").read()
d = dirname(dirname(os.path.abspath(__file__)))
d = os.path.join(d, "resources", "map.txt")
input = open(d, 'r').read()

print(input)
rtree, nbAnts, Tools.start_name, Tools.end_name = read_input(input)

config = Config()

visu = Floor([rtree.get_data(Tools.start_name)])
visu.draw()

bfs = Bfs(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name))
bfs.start_path.draw(color.blue)

ants = DisplayAnts([50], [bfs.start_path])