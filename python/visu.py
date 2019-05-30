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
			scene.camera.pos -= (ev.pos - self.camera_pos ) / 10
	
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
			s.color = color.green
			s.radius = 2 * self.rradius
		elif room.name == Tools.end_name:
			s.color = color.red
			s.radius = 2 * self.rradius

	def draw(self):
		if len(self.rooms) == 1:
			self.rooms[0].visu = sphere(pos=vector(self.index,0,0), radius=self.rradius)
			if isinstance(self.rooms[0], SRoom):
				self.rooms[0].visu.color = color.green if self.rooms[0].status == Status.IN else color.red	
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
			if isinstance(room, SRoom):
				room.visu.color = color.green if room.status == Status.IN else color.red
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
			self.index = 0
		else:
			self.index = previous.index + 1

	def draw(self, color):
		p = self
		if p is None:
			return
		while True:
			if p.previous is None:
				break
			else:
				tunnel = p.room.get_tunnel(p.previous.room)
				if tunnel.visu:
					self.__modify_curve(tunnel.visu, color)
					p = p.previous
				else:
					break

	def __modify_curve(self, curve, newcolor):
		curve.modify(0, color = newcolor, radius = curve.radius * 3)
		curve.modify(1, color = newcolor, radius = curve.radius * 3)

class Ant:
	def __init__(self, path):
		self.path = path
		self.sphere = sphere(pos=path.room.visu.pos, radius = path.room.visu.radius * 0.4, color = color.yellow)
		self.sphere.velocity = self.path.previous.room.visu.pos
		self.origin = path

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
		self.n_ants = n_ants
		self.paths = paths
		self.ants = []
		self.finished_ants = []
		self.stock = []
		for i in range(len(paths)):
			for j in range(n_ants[i]):
				self.stock.append(Ant(paths[i]))
		deltat = 0.000005
		t = 0
		while True:
			if len(self.stock) == 0 and len(self.ants) == 0:
				self.stock = self.finished_ants
				self.finished_ants = []
			if len(self.stock) > 0:
				self.ants.append(self.stock.pop())
			while t <= 1:
				t_now = time.time()
				for ant in self.ants:
					ant.update_position(deltat)
				t = t + deltat
				deltat = Tools.time_multiplier * (time.time() - t_now)
			i = 0
			while i < len(self.ants):
				ant = self.ants[i]
				if not ant.update_velocity():
					self.ants.remove(ant)
					self.finished_ants.append(ant)
				else:
					i += 1
			t = 0