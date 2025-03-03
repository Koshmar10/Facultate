class Automata:
    def __init__(self, file):
        self.file = file

    def get_file(self):
        return self.file
    
    def set_file(self, file):
        self.file = file
    
    def load_automata(self) -> dict:
        with open(self.file, 'r') as config_file:
            # read the config file contents
            configuration = config_file.read()

            # get the settings of respective automata
            # TODO: handling of multiple automatas
            
            automata_settings = configuration[
                configuration.find("automata {") + 10
                :
                configuration.find('}', configuration.find("automata {") + 10)
            ]
            
            # remove the formatting of the data for easier manipulation
            automata_settings = [line.strip() for line in automata_settings.split(";")]
            automata_settings = [line.replace("\n", "") for line in automata_settings]
            
            # store all the config settings in a python dictionary for easier manipulation
            settings_dict = {}
            for setting in automata_settings:
                if setting != '':
                    name, value = setting.split("=")
                    name = name.strip()
                    value = value.strip()
                    settings_dict[name] = value

            # delete the square brackets then transform the information into a list
            settings_dict['states'] = list(settings_dict['states'][1:-1].split(", "))
            settings_dict['alphabet'] = list(settings_dict['alphabet'][1:-1].split(", "))
            settings_dict['rules'] = [rule.split(',') for rule in settings_dict['rules'][1:-1].split(' ')]
            settings_dict['rules'] = [item for item in settings_dict['rules'] if item != ['']]
            
            # store rules in a dictionary structure for easier change of state
            state_change_structure = {}
            for rule in settings_dict['rules']:
                if rule[0] not in state_change_structure:
                    state_change_structure[rule[0]] = [''] * len(settings_dict['states'])
                    state_change_structure[rule[0]][int(rule[1])] = rule[2]
                else:
                    state_change_structure[rule[0]][int(rule[1])] = rule[2]
            settings_dict['rules'] = state_change_structure

            # return the dictionary that stores automata configuration
            return settings_dict

    def run_automata(self, data) -> None:
        # getting the automata configuration from file
        automata_config = self.load_automata()
        
        # setting the start and end states
        start_state = automata_config['start']
        end_state = automata_config['accept']

        current_state = start_state
        # parse through input data and change the state accordingly
        for symbol in data:
            if symbol not in automata_config['alphabet']:
                print("Invalid input")
                return
            else:
                current_state = automata_config['rules'][current_state][int(symbol)]
        
        # check if the end state is the one that is expected    
        if current_state == end_state:
            print("Accepted")
        else:
            print("Not Accepted")

# run automata
if __name__ == "__main__":
    MyAutomata = Automata("automata.txt")
    MyAutomata.run_automata("010")