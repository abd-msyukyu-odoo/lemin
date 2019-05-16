# Data requirement
class Data:
	# name : any Comparable type
	def __init__(self, name):
		self.name = name

# -> BTree comparison function
# a, b : any Comparable type
def strcmp(a, b):
	return (a > b) - (a < b)

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
	
	def __replace_direct_branch(self, old, new):
		if self.right is old:
			self.right = new
		if self.left is old:
			self.left = new

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