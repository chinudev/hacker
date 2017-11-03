# https://www.hackerrank.com/challenges/priyanka-and-toys

numToys = int(input())
toyList = list(map(int, input().split()))
    
toyList.sort()

numUnits=0

prevCost = -10

for cost in toyList:
    if cost > prevCost+4:
        numUnits += 1
        prevCost = cost

print(numUnits)


