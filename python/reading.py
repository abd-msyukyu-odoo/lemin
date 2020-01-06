from globals import Tools
from globals import *


def read_input(input_file):
	rtree = BTree(None)
	input_file = input_file.splitlines()
	rooms = False
	nbAnts = int(input_file.pop(0))
	start = 0
	end = 0
	required = 0
	for i in input_file:
		if i == "##start":
			start += 1
		elif i == "##end":
			end += 1
		elif i[0] != '#':
			j = i.split(' ')
			if not rooms and len(j) == 3:
				rtree.add_data(Room(j[0], int(j[1]), int(j[2])))
				if start == 1:
					start_name = j[0]
					start += 1
				elif end == 1:
					end_name = j[0]
					end += 1
			elif (not rooms and len(j) < 3 or rooms) and len(j) == 1:
				rooms = True
				j = j[0].split('-')
				if len(j) == 2:
					a = rtree.get_data(j[0])
					b = rtree.get_data(j[1])
					if a and b:
						tunnel = Tunnel(a, b)
						a.add_tunnel(tunnel)
						b.add_tunnel(tunnel)
					else:
						print("Error")
						break
				else:
					print("Error")
					break
			else:
				print(rooms)
				print("Error")
				break
		# else a retirer
		else:
			j = i.split(': ')
			required = int(j[1])
	return rtree, nbAnts, start_name, end_name, required