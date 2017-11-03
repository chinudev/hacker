# https://www.hackerrank.com/challenges/fair-cut


def calculateUnfairness(numList, start, end):
    # assumption: numList is sorted in increasing order
    # divide numList into 3 sections 
    #  x= 0..start, k=start..end  and y=end..
    # unfairness = abs(#x - #y)*sum(k) + #k * abs(sum(x) - sum(y))  

    x=numList[:start]
    k=numList[start:end]
    y=numList[end:]

    ans = abs(len(x)*sum(k) - len(k)*sum(x)) + \
          abs(len(k)*sum(y) - len(y)*sum(k))
    #print("in func", ans, x,k,y)
    return ans


def getAnswer(numList,n,k):
    numList.sort()
    if ((n-k) % 2 == 0):
        start = int((n-k)/2)
        end = start+k
        #print("case1",start,end,numList)
        unfairness = calculateUnfairness(numList,start,end)
    else : 
        start = int((n-k)/2)
        end = start+k
        #print("case2",start,end,numList)
        unfairness = min(calculateUnfairness(numList,start,end),
                         calculateUnfairness(numList,start+1,end+1))
    #print("got answer",unfairness)
    return unfairness

assert(2 == (getAnswer([3,3,3,1],4,1)))
assert(6 == (getAnswer([4,3,1,2],4,2)))

(n,k) = list(map(int,input().split()))
numList = list(map(int,input().split())) 
numList.sort()

print(getAnswer(numList,n,k))
