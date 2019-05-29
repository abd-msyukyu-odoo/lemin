from globals import *
from vpython import *

class Path:
	def __init__(self, room, previous):
		self.name = room.name
		self.room = room
		self.previous = previous
		if previous is None:
			self.index = 0
		else:
			self.index = previous.index + 1

class Bfs:
	def __init__(self, s_room, e_room):
		self.s_room = s_room
		self.e_room = e_room
		self.pTree = BTree(None, Tools.name_cmp)
		self.end_path = self.search_path()
	
	def search_path(self):
		paths = []
		p1 = Path(self.s_room, None)
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
						if self.e_room is subroom:
							return path
			paths = n_paths
			if len(paths) == 0:
				return None

	def draw(self):
		p = self.end_path
		if p is None:
			return
		while True:
			if p.previous is None:
				break
			else:
				tunnel = p.room.get_tunnel(p.previous.room)
				if tunnel.visu:
					self.__modify_curve(tunnel.visu, color.yellow)
					p = p.previous
				else:
					break
			
	def __modify_curve(self, curve, newcolor):
		curve.modify(0, color = newcolor, radius = curve.radius * 3)
		curve.modify(1, color = newcolor, radius = curve.radius * 3)