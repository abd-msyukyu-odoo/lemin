from globals import *
from visu import Path
from enum import Enum

class Status(Enum):
	IN = 0
	OUT = 1

class SRoom(Room):
	@staticmethod
	def init(room):
		rin = SRoom(room, Status.IN)
		rout = SRoom(room, Status.OUT)
		tunnel = Tunnel(rin, rout, Direction.NATURAL, 0)
		rin.add_tunnel(tunnel)
		rout.add_tunnel(tunnel)
		return rin, rout

	def __init__(self, room, status):
		self.status = status
		self.room = room
		self.name = room.name + "#" + ("IN" if status == Status.IN else "OUT")
		self.tunnels = []


class Suurballe:
	def __init__(self, s_room, e_room, bTree_rooms):
		self.s_room = s_room
		self.e_room = e_room
		self.srTree = BTree(None)
		self.resourceTree = BTree(None)
		bTree_rooms.fill_copy(self.resourceTree)
		self.fill_srTree()
		self.fill_tunnels()
		self.start_paths = self.search_paths()

	def fill_srTree(self):
		a = []
		self.resourceTree.fill_array(a)
		while len(a) > 0:
			room = a[0]
			a.remove(room)
			if room is self.s_room:
				self.s_sroom = SRoom(room, Status.OUT)
				self.srTree.add_data(self.s_sroom)
			elif room is self.e_room:
				self.e_sroom = SRoom(room, Status.IN)
				self.srTree.add_data(self.e_sroom)
			else:
				rin, rout = SRoom.init(room)
				self.srTree.add_data(rin)
				self.srTree.add_data(rout)

	def fill_tunnels(self):
		srDone = BTree(None)
		a = []
		self.resourceTree.fill_array(a)
		while len(a) > 0:
			room = a[0]
			a.remove(room)
			rin = self.srTree.get_data(room.name + "#IN")
			if rin is not None:
				srDone.add_data(rin)
			rout = self.srTree.get_data(room.name + "#OUT")
			if rout is not None:
				srDone.add_data(rout)
			for tunnel in room.tunnels:
				other = tunnel.get_other(room)
				if tunnel.navigate(room) is not None and rout is not None:
					rother = self.srTree.get_data(other.name + "#IN")
					if rother is not None and not srDone.contains(rother.name):
						stout = Tunnel(rout, rother, Direction.NATURAL)
						rout.add_tunnel(stout)
						rother.add_tunnel(stout)
				if tunnel.navigate(other) is not None and rin is not None:
					rother = self.srTree.get_data(other.name + "#OUT")
					if rother is not None and not srDone.contains(rother.name):
						stin = Tunnel(rother, rin, Direction.NATURAL)
						rin.add_tunnel(stin)
						rother.add_tunnel(stin)

	def search_paths(self):
		return []