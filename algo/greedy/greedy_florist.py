#https://www.hackerrank.com/challenges/greedy-florist
import sys

def getMinimumCost(numFlower, numPeople, costList):
    costList.sort(reverse=True)
    totalCost=0
    multiplyFactor=0

    for i in range(len(costList)):
        if (i%numPeople == 0):
            multiplyFactor += 1
        totalCost += multiplyFactor*costList[i]

    return totalCost


n, k = input().strip().split()
n, k = [int(n), int(k)]
c = list(map(int, input().strip().split(' ')))
minimumCost = getMinimumCost(n, k, c)
print(minimumCost)


