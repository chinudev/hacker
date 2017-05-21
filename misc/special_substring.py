# https://www.hackerrank.com/contests/w32/challenges/special-substrings


class CompressedTries:
    def __init__(self):
        self.root=[None for i in range(26)]

    def add(self,string):
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




class SubstringSet:
    def __init__(self):
        self.dict = dict()

    def add(self, string):
        length = len(string)
        index = length

        while (index >= 0): 
            if string[0:index] in self.dict:
                break
            index -= 1
        # if no match found, index=-1
        # if first letter matched, index=0
        costAdder = length-index-1

        # add missing string into dict
        for i in range(index+1,length):
            self.dict[ string[0:i+1]]=1

        return costAdder


    def print(self):
        print(sorted(self.dict.keys()))




def computeResult(string):
    # is sub-string starting at index i palindrome 
    palindromeArray=[False for i in range(len(string))]
    palindromeSet=SubstringSet()

    totalValue=0
    trie = CompressedTries()

    for i in range(len(string)):
        print("round ",i);

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
                print("   palindrome",value, string[j:i+1])
                palindromeSet.add(string[j:i+1])

            else:
                # not palindrome. Set to 0 in case this was 
                #  a palindrome before e.g. string[j,i-1]
                palindromeArray[j]=0
            
        #palindromeSet.print()
        print("**Value=",totalValue)





#testTrie()
computeResult('bccbbbbc')

