import os

from reading import read_input
from visu import Floor

input = os.popen("./../resources/generator --flow-one").read()

print(input)
rtree, nbAnts, start_name, end_name = read_input(input)

visu = Floor([rtree.get_data(start_name)])
visu.draw()