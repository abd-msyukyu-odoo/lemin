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

btree = BTree(None)

for i in range(100):
	btree.add_data(Room(str(i)))
	#print(btree)

print(btree)