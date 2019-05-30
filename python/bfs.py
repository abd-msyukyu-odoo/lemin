from globals import *
from visu import Path

class Bfs:
	def __init__(self, s_room, e_room):
		self.s_room = s_room
		self.e_room = e_room
		self.pTree = BTree(None)
		self.start_path = self.search_path()
	
	def search_path(self):
		paths = []
		p1 = Path(self.e_room, None)
		self.pTree.add_data(p1)
		paths.append(p1)
		while True:
			n_paths = []
			for p in paths:
				joint_rooms = p.room.get_joint_rooms()
				for subroom in joint_rooms:
					if not self.pTree.contains(subroom.name):
						path = Path(subroom, p)
						self.pTree.add_data(path)
						n_paths.append(path)
						if self.s_room is subroom:
							return path
			paths = n_paths
			if len(paths) == 0:
				return None