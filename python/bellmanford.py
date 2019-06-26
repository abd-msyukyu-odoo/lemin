from globals import *
from visu import Path

class BellmanFord:
	def __init__(self, rooms, s_room, e_room):
		self.rooms = rooms
		self.s_room = s_room
		self.e_room = e_room
		self.paths = BTree(None)
		self.shortest_path = None
		self.solve()

	def solve(self):
		for room in self.rooms:
			path = Path(room, None)
			path.bfBtree = BTree(room)
			self.paths.add_data(path)
		paths = [self.paths.get_data(self.s_room.name)]
		for i in range(len(self.rooms) - 1):
			new_paths = []
			for path in paths:
				room = path.room
				for jroom in room.get_joint_rooms():
					if jroom is self.s_room:
						continue
					tunnel = room.get_tunnel(jroom)
					jpath = self.paths.get_data(jroom.name)
					if (jpath.previous is None or jpath.cost > tunnel.cost + path.cost) and \
						not path.bfBtree.contains(jroom.name):
						jpath.cost = tunnel.cost + path.cost
						jpath.previous = path
						jpath.bfBtree.remove_data(jroom.name)
						jpath.bfBtree = path.bfBtree
						jpath.bfBtree.add_data(jroom)
						new_paths.append(jpath)
			paths = new_paths
			if len(paths) == 0:
				break
		path = self.paths.get_data(self.e_room.name)
		if path.previous is not None:
			reverse_path = Path(path.room, None)
			check = 0
			while path.previous is not None and check <= len(self.rooms):
				path = path.previous
				reverse_path = Path(path.room, reverse_path)
				check += 1
			if check > len(self.rooms):
				if Tools.verbose:
					print("BellmanFord infinite negative cycle error")
				return
			self.shortest_path = reverse_path
