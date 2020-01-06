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
f = os.path.join(parent, "resources", "test.txt")
o = os.path.join(parent, "resources", "result.txt")

n = 100
Tools.verbose = False
visual = False
c_test = True

for i in range(n):
	if system() == 'Darwin':
		k = open(f, 'w')
		d = os.path.join(parent, "resources", "generator")
		input_file = os.popen(d + " --flow-one").read()
		k.write(input_file)
		k.close()
	else:
		k = open(f, 'r')
		input_file = k.read()
		k.close()

	rtree, nbAnts, Tools.start_name, Tools.end_name, required = read_input(input_file)

	start = time.time()
	bhandari = Bhandari(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name), rtree, nbAnts)
	print(str(i))
	if n == 1 and visual:
		config = Config()

		visu = Floor([bhandari.s_room])
		visu.draw()

		cg = ColorGenerator(bhandari.pathCostDistribution.paths)
		for path in bhandari.pathCostDistribution.paths:
			path.draw(cg.color(path.cost))

	if not c_test:
		print("python result : " + str(bhandari.pathCostDistribution.cost) + "/" + str(required) + (" FAIL" if bhandari.pathCostDistribution.cost > required else ""))
	else:
		if system() == 'Darwin':
			prog = "../lem-in"
		else:
			prog = "..\\lem-in.exe"
		os.system(" ".join([prog, "<", f, ">", o]))
		k = open(o, 'r')
		output = k.read()
		k.close()
		output = output.splitlines()
		j = 0
		for line in output:
			j += 1
			if line == "":
				j = len(output) - j
				break
		print("result c/python/required : " + str(j) + "/" + str(bhandari.pathCostDistribution.cost) + "/" + str(required) + (" FAIL" if j > bhandari.pathCostDistribution.cost or bhandari.pathCostDistribution.cost > required else ""))

	if n == 1 and visual:
		ants = DisplayAnts(bhandari.pathCostDistribution.ants_distribution, bhandari.pathCostDistribution.paths)