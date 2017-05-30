#https://www.hackerrank.com/challenges/bigger-is-greater


# this maps 'a' to 0, 'b' to 1, .. 'z' to 25
LetterMap = {chr(c+ord('a')): c for c in range(26)}

def findAnswer(inStr):

    #print("Testing ",inStr)
    '''
    # track largest index where this letter can be found.
    letterPos = [-1 for i in range(26)]
    for i in range(len(inStr)):
        letterPos[LetterMap[inStr[i]]]=i

    # find maxLeftPos to swap for each letter
    # For each letter, find largest index for all characters smaller than this letter 
    maxLeftPos = [-1 for i in range(26)]
    maxCharIndexSoFar=-1
    for i in range(26):
        maxLeftPos[i] = maxCharIndexSoFar
        if letterPos[i] > maxCharIndexSoFar:
            maxCharIndexSoFar = letterPos[i]
    '''

    # scan string from right to left. 
    #   find a char to left of it that can be used for swapping
    #   Pick the best e.g.  acdb : c,d swap is better than a,b swap
    #
    maxSwap_LeftCharIndex  = -1
    maxSwap_RightCharIndex = -1

    for rightIndex in range(len(inStr)-1,0,-1):
        if rightIndex <= maxSwap_LeftCharIndex: 
            #print("   break condition")
            break
        
        # go from right to left looking for a letter lower than this one
        #  no point in looking further left than the previous max position 
        for leftIndex in range(rightIndex-1,maxSwap_LeftCharIndex,-1):
            if inStr[leftIndex] < inStr[rightIndex]:
                maxSwap_LeftCharIndex  = leftIndex
                maxSwap_RightCharIndex = rightIndex
                #print("       updated ",maxSwap_LeftCharIndex ,maxSwap_RightCharIndex)
                break

    if maxSwap_LeftCharIndex == -1:
        return "no answer"

    assert(maxSwap_LeftCharIndex < maxSwap_RightCharIndex)

    # everything to left of left char swap position
    leftStr = inStr[:maxSwap_LeftCharIndex]

    midChar = inStr[maxSwap_RightCharIndex]

    # everything to right of left-char-swap position, including left char 
    #  but excluding right char
    rightStr = inStr[maxSwap_LeftCharIndex:maxSwap_RightCharIndex] + inStr[maxSwap_RightCharIndex+1:] 

    return leftStr+midChar+''.join(sorted(rightStr));


def test():
    assert(findAnswer('ab') == 'ba')
    assert(findAnswer('bb') == 'no answer')
    assert(findAnswer('hefg') == 'hegf')
    assert(findAnswer('dhck') == 'dhkc')
    assert(findAnswer('dkhc') == 'hcdk')
    assert(findAnswer('aba') == 'baa')
    assert(findAnswer('acdb') == 'adbc')


#test()
numTest = int(input().strip())
for i in range(numTest):
    inStr = input().strip()
    print(findAnswer(inStr))
