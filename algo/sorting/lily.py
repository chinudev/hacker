# https://www.hackerrank.com/challenges/lilys-homework
import operator
import bisect

def rearrange(numList, reverse) : 
    numList = numList.copy();

    if (reverse): 
        sortOp = operator.gt
    else:
        sortOp = operator.lt 

    numSwaps = 0
    for i in range(len(numList)):
        nextValue = numList[i]
        index = i
        
        for j in range(i+1,len(numList)): 
            if sortOp(numList[j], nextValue):
                nextValue = numList[j]
                index = j

        if index != i:   # swap 
            numList[i],numList[index] = numList[index],numList[i]
            numSwaps += 1

    #print(numSwaps, " = ", numList)

    return numSwaps


# convert numList to refList by doing swaps
def try2(numList):

    refList = numList.copy()
    refList.sort()

    #print("numList = ", numList)
    #print("refList = ", refList)

    # Compute num of swaps to transform to increasing order
    # We iterate in reverse order to make it easier to process index 
    #   returned by bisect
    #
    list1   = numList.copy()
    numSwaps1 = 0
    for i in range(len(list1)-1,-1,-1):

        # if list1[i] == refList[i], things are already in right order
        while list1[i] != refList[i]:

            # Instead of finding out what goes into index i, we will find 
            #   out where list1[i] needs to go. It must be somewhere in 
            #   range (0..i+1). 
            index = bisect.bisect_left(refList[:i+1], list1[i])
            assert(refList[index] == list1[i])

            list1[i],list1[index] = list1[index],list1[i]
            numSwaps1 += 1

    #print(" ascending " , numSwaps1, list1)

    # Compute numSwaps to switch to descending order
    # bisect doesn't work for descending order so doing this in a roundabout
    #   manner
    numSwaps2 = 0
    list2   = numList.copy()

    for i in range(len(list2)):
        idx = len(list2) - 1 - i 

        while list2[i] != refList[idx]:
            index = bisect.bisect_left( refList[:idx+1], list2[i])
            assert(refList[index] == list2[i])
            actualIndex = len(list2) - 1 - index
            #print(i, idx, index, actualIndex, list2, refList )


            list2[i],list2[actualIndex] = list2[actualIndex],list2[i]
            numSwaps2 += 1

    #print(" descending " , numSwaps2, list2)
    #print("answer = ", numSwaps1, numSwaps2)

    return min(numSwaps1, numSwaps2)



def test():
    a = [1,2,3,4,5]
    assert(0 == rearrange(a,False))
    assert(2 == rearrange(a,True))

    assert(0 == try2(a))

    a = [1,2,3,5,4] 
    assert(1 == rearrange(a,False))
    assert(3 == rearrange(a,True))

    assert(1 == try2(a))
    assert(0 == try2([5,4,3,2,1]))
    assert(1 == try2([7,4,0,3]))


#test()

numEntries = int(input())
numList = list(map(int, input().split()))
print(try2(numList))



