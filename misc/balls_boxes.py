# https://www.hackerrank.com/contests/w32/challenges/balls-and-boxes
#
import sys
import heapq

class BallStruct:
    def __init__(self, boxId, capacity, inputGrid, colorBallCount):

        self.boxId  = boxId
        self.capacity = capacity
        if capacity > 0: self.penalty = 0
        else:            self.penalty = 2*(1-capacity)-1

        self.ballCountList = colorBallCount # store reference, not copy 

        self.costList = []
        for colorId in range(len(inputGrid)):
            # each entry in costList contains two items
            #   [ cost to add ball of this color , ColorIndex of this color]
            self.costList.append([inputGrid[colorId][boxId], colorId])

        # highest cost item is at end. 
        self.costList.sort()

        # get cost for last time in list and corresponding cost(index 0)
        self.topCost = self.costList[-1][0] - self.penalty


    # return the highest cost to add a new ball
    def getTopCost(self):
        return self.topCost 

    # returns true if element was removed. Element may not be removed 
    #  if there are no more balls of this color
    # 
    def removeCostliest(self, expectedCost):
        removedFlag=False 
        (cost, colorId) = self.costList.pop()
        assert(cost-self.penalty == expectedCost)

        if (self.ballCountList[colorId] > 0):
            # reduce ball count
            self.ballCountList[colorId] -= 1
            self.capacity -= 1 
            #print("Color %d => box %d, cost=%d, penalty=%d" % (colorId,self.boxId,cost,self.penalty)) 
            # compute penalty
            if self.capacity > 0: self.penalty = 0
            else:                 self.penalty = 2*(1-self.capacity)-1
            removedFlag=True

        # pick the next top item
        self.topCost=-1  # in case no more possible balls can be added
        while (self.costList):
            # check if last element's colored ball is available
            (newCost,newColorId) = self.costList[-1]
            if self.ballCountList[newColorId] <= 0: 
                self.costList.pop()
            else:
                # found an entry
                self.topCost = newCost - self.penalty
                break

        return removedFlag

                
            
def testBallStruct():
    # BallStruct(boxId, capacity, inputGrid, colorBallCount):
    grid = [ [4,7], [3,1]]
    colorList = [2,1]

    b1 = BallStruct(1, 1, grid, colorList)
    b0 = BallStruct(0, 0, grid, colorList)

    assert(b0.getTopCost() == 3)   # 4 - 1(penalty)
    assert(b0.removeCostliest(3) == True)
    assert(colorList[0] == 1)
    assert(b0.getTopCost() == 0)   # 3 - 3(penalty)
    assert(b0.removeCostliest(0) == True)
    assert(b0.getTopCost() == -1)  # no more entries

    assert(b1.getTopCost() == 7)   # b1 thinks 7 is best cost for colorId 0 
    colorList[0]=0
    colorList[1]=1                 # change colorList to remove colorId 0
    assert(b1.removeCostliest(7) == False)  # remove should fail
    assert(b1.getTopCost() == 1)   # top cost changed to 1 (colorId=1)
    assert(b1.removeCostliest(1) == False)
    assert(b1.getTopCost() == -1)  # no more balls can be added




#testBallStruct()

n,m = input().strip().split(' ')
numColors,numBoxes = [int(n),int(m)]

ColorBallCount = list(map(int, input().strip().split(' ')))
BoxCapacity = list(map(int, input().strip().split(' ')))

B = []
for B_i in range(numColors):
   B_t = [int(B_temp) for B_temp in input().strip().split(' ')]
   B.append(B_t)

assert(len(B) == numColors)
assert(len(B[0]) == numBoxes)

# Make some additional data structure
    # BallStruct(boxId, capacity, inputGrid, colorBallCount):
boxArray=[]
costHeap = []
for boxId in range(numBoxes):
    boxObj = BallStruct(boxId, BoxCapacity[boxId], B, ColorBallCount)
    boxArray.append(boxObj)
    cost = boxObj.getTopCost()
    if cost > 0: 
        # we want max-heap so use -ve of cost
        heapq.heappush(costHeap, (-cost,boxId)) 

totalCost=0
while costHeap:
    (cost,boxId) = heapq.heappop(costHeap)
    cost=-cost
    boxObj = boxArray[boxId]
    if (boxObj.removeCostliest(cost) == True):
        totalCost += cost

    cost = boxObj.getTopCost()
    if cost > 0: 
        heapq.heappush(costHeap, (-cost,boxId))

print(totalCost)





'''
4 3 
3 1 1 1 
0 0 0 
10 10 10 
8 7 0 
0 8 7 
0 7 0 
Output: 
40
'''

'''
4 3 
3 2 2 1 
1 0 1
10 10 10 
8 7 7
0 8 7 
0 7 0
Output: 
53
'''

