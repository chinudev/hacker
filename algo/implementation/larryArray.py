

def willItWork(numList):

    length = len(numList)

    for i in range(length-2):
        numIndex = numList.index(i+1)

        if (numIndex != i): 
            numList = numList[:i] + [i+1] + numList[i:numIndex] + numList[numIndex+1:]
            #print("*****",numList)
            if ((numIndex-i) % 2 == 1):
                #print("*****swapping")
                numList[i+1], numList[i+2] = numList[i+2], numList[i+1]
        #print("***",i,numIndex,numList)

    #print(numList)
    if ((numList[-1] == length) and (numList[-2] == length-1)):
        return True
    else:
        return False



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

