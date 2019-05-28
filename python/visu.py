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

	def assign_color(self, s, room):
		if room.name == Tools.start_name:
			s.color = color.green
			s.radius = 2 * self.rradius
		elif room.name == Tools.end_name:
			s.color = color.red
			s.radius = 2 * self.rradius

	def draw(self):
		if len(self.rooms) == 1:
			self.rooms[0].pos = vector(self.index,0,0)
			s = sphere(pos=self.rooms[0].pos, radius=self.rradius)
			self.assign_color(s, self.rooms[0])
			self.rTree.add_data(self.rooms[0])
			self.draw_paths(self.rooms[0])
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
		i = 0
		for room in self.rooms:
			room.pos = vector(self.index, torus_radius * cos(2 * pi * i / lr),
				torus_radius * sin (2 * pi * i / lr))
			s = sphere(pos=room.pos, radius=self.rradius)
			self.assign_color(s, room)
			self.rTree.add_data(room)
			self.draw_paths(room)
			i += 1

	def draw_paths(self, room):
		joint_rooms = room.get_joint_rooms()
		for subroom in joint_rooms:
			if self.rTree.contains(subroom.name):
				curve(room.pos, subroom.pos, radius=0.01)