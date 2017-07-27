#https://www.hackerrank.com/challenges/richie-rich/problem



# convert numStr to palindrom with at most "k" changes
def getMax(numStr,k):
    # do one pass to find minimum k needed
    n = len(numStr)
    minK=0 
    # No need to check mid elem for odd-length string
    for i in range(int(n/2)):  
        if (numStr[i] != numStr[n-i-1]): 
            minK += 1

    if (minK > k): 
        return "-1"

    numList = list(numStr)
    extraMoves = k - minK
    #print(k,minK,extraMoves,numList)
    # change outermost numbers to 9, if we can affort to
    for i in range(int(n/2)):  
        # using max with char but it works as expected
        maxElem = max(numList[i],numList[n-i-1])

        # if both digit are same, check if we can change both to '9'
        if (numList[i] == numList[n-i-1]):
            if ((maxElem != '9') and (extraMoves > 1)):
                numList[i]     = '9'
                numList[n-i-1] = '9'
                extraMoves -= 2

        else:
            if (maxElem == '9'):
                numList[i]     = '9'
                numList[n-i-1] = '9'
            else:
                if (extraMoves > 0): 
                    numList[i]     = '9'
                    numList[n-i-1] = '9'
                    extraMoves -= 1
                else:
                    numList[i]     = maxElem
                    numList[n-i-1] = maxElem



    # handle mid elem outside the loop
    if ((n % 2) and (extraMoves > 0)): 
        midElem = int(n/2)
        numList[midElem] = '9'

    return "".join(numList)


def test():
    assert("3993" == getMax("3943",1))
    assert("992299"  == getMax("092282",3))
    assert("9921299" == getMax("0921282",3))
    assert("9929299" == getMax("0921282",4))
    assert("-1" == getMax("0011",1))



#test()

(n,k) = list(map(int,input().strip().split()))
s = input().strip()
result = getMax(s, k)
print(result)

