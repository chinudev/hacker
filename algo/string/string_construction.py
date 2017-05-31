#https://www.hackerrank.com/challenges/string-construction

import sys

def computeCost(s):
    return len(set(s))

n = int(input().strip())
for a0 in range(n):
    s = input().strip()
    print(computeCost(s)) 

