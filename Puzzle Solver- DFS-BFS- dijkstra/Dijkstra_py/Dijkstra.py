import numpy as np
from copy import deepcopy
from heapq import heapify, heappop

INF = 10000000
ZERO = "0"
COLUMNS = 3

class MatrixState():

    def __init__(self, currentState, cost=INF):
        self.currentState = currentState
        self.cost = cost
        self.previous = None
        self.lastValueTouched = 0

    def __str__(self) -> str:
        output = ""
        for item in self.currentState:
            output += f"{item[0]} {item[1]} {item[2]}\n"
        return output

    def __lt__(self, other):
        return self.cost < other.cost
                    
    def compareValues(self, other) -> bool:
        for tile in self.currentState == other.currentState:
            for i in range(3):
                if tile[i] == False:
                    return False
        return True

    def getCost(self) -> int:
        return self.cost

    def updateCost(self, num):
        self.cost = num

    def setPrev(self, other):
        self.previous = other

    def possibleMoves(self, createdPuzzleList: list, dfs=False) -> list:

        def movePiece(zeroIndex, newPos):

            newState = deepcopy(self)
            value = "0"

            value = newState.currentState[newPos]

            newState.currentState[zeroIndex] = value
            newState.currentState[newPos] = ZERO

            newState.lastValueTouched = int(value)
            newState.setPrev(self)

            if not dfs:
                newState.updateCost(self.getCost() + int(value))
            else:
                newState.updateCost(self.getCost() + 1)

            for matrixState in createdPuzzleList:
                if matrixState.compareValues(newState):
                    del newState
                    return matrixState, int(value)

            createdPuzzleList.append(newState)
            return newState, int(value)

        zeroIndex = np.where(self.currentState == ZERO)
        a = zeroIndex[0][0]
        b = zeroIndex[1][0]
        zeroIndex = a, b

        up = (a-1, b)
        left = (a, b+1)
        down = (a+1, b)
        right = (a, b-1)

        moves = list()
        if zeroIndex[0] > 0:
            moves.append(up)
        if zeroIndex[0] < COLUMNS-1:
            moves.append(down)
        if zeroIndex[1] > 0:
            moves.append(right)
        if zeroIndex[1] < COLUMNS-1:
            moves.append(left)

        nextMoves = list()
        for move in moves:
            newState = movePiece(zeroIndex, move)
            nextMoves.append([newState[0], newState[1]])

        return nextMoves


def dijkstra(startPuzzleState, desiredMatrix):
    level = 0

    createdStates = list()
    startPuzzleState.possibleMoves(createdStates)

    unvisited = createdStates
    heapify(unvisited)

    visited = []
    visited.append(startPuzzleState)

    while len(unvisited):
        level += 1
        currentState = heappop(unvisited)
        visited.append(currentState)

        unvisited = list()
        nextMoves = currentState.possibleMoves(createdStates)

        for nextMove in nextMoves:
            moveCost = nextMove[1]
            nextMove = nextMove[0]

            parentState = currentState.previous
            if not nextMove.compareValues(parentState):
                if nextMove in visited:
                    continue

                newCost = currentState.getCost() + moveCost
                if newCost < nextMove.getCost():
                    nextMove.updateCost(newCost)
                    nextMove.setPrev(currentState)
                    nextMove.lastValueTouched = moveCost
                else:
                    pass

                if nextMove.compareValues(desiredMatrix):
                    desiredMatrix.setPrev(nextMove.previous)
                    desiredMatrix.updateCost(nextMove.getCost())

                    path = []
                    current = desiredMatrix
                    while current is not None:
                        path.append(current)
                        current = current.previous

                    return path[::-1], desiredMatrix.getCost()

        for state in createdStates:
            if state not in visited:
                unvisited.append(state)

        heapify(unvisited)