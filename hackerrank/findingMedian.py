
# Given a list of numbers, return media
def findMedian(numList):
    length = len(numList)
    if length % 2 == 1 :   # odd number of elements
        return numList[int((length-1)/2)]
    else:
        return float(numList[int(length/2)] + numList[int(length/2) - 1])/2


def test_findMedian():
    assert(findMedian([2]) == 2)
    assert(findMedian([2,3]) == 2.5)
    assert(findMedian([1,2,3,4,5,6]) == 3.5)



def readAndProcess():
    numEntries = int(input().strip()) 
    numList = []
    while (numEntries > 0):
        numList.append(int(input().strip()))
        numList = sorted(numList)
        print(float(findMedian(numList)))
        numEntries = numEntries - 1


readAndProcess()
