# https://www.hackerrank.com/challenges/the-indian-job/problem


def findMatch(numList, target):

    minTarget = sum(numList) - target
    if minTarget > target:
        return False

    if (target == 0): return True
    if (minTarget <= 0): return True

    # we need to find one set of numbers that will add up to target.
    possibleArray = [0 for i in range(minTarget)]
    possibleArray[0]=1

    for num in numList:
        for i in range(minTarget-1,-1,-1):
            if (possibleArray[i] == 1):
                newPossibility = i+num
                if (newPossibility >= minTarget) and  (newPossibility <= target):
                    return True
                if newPossibility < minTarget:
                    possibleArray[newPossibility]=1 
        #print(possibleArray)
    return False

def unitTest():
    print(findMatch([2,4,2], 4))
    print(findMatch([2,4,2], 2))


#unitTest()

numTest = int(input())
for i in range(numTest):
    n,target = list(map(int,(input().split())))
    numList = list(map(int,(input().split())))
    if (findMatch(numList, target) == True):
        print("YES")
    else:
        print("NO")



