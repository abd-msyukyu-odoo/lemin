from enum import Enum

class Tube:

	def __init__(self, room1, room2):
		self.room1 = room1
		self.room2 = room2

	def get_other(self, room):
		if self.room1 is room:
			return self.room2
		elif self.room2 is room:
			return self.room1
		else:
			return None

class Room:

	def __init__(self, name):
		self.name = name
		self.tubes = {}

	def add_tube(self, tube):
		self.tubes[tube.get_other(self).name] = tube

	def get_other_rooms(self):
		rooms = []
		for tube in self.tubes.values():
			other = tube.get_other(self)
			if other is not None:
				rooms.append(other)
		return rooms

	def get_tube(self, room):
		if room.name in self.tubes.keys():
			return self.tubes[room.name]
		return None

class Path:

	def __init__(self, room):
		self.names = set()
		self.names.add(room.name)
		self.rooms = [room]
		self.n_ants = 1
		self.cost = 0

	def add_room(self, room):
		if room.name not in self.names:
			self.names.add(room.name)
			self.rooms.append(room)
			self.cost += 1
			return True
		return False

	def __iter__(self):
		self.n = 0
		return self

	def __next__(self):
		if self.n < len(self.rooms):
			result = self.rooms[self.n]
			self.n += 1
			return result
		else:
			raise StopIteration