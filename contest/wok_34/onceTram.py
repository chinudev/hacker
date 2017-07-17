#!/bin/python3

import sys

def isLucky(x):
    second = x % 1000
    first = int(x/1000)
    firstSum = sum(list(map(int,(str(first)))))
    secondSum = sum(list(map(int,(str(second)))))
    return (firstSum == secondSum)
        
def onceInATram(x):
    
    while True:
        x += 1
        if (isLucky(x)): break
   
    return x
    

if __name__ == "__main__":
    x = int(input().strip())
    result = onceInATram(x)
    print(result)

