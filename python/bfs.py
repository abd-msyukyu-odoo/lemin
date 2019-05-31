from globals import *
from visu import Path

class Bfs:
	def __init__(self, s_room, e_room):
		self.s_room = s_room
		self.e_room = e_room
		self.pTree = BTree(None)
		self.start_path = None
		self.discovered_rooms = []
		self.search_path()
	
	def search_path(self):
		paths = []
		p1 = Path(self.s_room, None)
		self.pTree.add_data(p1)
		paths.append(p1)
		self.discovered_rooms.append(self.s_room)
		while True:
			n_paths = []
			for p in paths:
				joint_rooms = p.room.get_joint_rooms()
				for subroom in joint_rooms:
					if not self.pTree.contains(subroom.name):
						path = Path(subroom, p)
						self.pTree.add_data(path)
						n_paths.append(path)
						self.discovered_rooms.append(subroom)
						if self.e_room is subroom and self.start_path is None:
							reverse_path = Path(path.room, None)
							while path.previous is not None:
								path = path.previous
								reverse_path = Path(path.room, reverse_path)
							self.start_path = reverse_path
			paths = n_paths
			if len(paths) == 0:
				return None