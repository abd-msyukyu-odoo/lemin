from vpython import *
from math import pi
from globals import *
from math import cos
from math import sin
import os
import signal
import time

class Config:
	def __init__(self, width = 1000, height = 1000):
		scene.width = width
		scene.height= width
		self.camera_pos = scene.camera.pos
		scene.bind('mousemove mousedown', self.move_camera)
		scene.bind('keyup', self.terminate)
		self.slide = slider(pos=scene.caption_anchor, bind=self.time_multiplier,
			step=0.1, value=0.5, top=10)

	def move_camera(self, ev):
		if ev.event == "mousedown":
			self.camera_pos = ev.pos
		elif ev.event == "mousemove":
			scene.camera.pos -= (ev.pos - self.camera_pos) / 20
	
	def terminate(self, ev):
		if ev.key == 'esc':
			os.kill(os.getpid(), signal.SIGINT)

	def time_multiplier(self):
		if self.slide.value == 0.5:
			Tools.time_multiplier = 1
		elif self.slide.value < 0.5:
			Tools.time_multiplier = self.slide.value * 2
		else:
			Tools.time_multiplier = (self.slide.value - 0.5) * 10 + 1

class Floor:
	def __init__(self, rooms, index = 0, rTree = None):
		self.rooms = rooms
		self.index = index
		self.rradius = 0.1
		self.rTree = rTree
		if rTree is None:
			self.rTree = BTree(None)

	def assign_color(self, s, room):
		if room.name == Tools.start_name:
			s.color = vector(1, 0, 1)
			s.radius = 2 * self.rradius
		elif room.name == Tools.end_name:
			s.color = color.blue
			s.radius = 2 * self.rradius

	def draw(self):
		if len(self.rooms) == 1:
			self.rooms[0].visu = sphere(pos=vector(self.index,0,0), radius=self.rradius)
			#if isinstance(self.rooms[0], SRoom):
			#	self.rooms[0].visu.color = color.green if self.rooms[0].status == Status.IN else color.red	
			self.assign_color(self.rooms[0].visu, self.rooms[0])
			self.rTree.add_data(self.rooms[0])
			self.draw_paths(self.rooms[0])
		else:
			self.draw_torus()
		next_rooms = self.next_rooms()
		if len(next_rooms) > 0:
			nextFloor = Floor(next_rooms, self.index + 1, self.rTree)
			nextFloor.draw()

	def next_rooms(self):
		tmpTree = BTree(None)
		next_rooms = []
		for room in self.rooms:
			joint_rooms = room.get_other_rooms()
			for subroom in joint_rooms:
				if not self.rTree.contains(subroom.name) and not tmpTree.contains(subroom.name):
					next_rooms.append(subroom)
					tmpTree.add_data(subroom)
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
			#if isinstance(room, SRoom):
			#	room.visu.color = color.green if room.status == Status.IN else color.red
			self.assign_color(room.visu, room)
			self.rTree.add_data(room)
			self.draw_paths(room)
			i += 1

	def draw_paths(self, room):
		other_rooms = room.get_other_rooms()
		for subroom in other_rooms:
			if self.rTree.contains(subroom.name):
				tunnel = room.get_tunnel(subroom)
				tunnel.visu = curve(room.visu.pos, subroom.visu.pos, radius=0.01)

class Path:
	def __init__(self, room, previous):
		self.name = room.name
		self.room = room
		self.previous = previous
		if previous is None:
			self.cost = 0
		else:
			tunnel = self.room.get_tunnel(previous.room)
			cost = tunnel.cost if tunnel.navigate(self.room) is not None else -1 * tunnel.cost
			self.cost = previous.cost + cost

	def draw(self, color):
		p = self
		if p is None:
			return
		while True:
			if p.previous is None:
				break
			else:
				if p.room.name != Tools.start_name and p.room.name != Tools.end_name:
					p.room.visu.color = color
				tunnel = p.room.get_tunnel(p.previous.room)
				if hasattr(tunnel, 'visu'):
					self.__modify_curve(tunnel.visu, color)
					p = p.previous
				else:
					break

	def __modify_curve(self, curve, newcolor):
		curve.modify(0, color = newcolor, radius = curve.radius * 3)
		curve.modify(1, color = newcolor, radius = curve.radius * 3)

class Ant:
	def __init__(self, path, name):
		self.path = path
		self.sphere = sphere(pos=path.room.visu.pos, radius = path.room.visu.radius * 0.4, color = color.black)
		self.sphere.velocity = self.path.previous.room.visu.pos
		self.origin = path
		self.name = name

	def update_velocity(self):
		self.path = self.path.previous
		if self.path.previous is None:
			self.path = self.origin
			self.sphere.velocity = self.path.previous.room.visu.pos
			self.sphere.pos = self.origin.room.visu.pos
			return False
		self.sphere.pos = self.path.room.visu.pos
		self.sphere.velocity = vector(self.path.previous.room.visu.pos.x - self.path.room.visu.pos.x, \
			self.path.previous.room.visu.pos.y - self.path.room.visu.pos.y, \
			self.path.previous.room.visu.pos.z - self.path.room.visu.pos.z)
		return True

	def update_position(self, deltat):
		self.sphere.pos = self.sphere.pos + self.sphere.velocity * deltat

class DisplayAnts:
	def __init__(self, n_ants, paths):
		name = 0
		self.n_ants = n_ants
		self.paths = paths
		self.ants = []
		self.finished_ants = []
		self.stock = []
		for i in range(len(paths)):
			self.stock.append([])
			self.ants.append([])
			self.finished_ants.append([])
			for j in range(n_ants[i]):
				self.stock[i].append(Ant(paths[i], "L" + str(name)))
				name += 1
		deltat = 0.000005
		t = 0
		printed = False
		while True:
			empty_stock = True
			empty_on_trail = True
			for i in range(len(paths)):
				if len(self.stock[i]) != 0:
					empty_stock = False
				if len(self.ants[i]) != 0:
					empty_on_trail = False
				if not empty_on_trail and not empty_stock:
					break
			if empty_on_trail and empty_stock:
				self.stock = self.finished_ants
				self.finished_ants = []
				printed = True
				#os.kill(os.getpid(), signal.SIGINT)
				for i in range(len(paths)):
					self.finished_ants.append([])
			else:
				for i in range(len(paths)):
					if len(self.stock[i]) > 0:
						self.ants[i].append(self.stock[i].pop())
			while t <= 1:
				t_now = time.time()
				for i in range(len(paths)):
					for ant in self.ants[i]:
						ant.update_position(deltat)
				t = t + deltat
				deltat = Tools.time_multiplier * (time.time() - t_now)
			## print paths
			# if not printed:
			# 	string = ""
			# 	for i in range(len(paths)):
			# 		for ant in self.ants[i]:
			# 			string += ant.name + "-" + ant.path.previous.room.name + " "
			# 	print(string[:len(string) - 1])
			##
			for i in range(len(paths)):
				j = 0
				while j < len(self.ants[i]):
					ant = self.ants[i][j]
					if not ant.update_velocity():
						self.ants[i].remove(ant)
						self.finished_ants[i].append(ant)
					else:
						j += 1
			t = 0

class ColorGenerator:
	def __init__(self, paths):
		self.paths = paths
		self.min = None
		self.max = None
		for path in paths:
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