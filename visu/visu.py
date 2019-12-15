from vpython import *
from platform import system
import os
from reading import read_lines

lines = []
while True:
	try:
		line = input()
	except EOFError:
		break
	lines.append(line)

 = read_lines(lines)

