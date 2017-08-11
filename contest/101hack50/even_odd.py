#!/bin/python3

import sys

def minimumChocolateMoves(n, X):
    chocsAvail = 0
    wrongBoxChocsAvail = 0
    wrongBoxes = 0
    for i in range(n):
        if (i % 2):         # odd index
            chocsAvail += X[i]-1    # need to leave at least 1 chocolate, others can be distributed
            if (X[i] % 2 == 0):
                wrongBoxes += 1
                wrongBoxChocsAvail += 1
        else:                
            chocsAvail += X[i]-2    # need to leave at least 2 chocolates, others can be distributed
            if (X[i] % 2):
                wrongBoxes += 1
                if (X[i] > 2): wrongBoxChocsAvail += 1

    print(wrongBoxes, chocsAvail, wrongBoxChocsAvail)
    if (wrongBoxes % 2): return -1
    if (chocsAvail < 0): return -1

    if (wrongBoxes <= 2*wrongBoxChocsAvail): 
        return int(wrongBoxes/2)
    else:
        return wrongBoxChocsAvail + (wrongBoxes-2*wrongBoxChocsAvail)

    # Complete this function

#  Return the minimum number of chocolates that need to be moved, or -1 if it's impossible.
q = int(input().strip())
for a0 in range(q):
    n = int(input().strip())
    X = list(map(int, input().strip().split(' ')))
    result = minimumChocolateMoves(n, X)
    print(result)
