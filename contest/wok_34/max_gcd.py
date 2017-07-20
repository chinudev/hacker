# https://www.hackerrank.com/contests/w34/challenges/maximum-gcd-and-sum
import math

MaxN = 10**6 

class PrimeStore:
    def __init__(self, maxN):
        "Create a prime store with primes <= sqrt(maxN)"

        self.maxN = maxN
        self.numList = [1 for i in range(0,maxN+1)]
        self.numList[1] = 0

        prevPrime = 1

        for i in range(2,int(math.sqrt(maxN))+1):
            if self.numList[i] == 0:
                continue

            # this number is a prime 
            self.numList[prevPrime] = i   # create a linked list of prime
            prevPrime = i

            for j in range(2*i,maxN+1,i):
                self.numList[j]=0

    def isPrime(self, n):
        if n > self.maxN: raise Exception("range exceeded")

        return self.numList[n] > 0

    def findFactors(self,n):
        if n > self.maxN: raise Exception("range exceeded")

        factorDict = dict()
        maxPrimeToTest = int(math.sqrt(n))
        prime = self.numList[1]

        while prime <= maxPrimeToTest:
            if (n % prime == 0) : 
                count = 0
                while (n % prime == 0) : 
                    n = n / prime
                    count=count+1
                factorDict[prime] = count
                maxPrimeToTest = int(math.sqrt(n))

            # pick next prime
            prime = self.numList[prime]

        if (n != 1): 
            factorDict[n] = 1

        return factorDict

            


PStore = PrimeStore(MaxN)


def findGcd(dictA, dictB):
    gcd = 1
    for prime,countA in dictA.items():
        if prime in dictB:
            countB = dictB[prime]
            count = min(countA,countB)
            gcd = gcd * (prime**count)
    return gcd


def findMaxGcd(listA, listB):

    listA.sort(reverse=True)
    listB.sort(reverse=True)

    # use the list with smallest maxNum to prepare divisorList
    if (listA[0] > listB[0]):
        listA,listB = listB,listA

    # Use listA to create list of possible GCD
    maxA = listA[0]

    factorDictForA = []

    for numA in listA:
        factorDictForA.append((numA,PStore.findFactors(numA)))


    # Go through listB 
    maxGcd = 0
    maxGcdSum = 0

    for numB in listB:
        if (numB <= maxGcd): break
        dictB = PStore.findFactors(numB)

        for (numA,dictA) in factorDictForA:
            if (numA < maxGcd): break
            gcd = findGcd(dictA, dictB)
            if (gcd > maxGcd):
                maxGcd = gcd
                maxGcdSum = numA + numB
            elif (gcd == maxGcd):
                maxGcdSum = max(maxGcdSum, numA + numB)


    #print(maxGcd, maxGcdSum)
    return maxGcdSum
    

def unitTest():
    assert(PStore.findFactors(10) == {2:1, 5:1})
    assert(PStore.findFactors(7) == {7:1})
    assert(PStore.findFactors(64) == {2:6})
    assert(PStore.findFactors(98) == {2:1,7:2})

    findMaxGcd([8,4,3,2,1],[12,8,5,3,2])
    #findMaxGcd([12,8,5,3,2],[8,4,3,2,1])
    #findMaxGcd([12,8,5,3,2],[12,8,5,3,2])


unitTest()

if __name__ == "__main__":
    n = int(input().strip())
    A = list(map(int, input().strip().split(' ')))
    B = list(map(int, input().strip().split(' ')))
    res = findMaxGcd(A, B)
    print(res)


