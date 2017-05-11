
def threeElemCheck(threeElemList):
    if (len(threeElemList) == 3) and  \
       (threeElemList in ([2,3,1], [3,1,2])):
        return True
    else:
        return False


def willItWork(numList):
    mismatchIndex = 0

    match = True   # tracks if everything as matched so far
    i=0
    while (i < len(numList)):
        if (i+1 != numList[i]): 
            if match == False:
                return False
            match = False

            if (i+3 > len(numList)):
                return False

            # check if next 3 
            threeElemList = [numList[i]   - i, 
                             numList[i+1] - i, 
                             numList[i+2] - i]
            if threeElemCheck(threeElemList) == True:
                i += 2
            else:
                return False

        i += 1

    return True



def readAndProcess():
    numTest = int(input().strip()) 
    for i in range(numTest):
        numEntries = int(input().strip())
        testArray = list(map(int, input().strip().split(' ')))

        assert(numEntries == len(testArray))

        if (willItWork(testArray)):
            print("YES")
        else:
            print("NO")



readAndProcess()

