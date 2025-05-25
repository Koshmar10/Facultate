import os
import re
import pprint as p

class Pda:
    def __init__(self, file_path):
        self.stack = []
        self.conf= os.path.join("Configs", file_path)
        self.rules = self.loadPda(self.conf)

    def loadPda(self, file):
        pdaDict = {}

        if os.path.isfile(file):
            with open(file, 'r') as config_file:
                configuration = config_file.read()
        else:
            # Assume the input is a configuration string
            configuration = file
        configuration = re.sub(r'#.*?\n', '', configuration)  # Remove comments
        configuration = configuration.replace('\n', ' ')
        configuration = configuration.split(';')
        config_dict = {}
        for line in configuration:
            if line != ' ' and line != '':
                key, value = line.split('=')
                key = key.strip()
                value = value.strip()
                if value[0] == '[':
                    value = value[1:-1]
                    if key!= 'rules':
                        value = [item.strip() for item in value.split(', ')]
                config_dict[key]=value

        rules = [line for line in config_dict['rules'].split(' ') if line!='']
        config_dict['rules']={}
        for rule in rules:
            current_state, pop_symbol, input_symbol,  push_symbol, next_state = rule.split(',')
            if current_state not in config_dict['rules']:
                config_dict['rules'][current_state] ={
                    input_symbol: {
                    'pop_symbol': pop_symbol,
                    'push_symbol': push_symbol,
                    'next_state': next_state
                    }
                }
            else:
                config_dict['rules'][current_state][input_symbol] ={
                    'pop_symbol': pop_symbol,
                    'push_symbol': push_symbol,
                    'next_state': next_state
                    }
                


        p.pprint(config_dict)
        return config_dict

        
    def runPda(self, inputData):
        #l-left  r-right u-up d-down
        def normalize(sym):
            if sym == 'l':
                return 'left'
            if sym == 'r':
                return 'right'
            if sym == 'u':
                return'up'
            return 'down'
        pda = self.rules
        stack = []
        current_state = pda['start']
        print(f'current state is {current_state}')
        for symbol in inputData:
            normalized_symbol = normalize(symbol)
            transition_rules = pda['rules'][current_state][normalized_symbol]
            if transition_rules['pop_symbol'] == '~' or transition_rules['pop_symbol'] == stack[-1]:
                current_state =transition_rules['next_state']
                if transition_rules['pop_symbol'] != '~':
                    if stack:
                        stack.pop()
                if transition_rules['push_symbol'] != '~':
                    stack.append(transition_rules['push_symbol'])
                print(stack)
                print(f'current state is {current_state}')

            else:
                print("could not move to next room ")
        if current_state in pda['accept']:
            print("Accepted")
        else:
            print("Rejected")
    
if __name__ == '__main__':
    pda = Pda('pda.txt')
    pda.runPda("lrlllluuu")

