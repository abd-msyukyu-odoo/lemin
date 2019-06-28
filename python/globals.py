from enum import Enum

class Tools: 
	start_name = None
	end_name = None
	time_multiplier = 1
	verbose = False

	@staticmethod
	def name_cmp(a, b):
		return (a > b) - (a < b)

	@staticmethod
	def path_cmp(path):
		return path.cost

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
	direction_switcher = {
			Direction.REVERSE: Direction.NATURAL,
			Direction.NATURAL: Direction.REVERSE
		}
	
	def __init__(self, room1, room2, direction = Direction.BOTH, cost = 1):
		self.direction = direction
		self.room1 = room1
		self.room2 = room2
		self.cost = cost

	def reverse(self):
		self.direction = Tunnel.direction_switcher.get(self.direction, Direction.BOTH)

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
		if data is None:
			self.rank = 0
		else:
			self.rank = 1
		if up is not None:
			self.rebalance()
	
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

	def get_other(self, btree):
		if self.left is btree:
			return self.right
		elif self.right is btree:
			return self.left
		else:
			return None

	def double_rotate(self):
		rotate(self)
		rotate(self)
		self.rank += 1
		return

	def rotate(self):
		if (self.up.left == self):
			tmp = self.right
		else:
			tmp = self.left
		
		self.up -> self.up.up
		self.tmp_side -> self.up
		self.up.up -> self
		self.up.anti_tmp_side -> tmp
		self.up.up.?side -> self
		self.tmp.up -> self.up
		self.up.rank -= 1
		return

	def rebalance(self):
		cur = self
		while cur.up is not None:
			parent = self.up
			if parent.rank <= cur.rank:
				parent.rank += 1
				if parent.up is None:
					return
				sibling = parent.up.get_other(parent)
				sibrank = 0 if sibling is None else sibling.rank
				if parent.up.rank == parent.rank and parent.up.rank - sibrank == 2:
					subsibling = parent.get_other(cur)
					subsibrank = 0 if subsibling is None else subsibling.rank
					if parent.rank - subsibrank == 2:
						cur.double_rotate()
					else:
						parent.rotate()
					return
			else:
				return
			cur = parent
		return

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
				elem.up.__remove_direct_branch(elem)
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

	def remove_data_wavl(self, name):
		return None

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

class PathStorage:
	def __init__(self, path):
		self.path = path
		self.pTree = BTree(None)
		cur_path = self.path
		while cur_path is not None:
			self.pTree.add_data(cur_path)
			cur_path = cur_path.previous

class PathCostDistribution:
	def __init__(self, paths, n_ants):
		self.paths = paths
		self.n_ants = n_ants
		self.cost = None
		if n_ants == 0:
			self.cost = 0
		else:
			self.cost = None
		self.ants_distribution = None
		self.evaluate()

	def is_valid(self):
		return self.cost is not None

	def evaluate(self):
		if len(self.paths) == 0 or self.n_ants == 0:
			return
		self.ants_distribution = []
		for i in range(len(self.paths)):
			self.ants_distribution.append(0)
		self.cost = 0
		dephased = 0
		for i in range(1, len(self.paths)):
			d = self.paths[i - 1].cost - self.paths[i].cost
			for j in range(i, len(self.paths)):
				self.ants_distribution[j] += d
				dephased += d
			self.cost += d
		if dephased + len(self.paths) - 1 >= self.n_ants:
			if Tools.verbose:
				print("    solution rejected")
			self.cost = None
			self.ants_distribution = None
			return
		remain = (self.n_ants - dephased) % len(self.paths)
		for i in range(1, remain + 1):
			self.ants_distribution[-i] += 1
		if remain != 0:
			self.cost += 1
		common = int((self.n_ants - dephased - remain) / len(self.paths))
		for i in range(len(self.paths)):
			self.ants_distribution[i] += common
		self.cost += common + self.paths[-1].cost - 1
		self.check_sum()

	def check_sum(self):
		n = 0
		for i in range(len(self.paths)):
			n += self.ants_distribution[i]
		if n != self.n_ants:
			if Tools.verbose:
				print("inconsistent number of ants")
		else:
			if Tools.verbose:
				print("    cost : " + str(self.cost))