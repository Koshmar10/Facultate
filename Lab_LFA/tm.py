import os
#Touring machine
import pprint

class TouringMachine:
    def __init__(self, config_filename: str, max_steps):
        base_dir = os.path.dirname(__file__)
        config_path = os.path.join(base_dir, "Configs", config_filename)
        self.config = self.load_tm(config_path)
        self.max_steps = max_steps

    def get_config(self):
        return self.config
    def load_tm(self,  config_path: str):
        with open(config_path) as file:
            content = file.read()
            content = content.split(';')
            content = [line.strip() for line in content]
            #key - value split
            config = {}
            for line  in content:
                if line:
                    (key, value) = line.split('=')
                    #print(key, value)
                    key = key.strip()
                    value = value.strip()
                    if value[0] == '[':
                        value = value[1:-1]
                        if key == 'rules':
                            value = value.split('\n')
                            value = [line.strip() for line in value if line.strip() != '']
                            rule_dict ={}
                            for rule in value:
                                parts = [p.strip() for p in rule.split(',')]
                                state, read_symbol, output_symbol, direction, next_state = parts
                                rule_dict.setdefault(state, {})[read_symbol] = {
                                    'output': output_symbol,
                                    'direction': direction,
                                    'next_state': next_state
                                }

                                
                            config[key]= rule_dict
                        else:
                            config[key.strip()] = value.split(', ')
                    else:
                        config[key.strip()]=value
            pprint.pprint(config)
            return config
            #print(content)
    
    def emulate(self, tape_input: str) -> bool:
        tape   = list(tape_input)
        head   = 0
        blank  = self.config['blank']
        rules  = self.config['rules']
        accept = set(self.config['accept'])
        try:
            reject = set(self.config['reject'])
        except:
            reject = []
        steps  = 0
        state = self.config['start']
        while steps < self.max_steps:
            # ——— 1) Infinite‐tape expansion —————————————————
            
            if head < 0:
                tape.insert(0, blank)
                head = 0
            elif head >= len(tape):
                tape.append(blank)
            symbol = tape[head]

            # ——— 2) Accept check —————————————————————
            if state in accept:
                return True
            if state in reject:
                return False 

            # ——— 3) Lookup rule for (state, symbol) ——————
            try:
                rule = rules[state][symbol]
            except KeyError:
                # no transition for this state+symbol → reject
                return False

            # ——— 4) Apply rule: write → move → change state ——
            tape[head] = rule['output']
            if rule['direction'] == 'R':
                head += 1
            else:
                head -= 1

            state = rule['next_state']
            steps += 1

        # ——— 5) Timeout → reject ————————————————————
        return False


          
            

touring = TouringMachine("tm.txt", max_steps=100_000)
    # False (REJECT)
print(touring.emulate(""))     # ACCEPT (0 is even)
print(touring.emulate("11"))   # ACCEPT (2 is even)
print(touring.emulate("1111")) # ACCEPT (4 is even)

print(touring.emulate("1"))    # REJECT (1 is odd)
print(touring.emulate("111"))  # REJECT (3 is odd)
