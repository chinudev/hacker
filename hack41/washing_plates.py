#https://www.hackerrank.com/contests/101hack41/challenges


import heapq

def quick(costPlus, costMinus,k):
    heap = []
    for index in range(len(costPlus)):
        totalCost = costPlus[index] + costMinus[index]
        heapq.heappush(heap,(-totalCost,index))
        #print("pushed",totalCost,index)

    totalCost=0
    for i in range(len(costPlus)):
        (cost,index) = heapq.heappop(heap)
        if (i < k):
            totalCost += costPlus[index]
            #print('adding',index,totalCost)
        else: 
            totalCost -= costMinus[index]
            #print('substract',index,totalCost)

    if totalCost < 0: totalCost=0
    return totalCost


(n,k) = [int(arr_temp) for arr_temp in input().strip().split(' ')]

costPlus=[]
costMinus=[]
for i in range(n):
    (p,m) = [int(arr_temp) for arr_temp in input().strip().split(' ')]
    costPlus.append(p)
    costMinus.append(m)


print(quick(costPlus,costMinus,k))
 
