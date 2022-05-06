import numpy as np
from Dijkstra import np, MatrixState, dijkstra

input = str(input(
    "Please enter an array of integers describing a 3 x 3 matrix.\nExample Format: ['1', '3', '4', '8', '0', '6', '7', '5', '2']\n"))

GOAL_MATRIX = np.array([(1,  2, 3),
                          (8, 0, 4),
                          (7,  6, 5)], dtype=str)

GOAL_MATRIX = MatrixState(GOAL_MATRIX)

values = list()
for ch in input:
    if ch.isalnum():
        values.append(ch)

currentState = np.empty([9], dtype=object)
for i in range(9):
    currentState[i] = values[i]

currentState.resize(3, 3)
currentState = MatrixState(currentState, 0)

while True:
    print("Implementing Dijkstra")
    path, cost = dijkstra(currentState, GOAL_MATRIX)
    break


print("Current State:")
print(currentState)
print(f"Cost: {cost}")
print("-"*30)

if path != None:
    for i, state in enumerate(path):
        if i > 0:
            print(f"Move {i}:")
            print(state)
            print(f"Cost: {state.getCost()}")
            print("-"*15)
else:
    print("error")
