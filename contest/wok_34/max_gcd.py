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

        factorList = []
        maxPrimeToTest = int(math.sqrt(n))
        prime = self.numList[1]

        while prime <= maxPrimeToTest:
            if (n % prime == 0) : 
                count = 0
                while (n % prime == 0) : 
                    n = n / prime
                    count=count+1
                factorList.append(prime)
                maxPrimeToTest = int(math.sqrt(n))

            # pick next prime
            prime = self.numList[prime]

        if (n != 1): 
            factorList.append(int(n))

        return factorList

            


PStore = PrimeStore(MaxN)


def findMaxGcd(listA, listB):

    listA.sort(reverse=True)
    listB.sort(reverse=True)

    # use the list with smallest maxNum to prepare divisorList
    if (listA[0] > listB[0]):
        listA,listB = listB,listA

    # Use listA to create list of possible GCD
    maxA = listA[0]
    DivisorList = [0 for i in range(maxA+1)]

    for num in listA:
        if DivisorList[num] > 0: continue     # already handled

        for factor in reversed(PStore.findFactors(num)):
            if DivisorList[factor] > 0:  continue

            for value in range(factor,num+1,factor):
                if (num % value == 0):
                    DivisorList[value] = num 


    # Go through listB 
    maxGcd = 0
    maxGcdSum = 0

    for num in listB:
        if (num < maxGcd): break

        if num <= maxA and DivisorList[num] > 0:
            # num must be greater than maxGcd and next number will be lower than this
            maxGcd = num             
            maxGcdSum = DivisorList[num] + num
            break

        for factor in reversed(PStore.findFactors(num)):
            if DivisorList[factor] == 0:  continue
            if (factor > maxA): continue

            for value in range(num,0,-factor):  # go backwards
                if (value <= maxGcd): break
                if (value > maxA): continue

                if (num % value == 0):
                    if DivisorList[value] > 0:  
                        maxGcd = value
                        maxGcdSum = DivisorList[value] + value
                        break

    #print(maxGcd, maxGcdSum)
    return maxGcdSum
    

def unitTest():
    assert(PStore.findFactors(10) == [2,5])
    assert(PStore.findFactors(7) == [7])
    assert(PStore.findFactors(64) == [2])
    assert(PStore.findFactors(98) == [2,7])

    findMaxGcd([8,4,3,2,1],[12,8,5,3,2])
    findMaxGcd([12,8,5,3,2],[8,4,3,2,1])
    findMaxGcd([12,8,5,3,2],[12,8,5,3,2])


#unitTest()

if __name__ == "__main__":
    n = int(input().strip())
    A = list(map(int, input().strip().split(' ')))
    B = list(map(int, input().strip().split(' ')))
    res = findMaxGcd(A, B)
    print(res)


