from enum import Enum

class Tools: 
	@staticmethod
	def name_cmp(a, b):
		return (a > b) - (a < b)
	start_name = None
	end_name = None
	time_multiplier = 1

class Room:

	def __init__(self, name, x=None, y=None):
		self.x = x
		self.y = y
		self.name = name
		self.tunnels = []

	def add_tunnel(self, tunnel):
		self.tunnels.append(tunnel)

	def remove_tunnel(self, tunnel):
		other = tunnel.get_other(self)
		self.tunnels.remove(tunnel)
		other.tunnels.remove(tunnel)

	def get_joint_rooms(self):
		rooms = []
		for tunnel in self.tunnels:
			other = tunnel.navigate(self)
			if other is not None:
				rooms.append(other)
		return rooms

	def get_other_rooms(self):
		rooms = []
		for tunnel in self.tunnels:
			other = tunnel.get_other(self)
			if other is not None:
				rooms.append(other)
		return rooms

	def get_tunnel(self, room):
		for tunnel in self.tunnels:
			other = tunnel.get_other(self)
			if (other is room):
				return tunnel
		return None

	def cmp(self, other):
		if self.name > other.name:
			return 1
		elif self.name < other.name:
			return -1
		return 0

class Status(Enum):
	IN = 0
	OUT = 1

class SRoom(Room):
	@staticmethod
	def init(room):
		rin = SRoom(room, Status.IN)
		rout = SRoom(room, Status.OUT)
		tunnel = Tunnel(rin, rout, Direction.NATURAL, 0)
		rin.add_tunnel(tunnel)
		rout.add_tunnel(tunnel)
		return rin, rout

	def __init__(self, room, status):
		self.status = status
		self.room = room
		self.name = room.name + "#" + ("IN" if status == Status.IN else "OUT")
		self.tunnels = []

class Direction(Enum):
	NATURAL = 1
	REVERSE = -1
	BOTH = 0

class Tunnel:
	def __init__(self, room1, room2, direction = Direction.BOTH, cost = 1):
		self.direction = direction
		self.room1 = room1
		self.room2 = room2
		self.cost = cost

	def get_other(self, room):
		if self.room1 is room:
			return self.room2
		elif self.room2 is room:
			return self.room1
		else:
			return None

	def navigate(self, room):
		if self.room1 is room and (self.direction == Direction.BOTH or \
			self.direction == Direction.NATURAL):
			return self.room2
		elif self.room2 is room and (self.direction == Direction.BOTH or \
			self.direction == Direction.REVERSE):
			return self.room1
		else:
			return None

class BTree:
	# data : Data : Any type with "name" attribute : string -> by ext. : integer
	# f_cmp : comparison function
	# left, right : BTree
	def __init__(self, data, f_cmp = Tools.name_cmp, up = None):
		self.data = data
		self.left = None
		self.right = None
		self.f_cmp = f_cmp
		self.up = up
	
	def add_data(self, data):
		if self.data is None:
			self.data = data
			return 1
		cur = self
		while True:
			cmpr = self.f_cmp(data.name, cur.data.name)
			if cmpr < 0:
				if cur.left is None:
					cur.left = BTree(data, self.f_cmp, cur)
					return 1
				cur = cur.left
			elif cmpr > 0:
				if cur.right is None:
					cur.right = BTree(data, self.f_cmp, cur)
					return 1
				cur = cur.right
			else:
				return 0

	def __get_elem(self, name):
		if self.data is None:
			return None
		cur = self
		while True:
			cmpr = self.f_cmp(name, cur.data.name)
			if cmpr < 0:
				if cur.left is None:
					return None
				cur = cur.left
			elif cmpr > 0:
				if cur.right is None:
					return None
				cur = cur.right
			else:
				return cur
	
	def get_data(self, name):
		elem = self.__get_elem(name)
		return None if elem is None else elem.data

	def contains(self, name):
		return False if self.get_data(name) is None else True
	
	def __replace_direct_branch(self, old, new):
		if self.right is old:
			self.right = new
			if new is not None:
				new.up = old.up
		elif self.left is old:
			self.left = new
			if new is not None:
				new.up = old.up

	def __remove_direct_branch(self, elem):
		self.__replace_direct_branch(elem, None)

	def __get_min_elem(self):
		cur = self
		while cur.left is not None:
			cur = cur.left
		return cur

	def __get_max_elem(self):
		cur = self
		while cur.right is not None:
			cur = cur.right
		return cur

	def remove_data(self, name):
		elem = self.__get_elem(name)
		if elem is None:
			return None
		rm_data = elem.data
		if elem.right is None and elem.left is None:
			if elem.up is None:
				elem.data = None
			else:
				elem.up.__remove_direct_branch(elem, None)
		elif elem.right is None:
			if elem.up is None:
				elem.data = elem.left.data
				elem.right = elem.left.right
				elem.left = elem.left.left
				if elem.right is not None:
					elem.right.up = elem
				if elem.left is not None:
					elem.left.up = elem
			else:
				elem.up.__replace_direct_branch(elem, elem.left)
		elif elem.left is None:
			if elem.up is None:
				elem.data = elem.right.data
				elem.left = elem.right.left
				elem.right = elem.right.right
				if elem.right is not None:
					elem.right.up = elem
				if elem.left is not None:
					elem.left.up = elem
			else:
				elem.up.__replace_direct_branch(elem, elem.right)
		else:
			min_e = elem.right.__get_min_elem()
			min_e.up.__replace_direct_branch(min_e, min_e.right)
			elem.data = min_e.data
		return rm_data

	def fill_copy(self, bTree):
		bTree.add_data(self.data)
		if self.left is not None:
			self.left.fill_copy(bTree)
		if self.right is not None:
			self.right.fill_copy(bTree)

	def fill_array(self, arr):
		arr.append(self.data)
		if self.left is not None:
			self.left.fill_array(arr)
		if self.right is not None:
			self.right.fill_array(arr)

	def __str__(self):
		s = ""
		if (self.left is not None):
			s += self.left.__str__()
		if self.data:
			s += " " + self.data.name + " "
		if (self.right is not None):
			s += self.right.__str__()
		return s
