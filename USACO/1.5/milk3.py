"""
ID: jamessh3
LANG: PYTHON3
TASK: milk3
"""
#######
#######
############## Think about the time complexity of this problem, if number of jugs are increased, by what factor would the runtime increase

def next(direction, state, capacities): ####### direction is a "str" of two single digits, 1 2 or 3 representing jug 1 2 or 3, milk poured from left to right

    source_index = int(direction[0]) - 1
    sink_index = int(direction[1]) - 1
    transfer = min(state[source_index], capacities[sink_index] - state[sink_index])
    next_state = list(state)
    next_state[source_index] -= transfer
    next_state[sink_index] += transfer
    next_state = tuple(next_state)
    return next_state
    
fin = open("milk3.in", "r")
fout = open("milk3.out", "w")
A, B, C = map(int, fin.readline().strip().split())


states_set = set()
states_stack = []
capacities = (A,B,C)
initial_state = (0,0,C)
state = initial_state
states_set.add(state)
states_stack.append(state)

####### maximum four pouring options, can't pour into a full container, can't pour from empty container, can't pour back into container just poured from
####### a -> b: "12"    b -> a: "21"    a -> c: "13"    c -> a: "31"    b -> c: "23"    c -> b: "32"
####### find viable pour options, always pour leftmost pouring option in choices list, then delete from list
####### DFS stack tracking the progressive states of the jugs

solutions = []
choices_ = []
prev_pour = "" ####### initialize var prev_pour, no pour has been made yet so empty, usually takes on "12", "21", "13", "31", "23", or "32"
choices_stack = []
while len(states_stack) != 0:

    if state[0] == 0:
        solutions.append(state[2])
    states_set.add(state)
    states_stack.append(state)

    # choices substack consisting of pouring directions, always select last choice, then pop from choices, when choices is empty, choices popped from choices_stack
    
    choices = []
    x = state[0]
    y = state[1]
    z = state[2]
    if x != 0 and y != B and prev_pour != "21":
        direction = "12"
        next_state = next(direction, state, capacities)
        if next_state not in states_set:
            choices.append("12")
    if y != 0 and x != A and prev_pour != "12":
        direction = "21"
        next_state = next(direction, state, capacities)
        if next_state not in states_set:
            choices.append("21")
    if x != 0 and z != C and prev_pour != "31":
        direction = "13"
        next_state = next(direction, state, capacities)
        if next_state not in states_set:
            choices.append("13")
    if z != 0 and x != A and prev_pour != "13":
        direction = "31"
        next_state = next(direction, state, capacities)
        if next_state not in states_set:
            choices.append("31")
    if y != 0 and z != C and prev_pour != "32":
        direction = "23"
        next_state = next(direction, state, capacities)
        if next_state not in states_set:
            choices.append("23")
    if z != 0 and y != B and prev_pour != "23":
        direction = "32"
        next_state = next(direction, state, capacities)
        if next_state not in states_set:
            choices.append("32")

    if len(choices) == 0:
        states_stack.pop()
        if len(choices_stack) == 0:
            break
        while len(choices_stack) != 0:
            if len(choices_stack[-1]) == 0:
                states_stack.pop()
                choices_stack.pop()
            else:
                break
        if len(choices_stack) == 0:
            break
        direction = choices_stack[-1].pop()
        state = next(direction, states_stack[-1], capacities)
        if state not in states_set:
            prev_pour = direction
        else:
            while state in states_set:
            ####### search to completion, if states_set is empty at the end of the search, then all solutions guaranteed to be found
                while len(choices_stack) != 0:
                    if len(choices_stack[-1]) == 0:
                        states_stack.pop()
                        choices_stack.pop()
                    else:
                        break
                if len(choices_stack) == 0:
                    break
                direction = choices_stack[-1].pop()
                state = next(direction, states_stack[-1], capacities)
            prev_pour = direction
    else:
        direction = choices.pop()
        choices_stack.append(choices)
        state = next(direction, state, capacities)
        if state not in states_set:
            prev_pour = direction
        else:
            while state in states_set:
            ####### search to completion, if states_set is empty at the end of the search, then all solutions guaranteed to be found
                while len(choices_stack) != 0:
                    if len(choices_stack[-1]) == 0:
                        states_stack.pop()
                        choices_stack.pop()
                    else:
                        break
                if len(choices_stack) == 0:
                    break
                direction = choices_stack[-1].pop()
                state = next(direction, states_stack[-1], capacities)
            prev_pour = direction
            

solutions.sort()
for i in range(len(solutions)):
    if i != len(solutions) - 1:
        fout.write(str(solutions[i]) + " ")
    else:
        fout.write(str(solutions[i]) + "\n")

fin.close()
fout.close()
        
    

    
        
    
    
        
    


