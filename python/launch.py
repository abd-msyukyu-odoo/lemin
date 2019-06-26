from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *
from bhandari import *
from os.path import dirname, abspath
import os
from platform import system
import time

parent = dirname(dirname(os.path.abspath(__file__)))
f = os.path.join(parent, "resources", "test_big_superposition.txt")

n = 1
Tools.verbose = True
visual = False

for i in range(n):
	if system() == 'Darwin':
		k = open(f, 'w')
		d = os.path.join(parent, "resources", "generator")
		k.write(os.popen(d + " --big-superposition").read())

	input = open(f, 'r').read()

	#print(input)
	rtree, nbAnts, Tools.start_name, Tools.end_name, required = read_input(input)

	start = time.time()
	bhandari = Bhandari(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name), rtree, nbAnts)
	print(str(i) + " :---" + str(time.time() - start) + "---")

	if n == 1 and visual:
		config = Config()

		visu = Floor([bhandari.s_room])
		visu.draw()

		cg = ColorGenerator(bhandari.pathCostDistribution.paths)
		for path in bhandari.pathCostDistribution.paths:
			path.draw(cg.color(path.cost))

	print("result : " + str(bhandari.pathCostDistribution.cost) + "/" + str(required) + (" FAIL" if bhandari.pathCostDistribution.cost > required else ""))

	if n == 1 and visual:
		ants = DisplayAnts(bhandari.pathCostDistribution.ants_distribution, bhandari.pathCostDistribution.paths)