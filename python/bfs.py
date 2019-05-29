class Bfs:
	def __init__(self, s_room, e_room):
		self.s_room = s_room
		self.e_room = e_room

class Path:
	def __init__(self, room, previous):
		self.room = room
		self.previous = previous
		if previous is None:
			self.index = 0
		else:
			self.index = previous.index + 1