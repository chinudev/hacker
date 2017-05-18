#!/bin/python3
# https://www.hackerrank.com/contests/w31/challenges/zero-one-game

import sys


g = int(input().strip())
for a0 in range(g):
    n = int(input().strip())
    sequence = list(map(int, input().strip().split(' ')))
    for i in range(1,len(sequence)-1): 
        # replace pattern 010 by 000
        if (sequence[i-1] == 0) and (sequence[i] == 1) and (sequence[i+1] == 0):
            sequence[i]=0

    print(sequence)
    moveCount=0
    for i in range(1,len(sequence)-1):
        if (sequence[i-1] == 0) and (sequence[i+1] == 0):
            moveCount += 1
       
    print("move count ",moveCount)
    if moveCount % 2 == 0 : 
        print('Bob')
    else:
        print('Alice')
            
'''
3
4
1 0 0 1
5
1 0 1 0 1
6
0 0 0 0 0 0

expected output 
Bob
Alice
Bob
'''
