import os

from reading import read_input
from visu import Floor
from vpython import *

input = os.popen("./../resources/generator --flow-one").read()

print(input)
rtree, nbAnts, start_name, end_name = read_input(input)

visu = Floor([rtree.get_data(start_name)])
visu.draw()

scene.width = 800
scene.height= 800

cur_camera_pos = scene.camera.pos
def move_camera(ev):
	global cur_camera_pos
	if ev.event == "mousedown":
		cur_camera_pos = ev.pos
	elif ev.event == "mousemove":
		scene.camera.pos -= (ev.pos - cur_camera_pos ) / 10

scene.bind('mouseup mousemove mousedown', move_camera)