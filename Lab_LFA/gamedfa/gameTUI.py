import curses, mapGen
import pprint as p
from pda import Pda
import re
from pyfiglet import Figlet
cmd_win , map_win, screen = None,None, None
debug_file = open("/home/petru/Facultate/Lab_LFA/gamedfa/debug.log", "w")
# debug_file.write("Debugging started\n")

class GameEngine:
    def __init__(self, automata, map_data):
        self.automata = automata
        self.game_rules = automata.get_settings()
        self.map_data = map_data
        self.game_stack = ['~']
        self.player_position = self.game_rules['start'] # Default starting position

    def move_player(self, direction):
        pass

    def get_current_position(self):
        return self.player_position

    def check_win(self):
        pass
    def start_game_loop(self):
        debug_file.write(p.pformat(self.game_rules))
        self.player_position  = self.game_rules['start']
        while True:
            self.render_map()
            
            symbol = map_win.getch()

            if symbol == ord('q'):
                break
            elif symbol in (curses.KEY_ENTER, 10):
                self.interaction(self.player_position)
            elif symbol == ord(':'):
                self.getInput(cmd_win)
            else:
                self.update_state(symbol)
    def run(self, cmd):
        cmd_win.clear()
        cmd_win.refresh()

        directions = cmd.split()
        for direction in directions:
            if direction in ('left', 'right', 'up', 'down'):
                self.player_position = self.game_rules['rules'][self.player_position][direction][0]
                self.render_map()
                curses.napms(1300)
                self.interaction(self.player_position)
            elif direction == '' or direction == ' ':
                pass                
            else: 
                return 0
        return 1 
    def display_cmd(self, cmd = ' '):
        cmd_win.clear()
        cmd_win.addstr(2, 1, f': {cmd}')
        cmd_win.refresh()

    def getInput(self, window: curses.window):
        # Access the window parameter to avoid unused variable error
        cmd = ''
        curses.curs_set(1)
        cursY, cursX = 1, 3
        minX = 3
        self.display_cmd()
        while True:
            char = window.getch()
            if char == curses.KEY_ENTER or char in [10, 13]:  # Handle Enter key
                # Send command and clear
                window.clear()

                curses.curs_set(0)
                if self.run(cmd) == 0:
                    curses.curs_set(0)
                    break
                else:
                    curses.curs_set(1)
                    cmd = ''
                    self.display_cmd(cmd)
            elif char == 27:  # Handle Escape key
                cmd = ''
                cmd_win.clear()
                cmd_win.refresh()
                curses.curs_set(0)
                return
            elif char == curses.KEY_BACKSPACE or char == 127:  # Handle Backspace key
                if cmd:
                    cmd = cmd[:-1]
                self.display_cmd(cmd) 
            else:
                cmd += chr(char)
                self.display_cmd(cmd)

    def interaction(self, room):
        if room == 'Exit':
            cmd_win.clear()
            figlet = Figlet(font='slant')
            win_message = figlet.renderText('YOU WON')
            height, width = cmd_win.getmaxyx()
            for i, line in enumerate(win_message.splitlines()):
                x = (width - len(line)) // 2
                y = (height - len(win_message.splitlines())) // 2 + i
                cmd_win.addstr(y, x, line)
            cmd_win.refresh()
            curses.napms(2000)
            exit(0)
            return

    def update_state(self, input_symbol):
        debug_file.write(f"Current position: {self.player_position}, Input: {input_symbol}\n")
        debug_file.write(f"Current stack: {self.game_stack}\n")

        if input_symbol == curses.KEY_UP:
            input_symbol = 'up'
        elif input_symbol == curses.KEY_DOWN:
            input_symbol = 'down'
        elif input_symbol == curses.KEY_LEFT:
            input_symbol = 'left'
        elif input_symbol == curses.KEY_RIGHT:
            input_symbol = 'right'
        
        # Ensure a transition rule exists for the current state and input
        if self.player_position not in self.game_rules['rules'] or \
           input_symbol not in self.game_rules['rules'][self.player_position]:
            # No valid transition for this input from this state.
            # Optionally, provide feedback to the user, e.g., curses.flash()
            debug_file.write(f"No transition rule for state {self.player_position} with input {input_symbol}\n")
            return

        transition_rules = self.game_rules['rules'][self.player_position][input_symbol]
        pop_sym = transition_rules['pop_symbol']
        push_sym = transition_rules['push_symbol']
        next_state = transition_rules['next_state']

        debug_file.write(f"Transition rule found: next_state={next_state}, pop={pop_sym}, push={push_sym}\n")

        # Condition to allow transition:
        # 1. The rule requires an epsilon pop ('~'), meaning no item is consumed from the stack.
        # 2. The rule requires a specific item to be popped, and that item is at the top of the stack.
        can_transition = False
        if pop_sym == '~':
            can_transition = True
        elif self.game_stack and self.game_stack[-1] == pop_sym: # Check stack is not empty and top matches
            can_transition = True
        
        if can_transition:
            self.player_position = next_state
            if pop_sym != '~' and (self.game_stack and self.game_stack[-1] == pop_sym) : # Ensure we only pop if it was an item match
                self.game_stack.pop()
            if push_sym != '~':
                self.game_stack.append(push_sym)
            debug_file.write(f"Moved to: {self.player_position}, New stack: {self.game_stack}\n")
        else:
            debug_file.write(f"Transition blocked: pop_sym='{pop_sym}', stack_top='{self.game_stack[-1] if self.game_stack else None}'\n")
            # Optionally, provide feedback for a blocked move, e.g., curses.flash()
        
    def render_map(self):
        map_win.clear()
        height, width = screen.getmaxyx()

        
        mapRows = self.map_data.split('\n')
        start_room, end_room = 0, 0
        focus_row = 0
        #pozStart, pozStop = find_current_room(self.map_data, self.player_position)
        # line number and line relativ coords
        maxi =0
        for line in mapRows:
            maxi = max(maxi, len(line))

        pad = (width-maxi)//2
        for i, line in enumerate(mapRows):
            #line = line.replace(' ', '_')  # Replace spaces with underscores
            line = f'{" " * pad}{line}'
            matches = list(re.finditer(rf'\b{re.escape(self.player_position)}\b(?!\d)', line, re.DOTALL))
            if matches:
                for match in matches:
                    focus_row = i
                    start_room, end_room = match.start(), match.end()
                    break
            
            # debug_file.write(line + '\n')
            mapRows[i] = line
        map_win.addstr(3, 2, " ".join(self.game_stack))
        for i, line in enumerate(mapRows):    
            try:
                if focus_row == i:
                    poz=2
                    map_win.addstr(i+5, poz, line[:start_room])
                    poz+=len(line[:start_room])
                    map_win.addstr(i+5, poz, line[start_room:end_room], curses.color_pair(1))
                    poz+=len(line[start_room:end_room])
                    map_win.addstr(i+5, poz, line[end_room:])
                else:
                    map_win.addstr(i+5, 2, line)
            except curses.error:
                pass
        # debug_file.write(f'\n{start_room} {end_room}\n')

        map_win.refresh()
    

def find_current_room(text, pattern):
    matches = re.finditer(pattern, text, re.DOTALL)

    positions = []
    for match in matches:
        start = match.start()
        end = match.end()
        return (start, end)
    
    


def main(stdscr):
    global map_win, cmd_win, screen
    rooms = ['Entrance', 'Kitchen', 'Dungeon', 'Library', 'Exit', 'SecretRoom', 'Bathroom', 'Armory']
    requirements = {'Entrance': {'requires': '~', 'aquires': '~'},
                    'Kitchen': {'requires': '~', 'aquires': '~'},
                    'Dungeon': {'requires': 'sword', 'aquires': '~'},
                    'Bathroom': {'requires': '~', 'aquires': '~'},
                    'SecretRoom': {'requires': '~', 'aquires': 'key'},
                    'Armory': {'requires': '~', 'aquires': 'sword'},
                    'Library': {'requires': '~', 'aquires': '~'},
                    'Exit': {'requires': 'key', 'aquires': '~'}}
    # Open a file for debugging
    curses.start_color()
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)  # Define color pair 1
    m=mapGen.getMapInfo(rooms, 15)
    conf = mapGen.generateAutomataConfig(m[1], reqierments=requirements)
    p.pprint(conf)
    debug_file.write('\n' + p.pformat(conf + '\n'))
    engine = GameEngine(Pda(conf), m[0])

    curses.curs_set(0)  # Disable the cursor
    stdscr.clear()  # Clear the screen
    
    screen = curses.initscr()
    # Get screen dimensions
    #debug_file.write(f'found {curr_room} at: {highlight(gameMap, curr_room)}')
    height, width = screen.getmaxyx()

    # Calculate dimensions for map and command windows
    map_height = int(height * 0.8)
    cmd_height = height - map_height

    # Create map window
    map_win = curses.newwin(map_height, width, 0, 0)
    map_win.keypad(True)  # Enable keypad mode for arrow key inputs

    # Create command window
    cmd_win = curses.newwin(cmd_height, width, map_height, 0)

    # Create a pad for the map|
    # Add the game map to the pad
      # Ignore errors caused by invalid characters or out-of-bounds writes

    # Refresh the windows to display them
    cmd_win.refresh()
    map_win.refresh()
    # Example of writing text to the screen


    screen.refresh()
    # Wait for user input
    engine.start_game_loop()

if __name__ == "__main__":
    curses.wrapper(main)