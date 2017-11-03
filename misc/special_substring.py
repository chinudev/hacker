# https://www.hackerrank.com/contests/w32/challenges/special-substrings
import timeit


class CompressedTries:
    def __init__(self):
        self.root=[None for i in range(26)]

    def add(self,string):
        return 0
        length=len(string)
        trie = self.root
        for index in range(length):
            letter=ord(string[index]) - ord('a')
            nextTrie=trie[letter]

            if type(nextTrie) == list:
                trie=nextTrie
                # continue to next iteration of for loop
            elif nextTrie == None:
                trie[letter]=string[index:]
                return length-index
            else:
                # trie points to a string
                string=string[index:]
                if nextTrie.find(string) == 0: 
                    return 0
                if string.find(nextTrie) == 0: 
                    trie[letter]=string
                    return len(string) - len(nextTrie)

                string2=nextTrie
                length2=len(string2)
                minLen = min(length, length2)
                for nextIndex in range(minLen):
                    if (string2[nextIndex] == string[nextIndex]):
                        letter=ord(string[nextIndex]) - ord('a')
                        trie[letter] = [None for i in range(26)]
                        trie=trie[letter]
                    else:
                        break

                letter=ord(string[nextIndex]) - ord('a')
                trie[letter] = string[nextIndex:]

                letter2=ord(string2[nextIndex]) - ord('a')
                trie[letter2] = string2[nextIndex:]
                return len(trie[letter])


        # if we came out of for loop, all letters matched existing node
        return 0


def testTrie():
    t = CompressedTries()
    print(t.add('abc'))
    print(t.add('b'))
    print(t.add('ab'))
    print(t.add('abc'))
    print(t.add('bb'))
    print(t.add('bbabcd'))
    print(t.add('bbabde'))


def fastLongestPalindromes(seq):
    """
    Given a sequence seq, returns a list l such that l[2 * i + 1]
    holds the length of the longest palindrome centered at seq[i]
    (which must be odd), l[2 * i] holds the length of the longest
    palindrome centered between seq[i - 1] and seq[i] (which must be
    even), and l[2 * len(seq)] holds the length of the longest
    palindrome centered past the last element of seq (which must be 0,
    as is l[0]).

    The actual palindrome for l[i] is seq[s:(s + l[i])] where s is i
    // 2 - l[i] // 2. (// is integer division.)

    Example:
    naiveLongestPalindrome('ababa') -> [0, 1, 0, 3, 0, 5, 0, 3, 0, 1]

    """
    seqLen = len(seq)
    l = []
    i = 0
    palLen = 0
    # Loop invariant: seq[(i - palLen):i] is a palindrome.
    # Loop invariant: len(l) >= 2 * i - palLen. The code path that
    # increments palLen skips the l-filling inner-loop.
    # Loop invariant: len(l) < 2 * i + 1. Any code path that
    # increments i past seqLen - 1 exits the loop early and so skips
    # the l-filling inner loop.
    while i < seqLen:
        # First, see if we can extend the current palindrome.  Note
        # that the center of the palindrome remains fixed.
        if i > palLen and seq[i - palLen - 1] == seq[i]:
            palLen += 2
            i += 1
            continue

        # The current palindrome is as large as it gets, so we append
        # it.
        l.append(palLen)

        # Now to make further progress, we look for a smaller
        # palindrome sharing the right edge with the current
        # palindrome.  If we find one, we can try to expand it and see
        # where that takes us.  At the same time, we can fill the
        # values for l that we neglected during the loop above. We
        # make use of our knowledge of the length of the previous
        # palindrome (palLen) and the fact that the values of l for
        # positions on the right half of the palindrome are closely
        # related to the values of the corresponding positions on the
        # left half of the palindrome.

        # Traverse backwards starting from the second-to-last index up
        # to the edge of the last palindrome.
        s = len(l) - 2
        e = s - palLen
        for j in range(s, e, -1):
            # d is the value l[j] must have in order for the
            # palindrome centered there to share the left edge with
            # the last palindrome.  (Drawing it out is helpful to
            # understanding why the - 1 is there.)
            d = j - e - 1

            # We check to see if the palindrome at l[j] shares a left
            # edge with the last palindrome.  If so, the corresponding
            # palindrome on the right half must share the right edge
            # with the last palindrome, and so we have a new value for
            # palLen.
            #
            # An exercise for the reader: in this place in the code you
            # might think that you can replace the == with >= to improve
            # performance.  This does not change the correctness of the
            # algorithm but it does hurt performance, contrary to
            # expectations.  Why?
            if l[j] == d:
                palLen = d
                # We actually want to go to the beginning of the outer
                # loop, but Python doesn't have loop labels.  Instead,
                # we use an else block corresponding to the inner
                # loop, which gets executed only when the for loop
                # exits normally (i.e., not via break).
                break

            # Otherwise, we just copy the value over to the right
            # side.  We have to bound l[i] because palindromes on the
            # left side could extend past the left edge of the last
            # palindrome, whereas their counterparts won't extend past
            # the right edge.
            l.append(min(d, l[j]))
        else:
            # This code is executed in two cases: when the for loop
            # isn't taken at all (palLen == 0) or the inner loop was
            # unable to find a palindrome sharing the left edge with
            # the last palindrome.  In either case, we're free to
            # consider the palindrome centered at seq[i].
            palLen = 1
            i += 1

    # We know from the loop invariant that len(l) < 2 * seqLen + 1, so
    # we must fill in the remaining values of l.

    # Obviously, the last palindrome we're looking at can't grow any
    # more.
    l.append(palLen)

    # Traverse backwards starting from the second-to-last index up
    # until we get l to size 2 * seqLen + 1. We can deduce from the
    # loop invariants we have enough elements.
    lLen = len(l)
    s = lLen - 2
    e = s - (2 * seqLen + 1 - lLen)
    for i in range(s, e, -1):
        # The d here uses the same formula as the d in the inner loop
        # above.  (Computes distance to left edge of the last
        # palindrome.)
        d = i - e - 1
        # We bound l[i] with min for the same reason as in the inner
        # loop above.
        l.append(min(d, l[i]))

    return l


def testPalindrome():
    s='abcabba'
    l = fastLongestPalindromes(s)
    print(s)
    print(l)



def computeResult(string):
    # is sub-string starting at index i palindrome 
    palindromeArray=[False for i in range(len(string))]
    totalValue=0
    trie = CompressedTries()

    resultArray=[]
    for i in range(len(string)):

        # count down for j since we larger sub-string use value of smaller sub-string
        #  from previous round
        for j in range(i+1):

            #check if string [j:i] is a palindrome
            if ((i==j)                      # one letter string is palindrome 
                 or 
                 ((string[i] == string[j])  # make sure ends of string are same
                   and
                   ( (i-j<3)                # if len of sub-string <=3  
                     or 
                     (palindromeArray[j+1]==1)) # check if string[j+1,i-1] is palindrome
                 )
               ):
                palindromeArray[j]=1
                value=trie.add(string[j:i+1])
                totalValue += value
                #print("   palindrome",value, string[j:i+1])

            else:
                # not palindrome. Set to 0 in case this was 
                #  a palindrome before e.g. string[j,i-1]
                palindromeArray[j]=0
            
        #print(totalValue)
        resultArray.append(totalValue)

    return resultArray



test='bccbbbbc'
bigTest=test
for i in range(1):
    bigTest += test
print("bigTest length=",len(bigTest))


#testTrie()
#testPalindrome()

l = fastLongestPalindromes(bigTest)
print(l)

exit()

#computeResult('bccbbbbc')

# 39 tests
# first 9 pass, 10-19 timeout. 20-39 will be end of day

#result=computeResult(bigTest)
print(timeit.timeit('computeResult(bigTest)',setup="from __main__ import computeResult,bigTest",number=1))
#print ("\n".join(map(str, result)))

# ~9 sec to handle a 8000 char string. Trie introduces .4 sec so not the big contributor

