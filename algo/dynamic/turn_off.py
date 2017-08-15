# https://www.hackerrank.com/challenges/turn-off-the-lights/problem

def findBest(numList, k):
    leastCost = 2**60
    n = len(numList)

    # starting point can be index 0,1,2,...k. 
    #  after that we jump 2k+1 
    for i in range(k+1):
        if i >= n: 
            break
        if (((n-1-i) % (2*k+1)) > k):
            continue

        currSum = 0
        for j in range(i,n,2*k+1):
            currSum += numList[j]
        leastCost = min(leastCost, currSum)

    return leastCost

n,k = list(map(int,input().split()))
numList = list(map(int,input().split()))
print(findBest(numList,k))


