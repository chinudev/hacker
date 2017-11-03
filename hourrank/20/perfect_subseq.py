import sys


factorialList=[1,1]
lastFactorial=1
mod = 10**9 + 7

def getFactorial(n):
    for i in range(lastFactorial+1,n+1):
        factorialList[i] = factorialList[i-1]*i % mod
    return factorialList[n]

memoize={}
def computeCombo(a,b):
    a=min(a,b)
    b=max(a,b)
    lookup=str(a)+","+str(b)
    if lookup in memoize:
        return memoize[lookup]

    computeCombo(a,b-1)

    


def countSubs(s):
    countA=0; countB=0
    countC=0; countD=0
    for char in s:
        if char == 'A': countA += 1
        if char == 'B': countB += 1
        if char == 'C': countC += 1
        if char == 'D': countD += 1

    countAB = min(countA,countB)
    countCD = min(countC,countD)
    denom = (getFactorial(countAB) * getFactorial(countCD)) % mod
    return getFactorial(countAB + countCD) / denom

    

# Return the number of non-empty perfect subsequences mod 1000000007
q = int(input().strip())
for a0 in range(q):
    s = input().strip()
    result = countSubs(s)
    print(result)

