from vpython import *
import os
import signal
import time
from structs import *
from math import pi, cos, sin, sqrt

class Config:
	time_multiplier = 1

	def __init__(self, width = 1800, height = 1000):
		scene.width = width
		scene.height = height
		self.camera_pos = scene.camera.pos
		scene.bind('mousedown mousemove', self.move_camera)
		scene.bind('keyup', self.terminate)
		self.slide = slider(pos=scene.caption_anchor, bind=self.update_time_multiplier,
			step=0.1, value=0.5, top=10)

	def move_camera(self, ev):
		if ev.event == 'mousedown':
			self.camera_pos = ev.pos
		elif ev.event == 'mousemove':
			scene.camera.pos -= (ev.pos - self.camera_pos) / 20
	
	def terminate(self, ev):
		if ev.key == 'esc':
			os.kill(os.getpid(), signal.SIGINT)

	def update_time_multiplier(self):
		if self.slide.value == 0.5:
			Config.time_multiplier = 1
		elif self.slide.value < 0.5:
			Config.time_multiplier = self.slide.value * 2
		else:
			Config.time_multiplier = (self.slide.value - 0.5) * 10 + 1

class Floor:
	start = None
	end = None

	def __init__(self, rooms, index = 0, rSet = None):
		self.rooms = rooms
		self.index = index
		self.rradius = 0.1
		self.rSet = rSet
		if rSet is None:
			self.rSet = set()

	def assign_color(self, s, room):
		if room.name == Floor.start.name:
			s.color = vector(1, 0, 1)
			s.radius = 2 * self.rradius
		elif room.name == Floor.end.name:
			s.color = color.blue
			s.radius = 2 * self.rradius

	def draw(self):
		if len(self.rooms) == 1:
			self.rooms[0].visu = sphere(pos=vector(self.index,0,0), radius=self.rradius)
			self.assign_color(self.rooms[0].visu, self.rooms[0])
			self.rSet.add(self.rooms[0].name)
			self.draw_paths(self.rooms[0])
		else:
			self.draw_torus()
		next_rooms = self.next_rooms()
		if len(next_rooms) > 0:
			nextFloor = Floor(next_rooms, self.index + 1, self.rSet)
			nextFloor.draw()

	def next_rooms(self):
		tmpSet = set()
		next_rooms = []
		for room in self.rooms:
			joint_rooms = room.get_other_rooms()
			for subroom in joint_rooms:
				if subroom.name not in self.rSet and subroom.name not in tmpSet:
					next_rooms.append(subroom)
					tmpSet.add(subroom.name)
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
			pos = vector(self.index, torus_radius * cos(2 * pi * i / lr),
				torus_radius * sin (2 * pi * i / lr))
			room.visu = sphere(pos=pos, radius=self.rradius)
			self.assign_color(room.visu, room)
			self.rSet.add(room.name)
			self.draw_paths(room)
			i += 1

	def draw_paths(self, room):
		other_rooms = room.get_other_rooms()
		for subroom in other_rooms:
			if subroom.name in self.rSet:
				tube = room.get_tube(subroom)
				tube.visu = curve(room.visu.pos, subroom.visu.pos, radius=0.01)

class PathsColorGenerator:

	def __init__(self, paths):
		self.paths = paths
		self.min = None
		self.max = None
		for path in self.paths:
			if self.min is None or path.cost < self.min:
				self.min = path.cost
			if self.max is None or path.cost > self.max:
				self.max = path.cost

	def color(self, cost):
		if self.max == self.min:
			return vector(0, 1, 0)
		p = (cost - self.min) / (self.max - self.min)
		red = 1 if p > 0.5 else 2 * p
		green = 1 if p < 0.5 else 2 - 2 * p
		return vector(red, green, 0)

	def draw_paths(self):
		for path in self.paths:
			color = self.color(path.cost)
			i = 0
			for room in path:
				i += 1
				if room.name == Floor.end.name:
					break
				elif room.name != Floor.start.name:
					room.visu.color = color
				tube = room.get_tube(path.rooms[i])
				if hasattr(tube, 'visu'):
					self.__modify_curve(tube.visu, color)

	def __modify_curve(self, curve, new_color):
		curve.modify(0, color = new_color, radius = curve.radius * 3)
		curve.modify(1, color = new_color, radius = curve.radius * 3)

class Ant:
	def __init__(self, path):
		self.path = path
		self.sphere = sphere(pos=path.rooms[0].visu.pos, radius = path.rooms[0].visu.radius * 0.4, color = color.black)
		self.sphere.velocity = self.path.rooms[1].visu.pos
		self.i = 0

	def update_velocity(self):
		self.i += 1
		if self.i + 1 == len(self.path.rooms):
			self.i = 0
			self.sphere.velocity = self.path.rooms[1].visu.pos
			self.sphere.pos = self.path.rooms[0].visu.pos
			return False
		self.sphere.pos = self.path.rooms[self.i].visu.pos
		self.sphere.velocity = vector(self.path.rooms[self.i + 1].visu.pos.x - self.path.rooms[self.i].visu.pos.x, \
			self.path.rooms[self.i + 1].visu.pos.y - self.path.rooms[self.i].visu.pos.y, \
			self.path.rooms[self.i + 1].visu.pos.z - self.path.rooms[self.i].visu.pos.z)
		return True

	def update_position(self, deltat):
		self.sphere.pos = self.sphere.pos + self.sphere.velocity * deltat

	@staticmethod
	def display_ants(paths):
		ants = []
		finished_ants = []
		stock = []
		for i in range(len(paths)):
			stock.append([])
			ants.append([])
			finished_ants.append([])
			for j in range(paths[i].n_ants):
				stock[i].append(Ant(paths[i]))
		deltat = 0.000005
		t = 0
		while True:
			empty_stock = True
			empty_on_trail = True
			for i in range(len(paths)):
				if len(stock[i]) != 0:
					empty_stock = False
				if len(ants[i]) != 0:
					empty_on_trail = False
				if not empty_on_trail and not empty_stock:
					break
			if empty_on_trail and empty_stock:
				stock = finished_ants
				finished_ants = []
				for i in range(len(paths)):
					finished_ants.append([])
			else:
				for i in range(len(paths)):
					if len(stock[i]) > 0:
						ants[i].append(stock[i].pop())
			while t <= 1:
				t_now = time.time()
				for i in range(len(paths)):
					for ant in ants[i]:
						ant.update_position(deltat)
				t = t + deltat
				deltat = Config.time_multiplier * (time.time() - t_now)
			for i in range(len(paths)):
				j = 0
				while j < len(ants[i]):
					ant = ants[i][j]
					if not ant.update_velocity():
						ants[i].remove(ant)
						finished_ants[i].append(ant)
					else:
						j += 1
			t = 0