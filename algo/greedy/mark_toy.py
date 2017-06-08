# https://www.hackerrank.com/challenges/mark-and-toys

from heapq import *

(numEntries, money) = list(map(int,input().split()))
costTable = list(map(int,input().split()))
costTable.sort()

numToys = 0

for cost in costTable:
    money -= cost
    if (money > 0): numToys += 1

print(numToys)


