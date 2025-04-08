import sys
import mapGen
from pprint import pprint
from pathlib import Path


# Add the parent of the parent folder to sys.path
parent_directory = Path(__file__).resolve().parent.parent
sys.path.append(str(parent_directory))

import automata as aut

def game_loop(game_rules):
    game_mode = input("Select how to play <all at once>(1) / <one at a time>(2)")
    if game_mode == "1":
        print('''provide a string of pinputs
                l - left
                r -right
                u - up
                d - down ''')
        movement_inputs=input()
        currentRoom = game_rules['start']
        for movement in movement_inputs:
            movement_translation = {'l': 'left', 'r': 'right', 'u': 'up', 'd': 'down'}
            if movement in movement_translation:
                translated_movement = movement_translation[movement]
            else:
                print(f"Invalid movement: {movement}")
                continue
            print(f"Went from {currentRoom}", end=' ')
            currentRoom = str(game_rules['rules'][currentRoom][translated_movement][0])
            print(f" To {currentRoom}")
        print(game_rules['accept'])
        if currentRoom in game_rules['accept']:
            print("You won the game")
        else:
            print("Ai pierdut panaramo")
        

# Initialize the Automata class with the file 'automata.txt'
if __name__ == "__main__":
    mapInfo = mapGen.generateMap(mapGen.room_names, 12)
    conf = mapGen.generateAutomataConfig(mapInfo[0])
    engine = aut.Automata(conf)
    game_rules = engine.get_settings()
    pprint(game_rules)
    pprint(mapGen.generateMapString(mapInfo[0], mapInfo[1]))
    game_loop(game_rules)

# If you want to avoid printing, ensure the Automata class does not print during initialization.