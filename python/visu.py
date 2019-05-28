from vpython import *
from math import pi
from globals import *
from math import cos
from math import sin

class Floor:
	def __init__(self, rooms, index = 0, rTree = None):
		self.rooms = rooms
		self.index = index
		self.rradius = 0.1
		self.rTree = rTree
		if rTree is None:
			self.rTree = BTree(None, Tools.name_cmp)
		for room in rooms:
			self.rTree.add_data(room)

	def draw(self):
		if len(self.rooms) == 1:
			sphere(pos=vector(self.index,0,0), radius=self.rradius)
		else:
			self.draw_torus()
		next_rooms = self.next_rooms()
		if len(next_rooms) > 0: 
			nextFloor = Floor(next_rooms, self.index + 1, self.rTree)
			nextFloor.draw()

	def next_rooms(self):
		next_rooms = []
		for room in self.rooms:
			joint_rooms = room.get_joint_rooms()
			for subroom in joint_rooms:
				if not self.rTree.contains(subroom.name):
					next_rooms.append(subroom)
		return next_rooms

	def draw_torus(self):
		torus_radius = len(self.rooms) * 4 * self.rradius / pi
		""" ring(pos=vector(self.index,0,0),
			axis=vector(1,0,0),
			radius=torus_radius,
			thickness=self.rradius * 0.1) """
		lr = len(self.rooms)
		for i in range(lr):
			sphere(pos=vector(self.index, torus_radius * cos(2 * pi * i / lr),
				torus_radius * sin (2 * pi * i / lr)), radius=self.rradius)