#!/bin/python3
import sys



def circularWalk(numNodes, start, dest, r_0, g, seed, p):

    if start == dest: return 0

    # Complete this function
    jumpTable = [0 for i in range(numNodes)]

    # populate the jump table
    jumpTable[0] = r_0
    for i in range(1,numNodes):
        jumpTable[i] = (jumpTable[i-1]*g + seed) % p

    # do bread-first search starting from "start" 
    #   once we have visited a node we will set its jumpTable entry to 
    #   zero => it won't be explored further.
    exploreList = [start]
    jumpCount=1
    while (exploreList):
        newExploreList = []

        for entry in exploreList:
            assert(entry != dest)   # dest shouldn't be in exploreList

            if jumpTable[entry] == 0: next

            distToDest = abs(entry - dest)
            if (distToDest > numNodes/2) : distToDest = numNodes - distToDest
            if distToDest < jumpTable[entry]: 
                return jumpCount+1
            
            for offset in range(-jumpTable[entry],jumpTable[entry]+1):
                if offset == 0: next
                newIndex = (entry+offset) % numNodes
                if newIndex == dest:
                    return jumpCount

                if jumpTable[newIndex] != 0:
                    newExploreList.append(newIndex)

            # mark this node as explored
            jumpTable[entry]=0

        exploreList = newExploreList
        jumpCount += 1

    return -1 

    


n, s, t = input().strip().split(' ')
n, s, t = [int(n), int(s), int(t)]
r_0, g, seed, p = input().strip().split(' ')
r_0, g, seed, p = [int(r_0), int(g), int(seed), int(p)]
result = circularWalk(n, s, t, r_0, g, seed, p)
print(result)
