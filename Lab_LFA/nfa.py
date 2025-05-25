from automata import automata as aut

dfa = aut.Automata("dfa.txt")
print(dfa.runAutomata("00"))
nfa= aut.Automata("nfa.txt")
print(nfa.runAutomata("000000"))