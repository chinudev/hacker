

MaxN = 8000

def createDict(arr):
    arrDict = dict()

    for i in range(len(arr)):
        num = arr[i]
        if (num in arrDict):
            arrDict[num].append(i)
        else:
            arrDict[num] = [i]

    marker = len(arr)
    for key in arrDict:
        arrDict[key].append(marker)
    
    arrDict[0] = [marker]   # entry for elements not in array

    return arrDict


#DictCache = dict()

def findCount(arr, arrDict, x, y):

    if (x == y): 
        x=0
        y=0
    if (x not in arrDict): x = 0
    if (y not in arrDict): y = 0
    if (y < x): x,y = y,x

    #xyKey = str(x) + "." + str(y)
    #if xyKey in DictCache:
        #return DictCache[xyKey]

    runningCount = 0

    xList = arrDict[x]
    yList = arrDict[y]

    maxExcursion = max(len(xList), len(yList)) 
    trailingCount = [0 for i in range(maxExcursion*2+1)]
    zeroOffset = maxExcursion

    xIndex = 0
    yIndex = 0
    currIndex = 0

    while currIndex < len(arr): 
        #print("looping ", currIndex, xIndex, yIndex, runningCount, trailingCount, zeroOffset)
        if (currIndex == xList[xIndex]):
            trailingCount[zeroOffset] += 1
            zeroOffset += 1
            runningCount += trailingCount[zeroOffset]

            currIndex += 1
            xIndex += 1

        elif (currIndex == yList[yIndex]):
            trailingCount[zeroOffset] += 1
            zeroOffset -= 1
            runningCount += trailingCount[zeroOffset]

            currIndex += 1
            yIndex += 1

        else:
            minNext = min(xList[xIndex],yList[yIndex])
            nonXYCount = minNext - currIndex 

            # zeroOffset doesn't change
            adder = int((nonXYCount*(nonXYCount+1))/2) + nonXYCount*trailingCount[zeroOffset]
            #print(" handling zeros ", minNext, nonXYCount,adder, trailingCount, zeroOffset)
            runningCount += adder
            trailingCount[zeroOffset] += nonXYCount

            currIndex = minNext


    #DictCache[xyKey] = runningCount
    return runningCount


def unitTest():
    #arr = [1,1,1, 4, 1,1, 4, 1,1, 5, 1,1, 5, 1,1,1]
    #arr = [4,5,1,2,1,5,4]
    #arr = [1,1, 4, 1,1, 5, 1,1, 4,5, 4,5, 1,1]
    arr = [4,5,1,1]
    arrDict = createDict(arr)
    print(findCount(arr,arrDict, 4,5))
    #print(findCount(arr,arrDict, 1,2))
    return
    print(findCount(arr,arrDict, 4,5))
    print(findCount(arr,arrDict, 1,4))
    print(findCount(arr,arrDict, 1,5))
    print(findCount(arr,arrDict, 3,3))
    print(findCount(arr,arrDict, 6,1))
    print(findCount(arr,arrDict, 9,1))
    print(findCount(arr,arrDict, 1,7))


if __name__ == "__main__":
    #unitTest()

    n, q = input().strip().split(' ')
    n, q = [int(n), int(q)]
    arr = list(map(int, input().strip().split(' ')))
    arrDict = createDict(arr)
    for a0 in range(q):
        x, y = input().strip().split(' ')
        x, y = [int(x), int(y)]
        print(findCount(arr, arrDict, x, y))


