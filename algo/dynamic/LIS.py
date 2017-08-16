# https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem

MAX_NUM = 10**5


def findLIS(numList):

    maxLenSoFar = 0
    maxLenList = [0 for i in range(MAX_NUM+1)]
    for num in numList:
        # instead of adding 1 for each maxLenList[i], subtract 1 here
        maxLen = maxLenList[num] - 1
        for i in range(num):
            maxLen = max(maxLen, maxLenList[i])

        maxLenList[num] = maxLen + 1
        maxLenSoFar = max(maxLenSoFar, maxLen+1)

    return maxLenSoFar


n = int(input())
numList = []
for i in range(n):
    numList.append(int(input()))

print(findLIS(numList))

