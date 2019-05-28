from vpython import *
from math import pi

class Floor:
    def __init__(self, rooms, index):
        self.rooms = rooms
        self.index = index
        self.rradius = 0.1

    def draw(self):
        next_rooms = self.next_rooms()
        if len(next_rooms) > 0: 
            nextFloor = Floor(next_rooms, self.index + 1)
            nextFloor.draw()
        if len(rooms) == 1:
            sphere(pos=vector(self.index,0,0), radius=self.rradius)
        else:
            draw_torus()

    def next_rooms(self):
        next_rooms = []
        for room in rooms:
            next_rooms += room.get_joint_rooms()
        return next_rooms

    def draw_torus(self):
        ring(pos=vector(self.index,0,0),
            axis=vector(1,0,0),
            radius=4 * self.rradius / pi,
            thickness=self.rradius)