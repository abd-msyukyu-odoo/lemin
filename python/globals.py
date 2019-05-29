class Tools: 
	@staticmethod
	def name_cmp(a, b):
		return (a > b) - (a < b)
	start_name = None
	end_name = None

class Room:

	def __init__(self, name, x=None, y=None):
		self.x = x
		self.y = y
		self.name = name
		self.tunnels = []

	def add_tunnel(self, tunnel):
		self.tunnels.append(tunnel)

	def get_joint_rooms(self):
		rooms = []
		for tunnel in self.tunnels:
			rooms.append(tunnel.get_other(self))
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

class Tunnel:
	def __init__(self, room1, room2, direction = 0):
		self.direction = direction
		self.room1 = room1
		self.room2 = room2
		self.cost = 1

	def get_other(self, room):
		return self.room1 if room is self.room2 else self.room2

class BTree:
	# data : Data : Any type with "name" attribute : string -> by ext. : integer
	# f_cmp : comparison function
	# left, right : BTree
	def __init__(self, data, f_cmp, up = None):
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
		if self.left is old:
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
			elem.up.__remove_direct_branch(elem, None)
		elif elem.right is None or elem.left is None:
			elem.up.__replace_direct_branch(elem, \
				elem.right if elem.left is None else elem.left)
		else:
			min = elem.right.__get_min_elem()
			min.up.__replace_direct_branch(min, min.right)
			elem.data = min.data
		return rm_data

	def __str__(self):
		s = ""
		if (self.left is not None):
			s += self.left.__str__()
		if self.data:
			s += " " + self.data.name + " "
		if (self.right is not None):
			s += self.right.__str__()
		return s
