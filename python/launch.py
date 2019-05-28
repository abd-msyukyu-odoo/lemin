import os

from reading import read_input

input = os.popen("./../resources/generator --flow-one").read()

print(input)
rtree, nbAnts, start_name, end_name = read_input(input)

