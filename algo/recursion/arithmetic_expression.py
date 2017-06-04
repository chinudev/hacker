

def getAnswer(numList, mod):

    modListList = [[] for i in range(len(numList))]

    # create entry for the first number
    modList = [0 for i in range(mod)]
    modList[numList[0]] = 1
    modListList[0] = modList
    #print(0, modList)

    # for each number figure out possible paths
    for i in range(1,len(numList)):
        currNum = numList[i]
        newModList = [0 for i in range(mod)]

        for k in range(mod):
            if (modList[k] == 1):
                newValue = (currNum + k) % mod
                newModList[newValue] = 1

                newValue = (currNum - k) % mod
                newModList[newValue] = 1

                newValue = (currNum * k) % mod
                newModList[newValue] = 1

        modList = newModList
        modListList[i] = modList
        #print(i, modList)

    assert(modListList[-1][0] == 1)


    # build op list
    opList = [' ' for i in range(len(numList)-1)]
    targetEntry = 0

    for i in range(len(numList)-1,0,-1):
        currNum = numList[i]

        # consider addition. Subtract to find what previous round should 
        #   have produced
        possibleValue = (targetEntry - currNum) % mod
        if (modListList[i-1][possibleValue] == 1):
            targetEntry = possibleValue
            opList[i-1] = '+'
            continue;

        # consider subtraction. Remember we are working backwards
        possibleValue = (targetEntry + currNum) % mod
        if (modListList[i-1][possibleValue] == 1):
            targetEntry = possibleValue
            opList[i-1] = '-'
            continue;

        # consider multiplication. Iterating to find the inverse 
        for k in range(mod): 
            if modListList[i-1][k] == 1:
                newValue = (k * currNum) % mod
                if newValue == targetEntry: 
                    targetEntry = k
                    opList[i-1] = '*'
                    break
        else:
            # exectuted if for loop exits without break
            assert(true)

    assert(targetEntry == numList[0])

    for i in range(len(numList)-1):
        print(numList[i],end='')
        print(opList[i],end='')
    print(numList[-1])



#getAnswer([22,79,21], 101)

ignore = input()
numList = list(map(int,input().split()))
getAnswer(numList, 101)
