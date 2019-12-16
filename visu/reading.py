import os
import signal
from structs import *

def read_lines(lines):
	n_ants = 0
	rooms = {}
	path_starts = {} #room name to ant_pioneer name
	ants_pioneer = {} #ant_pioneer name to path
	ants_follower = {} #ant name to ant_pioneer_name
	start = None
	is_start = False
	end = None
	is_end = False
	is_incomplete = False
	status = 0
	l = 0
	l_paths = 0
	if "ERROR" in lines[0]:
		print("ERROR")
		os.kill(os.getpid(), signal.SIGINT)
	for line in lines:
		l += 1
		if status == 1 and '-' in line:
			status = 2
		elif line == "":
			l_paths = l
			continue
		elif is_incomplete:
			continue
		if status == 0:
			if line[0] != '#':
				status = 1
				n_ants = int(line)
		elif status == 1:
			if line == "##start":
				is_start = True
			elif line == "##end":
				is_end = True
			elif line[0] != '#':
				data = line.split(' ')
				rooms[data[0]] = Room(data[0])
				if is_start:
					start = rooms[data[0]]
					is_start = False
				elif is_end:
					end = rooms[data[0]]
					is_end = False
		elif status == 2 and line[0] != '#':
			data = line.split('-')
			if len(data) != 2 or data[0] not in rooms.keys() \
				or data[1] not in rooms.keys() \
				or data[0] in rooms[data[1]].tubes.keys() \
				or data[1] in rooms[data[0]].tubes.keys():
				is_incomplete = True
				continue
			tube = Tube(rooms[data[0]], rooms[data[1]])
			rooms[data[0]].add_tube(tube)
			rooms[data[1]].add_tube(tube)
	for i in range(l_paths, len(lines)):
		if lines[i][0] == 'L':
			predatas = lines[i].split(' ')
			for predata in predatas:
				data = predata.split('-')
				if data[0] in ants_pioneer.keys():
					ants_pioneer[data[0]].add_room(rooms[data[1]])
				elif data[1] != start.name and data[0] not in ants_follower.keys():
					if data[1] not in path_starts.keys():
						ants_pioneer[data[0]] = Path(start)
						ants_pioneer[data[0]].add_room(rooms[data[1]])
						path_starts[data[1]] = data[0]
						ants_follower[data[0]] = data[0]
					else:
						ants_follower[data[0]] = path_starts[data[1]]
						ants_pioneer[ants_follower[data[0]]].n_ants += 1
	return n_ants, rooms, start, end, list(ants_pioneer.values())