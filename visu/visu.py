from vpython import *
from platform import system
import os
from reading import read_lines
from rendering import *
from structs import *

lines = []
while True:
	try:
		line = input()
	except EOFError:
		break
	lines.append(line)

n_ants, rooms, Floor.start, Floor.end, paths = read_lines(lines)

Config()

visu = Floor([Floor.start])
visu.draw()

cg = PathsColorGenerator(paths)
cg.draw_paths()

Ant.display_ants(paths)