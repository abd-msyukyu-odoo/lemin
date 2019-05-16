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
	def __init__(self, data, f_cmp):
		self.data = data
		self.left = None
		self.right = None
		self.f_cmp = f_cmp
	
	def add_data(self, data):
		cur = self
		while True:
			cmp = self.f_cmp(data.name, cur.data.name)
			if cmp < 0:
				if cur.left is None:
					cur.left = BTree(data, self.f_cmp)
					return 1
				cur = cur.left
			elif cmp > 0:
				if cur.right is None:
					cur.right = BTree(data, self.f_cmp)
					return 1
				cur = cur.right
			else:
				return 0

	def get_data(self, name):
		cur = self
		while True:
			cmp = self.f_cmp(name, cur.data.name)
			if cmp < 0:
				if cur.left is None:
					return None
				cur = cur.left
			elif cmp > 0:
				if cur.right is None:
					return None
				cur = cur.right
			else:
				return cur.data