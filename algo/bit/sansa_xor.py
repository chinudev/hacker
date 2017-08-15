# https://www.hackerrank.com/challenges/sansa-and-xor/problem


numTest = int(input())

for i in range(numTest):
    n = int(input())
    numList = list(map(int,input().split()))

    # number of times ith element occurs in contiguous sub-arrays is 
    #  (n-i)(i+1). 
    xorNum = 0
    for i in range(n):
        numOccur = (n-i)*(i+1)
        if (numOccur % 2):
            xorNum = xorNum ^ numList[i]

    print(xorNum)
    
