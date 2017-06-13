#!/bin/python3
# https://www.hackerrank.com/contests/w33/challenges/pattern-count 

import sys

def patternCount(s):
    # state is used to track state machine. 
    #   0 => no match
    #   1 => 1 found
    #   2 => 0 following a one
    #
    state = 0
    patternCount = 0

    for c in s:
        if c == '0':
            if state == 1:
                state = 2
            elif state == 2:
                state = 2
            else: 
                state = 0
        elif c == '1':
            if state == 2: patternCount += 1
            state = 1

        else: 
            state = 0

    return patternCount
            


def test():
    assert(2 == patternCount("10001abc101"))
    assert(0 == patternCount("00011"))
    assert(1 == patternCount("101"))
    assert(1 == patternCount("11001"))
    assert(2 == patternCount("101010"))
    assert(0 == patternCount("10a1a010"))


#test()

q = int(input().strip())
for a0 in range(q):
    s = input().strip()
    result = patternCount(s)
    print(result)

