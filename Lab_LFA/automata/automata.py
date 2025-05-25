import re
import sys
import os  # Import os for path manipulation
accepts=[]

class Automata:
    def __init__(self, file_path):
        # Prepend the Configs folder to the file path
        self.file_path = os.path.join("Configs", file_path)
        self.settings = self.load_automata(self.file_path)
        
    def get_file_path(self):
        return self.file_path
    def get_settings(self):
        return self.settings
    def set_settings(self, settings):
        self.settings = settings
    def set_file_path(self, file_path):
        self.file_path = os.path.join("Configs", file_path)
    
    def load_automata(self, input_data) -> dict:
        # Check if the input is a file path or a configuration string
        if os.path.isfile(input_data):
            with open(input_data, 'r') as config_file:
                configuration = config_file.read()
        else:
            # Assume the input is a configuration string
            configuration = input_data

        # Process the configuration
        configuration = re.sub(r'#.*?\n', '', configuration)  # Remove comments
        automata_settings = configuration[
            configuration.find("automata {") + 10
            :
            configuration.find('}', configuration.find("automata {") + 10)
        ]
        
        # Remove the formatting of the data for easier manipulation
        automata_settings = [line.strip() for line in automata_settings.split(";")]
        automata_settings = [line.replace("\n", "") for line in automata_settings]
        
        # Store all the config settings in a Python dictionary for easier manipulation
        settings_dict = {}
        for setting in automata_settings:
            if setting != '':
                try:
                    name, value = setting.split("=")
                except ValueError:
                    raise ValueError(f"Invalid setting format: {setting}")
                name = name.strip()
                value = value.strip()
                settings_dict[name] = value

        # Parse specific settings into lists or dictionaries
        try:
            settings_dict['states'] = list(settings_dict['states'][1:-1].split(", "))
            settings_dict['alphabet'] = list(settings_dict['alphabet'][1:-1].split(", "))
            settings_dict['accept'] = list(settings_dict['accept'][1:-1].split(", "))
            ruleSet = [state for state in settings_dict['rules'][1:-1].split(' ') if state != '']
            rule_dict = {}
            for rule in ruleSet:
                initial = rule.split(',')[0]
                transition = rule.split(',')[1]
                final = rule.split(',')[2]
                
                if initial not in rule_dict:
                    rule_dict[initial] = {}
                if transition not in rule_dict[initial]:
                    rule_dict[initial][transition] = [final]
                else:
                    rule_dict[initial][transition].append(final)

            settings_dict['rules'] = rule_dict
            
        except KeyError as e:
            raise ValueError(f"Configuration incorrect: missing key {e}")
        except Exception as e:
            raise ValueError(f"Configuration incorrect: {e}")

        # Return the dictionary that stores automata configuration
        return settings_dict

    def runSubAutomata(self, data, start='') -> None:
        # getting the automata configuration from file
        currentState=''
        if start == '':
            currentState=self.settings['start']
        else:
            currentState=start
        print('subPorcess')
        for symbol in data:
            print('sbproc', currentState)
            currentState=self.settings['rules'][currentState][symbol][0]
        if currentState in self.settings['accept']:
            return True
        else:
            return False
    def runAutomata(self, data):
        accInputs=False
        currentState=self.settings['start']        
        for i, symbol in enumerate(data):
            print('maainProc', currentState)
            if 'ε' in self.settings['rules'][currentState]:
                for state in self.settings['rules'][currentState]['ε']:
                    accInputs = accInputs or self.runSubAutomata(data[i:], state)
            if symbol in self.settings['rules'][currentState]:
                nextStates=self.settings['rules'][currentState][symbol]
                currentState=nextStates[0]
                if len(nextStates) > 1:
                    firstPass=False
                    for state in nextStates:
                        if firstPass:    
                            accInputs = accInputs or self.runSubAutomata(data[i+1:], state)
                        firstPass=True
                
        if currentState in self.settings['accept']:
            accInputs = True
        return False or accInputs

    
# run automata
'''
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python automata.py <path_to_automata_file>")
        sys.exit(1)
    
    automata_file_path = sys.argv[1]
    MyAutomata = Automata(automata_file_path)
    print(MyAutomata.load_automata())
    if MyAutomata.runAutomata(''):
        print("Accepted")
    else:
        print("Not Accepted")
'''
