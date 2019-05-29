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

class Ant:
	def __init__(self, path):
		self.path = path
		self.sphere = sphere(pos=path.room.visu.pos, radius = path.room.visu.radius * 0.4, color = color.yellow)
		self.sphere.velocity = self.path.previous.room.visu.pos
		self.origin = path

	def update_velocity(self):
		self.path = self.path.previous
		if self.path.previous is None:
			self.path = self.origin
			self.sphere.velocity = self.path.previous.room.visu.pos
			self.sphere.pos = self.origin.room.visu.pos
			return False
		self.sphere.velocity = vector(self.path.previous.room.visu.pos.x - self.path.room.visu.pos.x, \
			self.path.previous.room.visu.pos.y - self.path.room.visu.pos.y, \
			self.path.previous.room.visu.pos.z - self.path.room.visu.pos.z)
		return True

	def update_position(self, deltat):
		self.sphere.pos = self.sphere.pos + self.sphere.velocity * deltat

class DisplayAnts:
	def __init__(self, n_ants, paths):
		self.n_ants = n_ants
		self.paths = paths
		self.ants = []
		self.finished_ants = []
		self.stock = []
		for i in range(len(paths)):
			for j in range(n_ants[i]):
				self.stock.append(Ant(paths[i]))
		deltat = 0.00005
		t = 0
		while True:
			if len(self.stock) == 0 and len(self.ants) == 0:
				self.stock = self.finished_ants
				self.finished_ants = []
			if len(self.stock) > 0:
				self.ants.append(self.stock.pop())
			while t <= 1:
				for ant in self.ants:
					ant.update_position(deltat)
				t = t + deltat
			i = 0
			while i < len(self.ants):
				ant = self.ants[i]
				if not ant.update_velocity():
					self.ants.remove(ant)
					self.finished_ants.append(ant)
				else:
					i += 1
			t = 0

class Bfs:
	def __init__(self, s_room, e_room):
		self.s_room = s_room
		self.e_room = e_room
		self.pTree = BTree(None, Tools.name_cmp)
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

	def draw(self):
		p = self.start_path
		if p is None:
			return
		while True:
			if p.previous is None:
				break
			else:
				tunnel = p.room.get_tunnel(p.previous.room)
				if tunnel.visu:
					self.__modify_curve(tunnel.visu, color.blue)
					p = p.previous
				else:
					break
			
	def __modify_curve(self, curve, newcolor):
		curve.modify(0, color = newcolor, radius = curve.radius * 3)
		curve.modify(1, color = newcolor, radius = curve.radius * 3)