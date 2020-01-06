from reading import read_input
from visu import *
from vpython import *
from globals import *
from bfs import *
from bhandari import *
from os.path import dirname, abspath
import os
from platform import system
import numpy as np
import sys
import time

parent = dirname(dirname(os.path.abspath(__file__)))
f = os.path.join(parent, "resources", "test.txt")
o = os.path.join(parent, "resources", "result.txt")

n = 500
Tools.verbose = False
visual = False
c_test = True
python_test = False

if system() == 'Darwin':
	make = "make"
else:
	make = "mingw32-make.exe"

os.system(" ".join([make, "-C", parent, "re"]))
fails = 0
results = []
requireds = []
for i in range(n):
	if system() == 'Darwin':
		k = open(f, 'w')
		d = os.path.join(parent, "resources", "generator")
		input_file = os.popen(d + " " + sys.argv[1]).read()
		k.write(input_file)
		k.close()
	else:
		k = open(f, 'r')
		input_file = k.read()
		k.close()
	sleep(0.25)
	rtree, nbAnts, Tools.start_name, Tools.end_name, required = read_input(input_file)

	if python_test:
		bhandari = Bhandari(rtree.get_data(Tools.start_name), rtree.get_data(Tools.end_name), rtree, nbAnts)
	#print(str(i))
	if n == 1 and visual and python_test:
		config = Config()

		visu = Floor([bhandari.s_room])
		visu.draw()

		cg = ColorGenerator(bhandari.pathCostDistribution.paths)
		for path in bhandari.pathCostDistribution.paths:
			path.draw(cg.color(path.cost))

	if not c_test and python_test:
		print("python result : " + str(bhandari.pathCostDistribution.cost) + "/" + str(required) + (" FAIL" if bhandari.pathCostDistribution.cost > required else ""))
	else:
		if system() == 'Darwin':
			prog = "../lem-in"
		else:
			prog = "..\\lem-in.exe"
		os.system(" ".join([prog, "<", f, ">", o]))
		sleep(0.25)
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
		if python_test:
			if j > bhandari.pathCostDistribution.cost or bhandari.pathCostDistribution.cost > required:
				fails += 1
				requireds.append(required)
				results.append(j)
			print("result c/python/required : " + str(j) + "/" + str(bhandari.pathCostDistribution.cost) + "/" + str(required) + (" FAIL" if j > bhandari.pathCostDistribution.cost or bhandari.pathCostDistribution.cost > required else ""))
		else:
			if j > required:
				fails += 1
				requireds.append(required)
				results.append(j)

	if n == 1 and visual and python_test:
		ants = DisplayAnts(bhandari.pathCostDistribution.ants_distribution, bhandari.pathCostDistribution.paths)

print(str(fails) + " fails sur " + str(n) + " essais")
print("results: " + str(results))
print("requireds: " + str(requireds))
results = np.array(results)
requireds = np.array(requireds)
b = results - requireds
print(sys.argv[1] + " DONE")
