import heapq

# Simple wrapper around heapq
class MinHeap: 
    def __init__(self):
        self.heap = []

    def push(self,value):
        heapq.heappush(self.heap,value)

    def pushpop(self,value):
        return heapq.heappushpop(self.heap,value)

    def len(self):
        return len(self.heap)

    def topElem(self): 
        return self.heap[0]

class MaxHeap:
    def __init__(self):
        self.heap = []

    def push(self,value):
        heapq.heappush(self.heap,-1*value)

    def pushpop(self,value):
        retValue = heapq.heappushpop(self.heap,-1*value)
        return (retValue*-1)

    def len(self):
        return len(self.heap)

    def topElem(self): 
        return -1*self.heap[0]


# Imagine the list of number is split into two groups
# around the midpoint. 
# Left half is stored in a MaxHeap so we can find the largest number 
#  in the left half. 
# Right half is stored in a MinHeap so we can find the smallest number quickly.
# When number of element is even, both heap are same length. When count is odd,
#  left half (MaxHeap) will have one more element than right half.
#  
class MedianFinder:
    def __init__(self):
        self.minHeap = MinHeap()
        self.maxHeap = MaxHeap()
        self.length = 0

    def push(self,value):
        if self.length == 0:
            self.maxHeap.push(value)
            self.length=1
            return


        self.length = self.length + 1
        if self.length % 2 == 1:
            # Need to grow left half (MaxHeap)
            # First check if we need to put this value in right half (MinHeap)
            #   and get a replacement 
            if value > self.minHeap.topElem():
                value = self.minHeap.pushpop(value)
            self.maxHeap.push(value)

        else:
            # Need to grow right half
            if value < self.maxHeap.topElem():
                value = self.maxHeap.pushpop(value)
            self.minHeap.push(value)

    def getMedian(self):
        if self.length % 2 == 1:
            return float(self.maxHeap.topElem())
        else:
            return float(self.maxHeap.topElem() + self.minHeap.topElem()) / 2


def testMax():
    maxHeap = MaxHeap()

    maxHeap.push(10)
    assert(maxHeap.topElem() == 10)
    maxHeap.push(20)
    assert(maxHeap.topElem() == 20)
    maxHeap.push(5)
    assert(maxHeap.topElem() == 20)
    maxHeap.push(20)
    assert(maxHeap.topElem() == 20)
    assert(maxHeap.pushpop(6) == 20)
    assert(maxHeap.pushpop(22) == 22)
    assert(maxHeap.len() == 4)

def testMin():
    minHeap = MinHeap()

    minHeap.push(10)
    assert(minHeap.topElem() == 10)
    minHeap.push(20)
    assert(minHeap.topElem() == 10)
    minHeap.push(5)
    assert(minHeap.topElem() == 5)
    minHeap.push(5)
    assert(minHeap.topElem() == 5)
    assert(minHeap.pushpop(20) == 5)
    assert(minHeap.pushpop(2) == 2)
    assert(minHeap.len() == 4)



def readAndProcess():
    medianFinder = MedianFinder()

    numEntries = int(input().strip()) 
    numList = []
    while (numEntries > 0):
        medianFinder.push(int(input().strip()))
        print(medianFinder.getMedian())
        numEntries = numEntries - 1


readAndProcess()

