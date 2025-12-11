from itertools import combinations

from z3 import *


def get_optimal_presses(goal, buttons):
    best = len(buttons)+1
    for k in range(len(buttons)+1):
        if k >= best:
            return best
        for subset in combinations(buttons, k):
            lights = {i: False for i in range(len(goal))}
            for b in subset:
                for x in b:
                    lights[x] = not lights[x]
            lit_lights = tuple(lights[x] for x in range(len(goal)))
            if lit_lights == goal:
                best = min(best, len(subset))
    return best


def get_ip_solution(goal, buttons):
    n = len(goal)
    X = IntVector('x', len(buttons))

    s = Optimize()
    for k in range(len(buttons)):
        s.add([x >= 0 for x in X])

    A = []
    for button in buttons:
        row = [0 for _ in range(n)]
        for w in button:
            row[w] = 1
        A.append(row)

    for i in range(n):
        s.add(Sum(X[k]*A[k][i] for k in range(len(buttons))) == goal[i])
    s.minimize(Sum(X))

    # Check for satisfiability and get the model
    if s.check() == sat:
        model = s.model()
        return sum(model[k].as_long() for k in model)
    else:
        print("No solution found.")


result1 = 0
result2 = 0
with open('10.txt', 'r') as f:
    for line_num, line in enumerate(f.readlines()):
        i1 = line.find(']')
        pattern = line[1:i1]
        lights_goal = tuple(char == '#' for char in pattern)
        tokens = line[i1+2:].split()
        buttons = []
        for token in tokens[:-1]:
            buttons.append(eval(token[:-1] + ',)'))
        buttons = tuple(buttons)
        joltage_goal = eval('(' + tokens[-1][1:-1] + ',)')
        result1 += get_optimal_presses(lights_goal, buttons)
        result2 += get_ip_solution(joltage_goal, buttons)

print(result1)
print(result2)
