from globals import *
from visu import Path
from bfs import Bfs
from bellmanford import BellmanFord

class Bhandari:
	def __init__(self, s_room, e_room, bTree_rooms, n_ants = 0):
		self.s_sroom = None
		self.e_sroom = None
		self.n_ants = n_ants
		self.s_room = s_room
		self.e_room = e_room
		self.srTree = BTree(None)
		self.resourceTree = bTree_rooms
		self.fill_srTree(s_room, e_room)
		self.bfs = None
		self.shortest_spaths = []
		self.shortest_paths = []
		if self.s_sroom is not None and self.e_sroom is not None:
			self.fill_tunnels()
			self.bfs = Bfs(self.s_sroom, self.e_sroom)
			self.shortest_spaths = self.solve()
			self.shortest_paths = self.reduce_spaths()

	def fill_srTree(self, s_room, e_room):
		a = []
		self.resourceTree.fill_array(a)
		while len(a) > 0:
			room = a[0]
			a.remove(room)
			if room is s_room:
				self.s_sroom = SRoom(room, Status.OUT)
				self.srTree.add_data(self.s_sroom)
			elif room is e_room:
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

	def solve(self):
		if self.bfs.shortest_path is None:
			print("No path found")
			return []
		pathStorages = []
		origin = self.reverse_path(self.bfs.shortest_path, pathStorages, self.bfs.shortest_path)
		print("found the first path")
		pathStorages = [PathStorage(origin)]
		bf = BellmanFord(self.bfs.discovered_rooms, self.s_sroom, self.e_sroom)
		while bf.shortest_path is not None:
			print("found a path")
			origin = self.reverse_path(bf.shortest_path, pathStorages, bf.shortest_path)
			pathStorages.append(PathStorage(origin))
			bf = BellmanFord(self.bfs.discovered_rooms, self.s_sroom, self.e_sroom)
		paths = []
		for pathStorage in pathStorages:
			paths.append(pathStorage.path)
		return paths

	def reverse_path(self, path, pathStorages, origin):
		while path.previous is not None:
			tunnel = path.room.get_tunnel(path.previous.room)
			if tunnel.cost < 0:
				tunnel.reverse()
				tunnel.cost = -1 * tunnel.cost
				origin = self.handle_overlap(path, pathStorages, origin)
				return origin
			tunnel.reverse()
			tunnel.cost = -1 * tunnel.cost
			path = path.previous
		return origin

	def handle_overlap(self, path, pathStorages, origin):
		target = path.previous.name
		overlap = None
		storage = None
		for pathStorage in pathStorages:
			overlap = pathStorage.pTree.get_data(target)
			if overlap is not None:
				storage = pathStorage
				break
		if overlap is None:
			print("overlap detection failure")
			return None
		if overlap.previous.name == path.name:
			print("matching overlap")
			untracked = path.previous.previous
			tracked = overlap.previous.previous
			path.previous = tracked # premiere partie du merge des chemins, ce chemin est correct, on peut creer son pathStorage a partir de maintenant
			pathStorages.append(PathStorage(origin))
			uturn = storage.pTree.get_data(untracked.name) #check des uturn pour la deuxieme partie du merge
			while uturn is not None:
				print("working on uturn")
				tunnel = overlap.room.get_tunnel(uturn.room)
				tunnel.reverse()
				tunnel.cost = -1 * tunnel.cost
				overlap = uturn
				untracked = untracked.previous
				uturn = storage.pTree.get_data(untracked.name)
			overlap.previous = untracked # cet overlap est gere, il faut continuer a inverse la suite du chemin et gerer les overlaps suivants
			pathStorages.remove(storage) # ce pathStorage n'est plus d'actualite, et on ne peut pas le recreer tant qu'on n'a pas gere les overlaps qui suivent
			return self.reverse_path(overlap, pathStorages, storage.path)
		else:
			print("fail to match overlap")
			return None

	def reduce_spaths(self):
		paths = []
		print("reducing paths")
		for shortest_spath in self.shortest_spaths:
			spath = shortest_spath
			origin = Path(spath.room.room, None)
			path = origin
			cost = 0
			while spath is not None:
				spath = spath.previous
				path.previous = Path(spath.room.room, None)
				spath = spath.previous
				path = path.previous
				cost += 1
			origin.cost = cost
			print("path cost : " + str(cost))
			paths.append(origin)
		return paths