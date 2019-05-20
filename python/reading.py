from globals import *


def read_input(input):
    rtree = BTree(None, Room.cmp)
    input = input.splitlines()
    rooms = False
    nbAnts = int(input.pop(0))
    start = 0
    end = 0
    for i in input:
        if i == "##start":
            start += 1
        if i == "##end":
            end += 1
        if i[0] != '#':
            j = i.split(' ')
            if not rooms and len(j) == 3:
                rtree.add_data(Room(j[0], int(j[1]), int(j[2])))
                if start == 1:
                    start_name = j[0]
                    start += 1
                elif end == 1:
                    end_name = j[0]
                    end += 1
            elif not rooms and len(j) < 3:
                rooms = True
            elif rooms and len(j) == 1:
                j = j[0].split('-')
                if len(j) == 2:
                    a = rtree.get_data(j[0])
                    b = rtree.get_data(j[1])
                    if a and b:
                        a.add_tunnel(b)
                        b.add_tunnel(a)
                    else:
                        print("Error")
                        break
                else:
                    print("Error")
                    break
            else:
                print(rooms)
                print("Error")
                break
    return rtree, nbAnts, start_name, end_name