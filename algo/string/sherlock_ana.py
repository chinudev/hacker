# https://www.hackerrank.com/challenges/sherlock-and-anagrams

from math import factorial

# returns an array with count of each letter found in string
#   assumption : inputStr contains only lower case english characters 
def letterCount(inputStr):
    countList = [0 for i in range(26)]
    for c in inputStr:
        num = ord(c) - ord('a')
        assert(num < 26)
        countList[num] += 1
    return str(countList)


def getAnagramPairCount(inputStr):

    anagramDict = {}
    # go through every possible sub-string [i:j]
    #   remember sub-string includes i but not j
    for i in range(len(inputStr)):
        for j in range(i+1,len(inputStr)+1):
            #print(inputStr[i:j])
            countStr = letterCount(inputStr[i:j])
            if (countStr in anagramDict):
                anagramDict[countStr] += 1
            else:
                anagramDict[countStr] = 1

    totalCombos = 0
    for countStr, count in anagramDict.items():
        if (count> 1):
            combos = factorial(count)/(factorial(count-2)*factorial(2))
            totalCombos += int(combos)
            #print(countStr,count, combos)

    return totalCombos


def unitTest():
    assert(4 == getAnagramPairCount("abba"))
    assert(0 == getAnagramPairCount("abcd"))

    assert(3 == getAnagramPairCount("ifailunkqq"))
    assert(2 == getAnagramPairCount("hucpoltgty"))
    assert(2 == getAnagramPairCount("ovarjsnrbf"))
    assert(6 == getAnagramPairCount("pvmupwjjjf"))
    assert(3 == getAnagramPairCount("iwwhrlkpek"))


#unitTest()

q = int(input().strip())
for a0 in range(q):
    s = input().strip()
    result = getAnagramPairCount(s)
    print(result)

