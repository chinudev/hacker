# https://www.hackerrank.com/contests/w34/challenges/maximum-gcd-and-sum
import math

MaxN = 10**6 


def findMaxGcd(listA, listB):

    maxA = 0
    dictA = [0 for i in range(MaxN+1)]
    for num in listA:
        maxA = max(num,maxA)
        dictA[num]=1

    maxB = 0
    dictB = [0 for i in range(MaxN+1)]
    for num in listB:
        maxB = max(num,maxB)
        dictB[num]=1

    maxNumber = max(maxA, maxB)
    maxPossibleGcd = min(maxA, maxB)

    for maxGcd in range(maxPossibleGcd,2,-1):
        matchedA = False
        matchedB = False

        for gcdMultiple in range(maxGcd, maxNumber+1, maxGcd):
            if (matchedA == False) and dictA[gcdMultiple]:
                    matchedA = True
                    maxMatchA = gcdMultiple
                    for num in range(gcdMultiple, maxNumber+1, maxGcd):
                        if (dictA[num]):
                            maxMatchA = num

                    if matchedB:
                        #print(maxGcd, maxMatchA+maxMatchB)
                        return maxMatchA + maxMatchB

            if matchedB == False:
                if dictB[gcdMultiple]:
                    matchedB = True
                    maxMatchB = gcdMultiple
                    for num in range(gcdMultiple, maxB+1, maxGcd):
                        if (dictB[num]):
                            maxMatchB = num

                    if matchedA:
                        #print(maxGcd, maxMatchA+maxMatchB)
                        return maxMatchA + maxMatchB


    # if we fall here, max gcd is 1
    return maxA + maxB 
    

def unitTest():

    print(findMaxGcd([8,4,3,2,1],[12,8,5,3,2]))
    #findMaxGcd([12,8,5,3,2],[8,4,3,2,1])
    #findMaxGcd([12,8,5,3,2],[12,8,5,3,2])


#unitTest()

if __name__ == "__main__":
    n = int(input().strip())
    A = list(map(int, input().strip().split(' ')))
    B = list(map(int, input().strip().split(' ')))
    res = findMaxGcd(A, B)
    print(res)


