file = open("map", "r")

rooms = {}

connection = False

class Room:
	connectedTo = []
	isStart = False
	isEnd = False
	def __init__(self, x, y, name):
		self.x = x
		self.y = y
		self.name = name
	def setConnectedTo(roomToConnect):
		connectedTo = roomToConnect

def isConnection(line):
	return line == "##connection\n"

for line in file:
	if connection is False:
		connection = isConnection(line)
		if connection is True:
			continue
		splitted = line.split()
		if len(splitted) == 4:
			print(splitted[0])
		else:
			rooms[splitted[0]] = Room(splitted[1], splitted[2], splitted[0])
	if connection is True:
		for line in file:
			splitted = line.split('-')
			if splitted[0] in rooms and splitted[1].rstrip() in rooms:
				rooms.get(splitted[0]).connectedTo.append(rooms.get(splitted[1].rstrip()))
