from globals import *
from visu import Path

class Suurballe:
	def __init__(self, s_room, e_room):
		self.s_room = s_room
		self.e_room = e_room
		self.pTree = BTree(None, Tools.name_cmp)
		self.start_paths = self.search_paths()

	def search_paths(self):
		return []