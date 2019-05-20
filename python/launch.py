import os

from reading import read_input

input = os.popen("./../resources/generator --flow-one").read()

print(input)
rtree, nbAnts, end_name, start_name = read_input(input)


#print(rtree)