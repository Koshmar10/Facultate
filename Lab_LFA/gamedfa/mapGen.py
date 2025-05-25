import automata
import random
from collections import deque
import pprint as p
room_names = ['Entrance', 'Kitchen', 'Dungeon', 'Library', 'Exit', 'SecretRoom', 'Bathroom', "Armory"]
requirements = {'Entrance': {'requires': '~', 'aquires': '~'},
                    'Kitchen': {'requires': '~', 'aquires': '~'},
                    'Dungeon': {'requires': 'sword', 'aquires': '~'},
                    'Bathroom': {'requires': '~', 'aquires': '~'},
                    'SecretRoom': {'requires': '~', 'aquires': 'key'},
                    'Armory': {'requires': '~', 'aquires': 'sowrd'},
                    'Library': {'requires': '~', 'aquires': '~'},
                    'Exit': {'requires': 'key', 'aquires': '~'}}
link_points = ['left', 'up', 'right', 'down']
roomConnections={}



def getMapInfo(rooms, count):
    x= generateMap(room_names,count)
    map_string = generateMapString(x[0], x[1])
    return (map_string, x[0], x[1])
def center(word):

    return len(word)//2
    
def printMap(file, mapItems, roomxy:dict):
    with open(file, "w") as map_file:
        map_file.write(p.pformat(mapItems) + "\n")
        map_file.write(p.pformat(roomxy) +'\n' )
        mapString = generateMapString(mapItems, roomxy)
        map_file.write(p.pformat(roomConnections) +'\n')
        
        map_file.write('\n' + mapString)

def generateMapString(mapItems, roomxy: dict) -> str:
    # Generate the map as a string
    mapH, mapW = 0, 0
    maxx, minx, maxy, miny = 0, 0, 0, 0
    for item in mapItems[1:]:
        if item[3] not in roomConnections:
            roomConnections[item[3]] = [item[2]]
        else:
            roomConnections[item[3]].append(item[2])
        if item[1] not in roomConnections:
            roomConnections[item[1]] = [oppositeDirection(item[2])]
        else:
            roomConnections[item[1]].append(oppositeDirection(item[2]))

    # Get map dimensions
    for x, y in roomxy.values():
        maxy, miny = max(maxy, y), min(miny, y)
        maxx, minx = max(maxx, x), min(minx, x)

    mapH = maxy - miny + 1
    mapW = maxx - minx + 1

    # Allocate space for the largest room name
    cellW = len(max([name for name in roomxy.keys()], key=len))
    cellSpace = '  '
    lrCom = '--'

    # Build the map string
    mapString = ''
    for row in range(maxy, miny - 1, -1):
        currentRow = ''
        rowBelow = ''
        for col in range(minx, maxx + 1, +1):
            cellSpace = '  '
            item = ''
            itemBelow = ' ' * cellW
            if not validxy(roomxy, (col, row)):
                x = ''
                for roomName, xy in roomxy.items():
                    if (col, row) == xy:
                        x = roomName
                suffix = ' ' * ((cellW - len(x)) // 2 if (cellW - len(x)) % 2 == 0 else (cellW - len(x)) // 2 + 1)
                prefix = ' ' * ((cellW - len(x)) // 2 if (cellW - len(x)) % 2 == 0 else (cellW - len(x)) // 2 + 1)
                if 'left' in roomConnections.get(x, []) and 'right' in roomConnections.get(x, []):
                    suffix = '-' * ((cellW - len(x)) // 2 if (cellW - len(x)) % 2 == 0 else (cellW - len(x)) // 2 + 1)
                    prefix = '-' * ((cellW - len(x)) // 2)
                    cellSpace = lrCom
                elif 'left' in roomConnections.get(x, []):
                    prefix = '-' * ((cellW - len(x)) // 2)
                elif 'right' in roomConnections.get(x, []):
                    suffix = '-' * ((cellW - len(x)) // 2 if (cellW - len(x)) % 2 == 0 else (cellW - len(x)) // 2 + 1)
                    cellSpace = lrCom
                if 'down' in roomConnections.get(x, []):
                    itemBelow = f'|'.center(cellW)
                item = f'{prefix}{x}{suffix}'
            else:
                item = ' ' * cellW
            currentRow += item + cellSpace
            rowBelow += itemBelow + ' ' * len(cellSpace)
        mapString += currentRow.rstrip() + '\n'
        mapString += rowBelow + '\n'

    return mapString

def getUniqueName(gameMap, roomName):
    i=1
    newName = f'{roomName}'
    for mapItem in gameMap:
        if mapItem[1] == newName:
            newName = f'{roomName}{i}'
            i+=1
    return newName
def getGeneralName(name):
    while name[-1].isdigit():
        name = name[:-1]
    return name
def oppositeDirection(direction):
    if direction == 'left':
        return 'right'
    elif direction == 'right':
        return 'left'
    elif direction == 'up':
        return 'down'
    elif direction == 'down':
        return 'up'
    else:
        return direction

def validxy(xylist, myxy):
    for xy in xylist.values():
        if myxy == xy:
            return False
    return True
def calcxy(currentxy, direction):
    if direction == 'left':
        return (currentxy[0]-1, currentxy[1]) 
    elif direction == 'right':
        return (currentxy[0]+1, currentxy[1])
    elif direction == 'up':
        return (currentxy[0], currentxy[1]+1)
    elif direction == 'down':
        return (currentxy[0], currentxy[1]-1)
    else:
        return currentxy
def generateMap(rooms, maxRoomCount): 
    # Map item structure: (id, roomName, linkDirection, parent)
    gameMap = []
    queue = deque()
    
    # Start with the Entrance
    entranceRoom = rooms[0]  # Assume the first room in the list is the Entrance
    queue.append((entranceRoom, None))  # No parent direction for the Entrance
    gameMap.append((0, entranceRoom, None, None))  # Entrance has no parent
    id = 1
    roomxy = {entranceRoom: (0, 0)}
    
    # Exclude Exit and Entrance from random selection during generation
    nonSpecialRooms = [room for room in rooms if room != 'Exit' and room != 'Entrance']
    
    # Main generation process
    while queue and len(gameMap) < maxRoomCount:
        currentRoom = queue.popleft()
        currentRoomName, currentDirection = currentRoom
        adjacentRoomsCount = random.randrange(1, len(link_points))  # Random number of adjacent rooms
        availableDirs = link_points.copy()
        
        # Remove the direction leading back to the parent (if applicable)
        if currentDirection:
            availableDirs.remove(oppositeDirection(currentDirection))
        
        while adjacentRoomsCount:
            if not availableDirs:
                break
            direction = random.choice(availableDirs)
            availableDirs.remove(direction)
            room = random.choice(nonSpecialRooms)  # Only select non-special rooms
            
            newRoomName = getUniqueName(gameMap, room)
            newRoomId = id
            newxy = calcxy(roomxy[currentRoomName], direction)
            
            if validxy(roomxy, newxy):
                roomxy[newRoomName] = newxy
                gameMap.append((newRoomId, newRoomName, direction, currentRoomName))
                queue.append((newRoomName, oppositeDirection(direction)))
                adjacentRoomsCount -= 1
                id += 1
    
    # Add the Exit room after generation
    exitAdded = False
    for roomName, xy in list(roomxy.items())[::-1]:  # Iterate over the last generated rooms
        for direction in link_points:
            newxy = calcxy(xy, direction)
            if validxy(roomxy, newxy):  # Find a valid position for the Exit
                exitRoomName = getUniqueName(gameMap, 'Exit')
                roomxy[exitRoomName] = newxy
                gameMap.append((id, exitRoomName, direction, roomName))
                exitAdded = True
                break
        if exitAdded:
            break
    
    return (gameMap, roomxy)
def generateAutomataConfig(mapItems, reqierments: dict):

    states, alphabet, rules = 'states = [ ', 'alphabet = [ ', 'rules = [ '
    for item in mapItems[:-1]:
        states += f'{item[1]}, '
    states += f'{mapItems[-1][1]}];'
    for link in link_points[:-1]:
        alphabet +=f'{link}, '
    alphabet += f'{link_points[-1]}'
    alphabet += ' ];'

    ruleDict = {}
    for item in mapItems[1:]:
        if item[3] not in ruleDict:
            ruleDict[item[3]]={
                item[2]:item[1]
            }
        else:
            ruleDict[item[3]][item[2]]=item[1]
        if item[1] not in ruleDict:
            ruleDict[item[1]] ={
                oppositeDirection(item[2]): item[3]
            }
        else:
            ruleDict[item[1]][oppositeDirection[item[2]]]= item[3]
    for state, transitions in ruleDict.items():
        for direction in link_points:
            if direction not in transitions:
                transitions[direction] = state
    #turn states into text
    ruleString=''

    for initial, transitions in ruleDict.items():
        for transition, next in transitions.items():
            ruleString += f'{initial},{reqierments[getGeneralName(initial)]['requires']},{transition},{reqierments[getGeneralName(next)]['aquires']},{next} '
    rules +=  ruleString + '];'
    stack_alphabet = 'stack_alphabet = [ '
    x = set()
    for item in reqierments.values():
        x.add(item['requires'])
        x.add(item['aquires'])
    x= list(x)
    for item in x[:-1]:
        stack_alphabet += f'{str(item)}, '
    stack_alphabet += f'{str(item[-1])} ];'

    start = 'start = Entrance;'
    accept = 'accept = [ Exit ];'
    config = states + alphabet+ stack_alphabet + rules + start + accept
    p.pprint(config)
    return config

if __name__ == '__main__':
    gameMap = generateMap(room_names, 12)
    generateAutomataConfig(gameMap[0], requirements)
    #p.pprint(gameMap[0])
    #p.pprint(gameMap[1])
    printMap('/home/petru/Facultate/Lab_LFA/gamedfa/map.txt', gameMap[0], gameMap[1])