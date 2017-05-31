#https://www.hackerrank.com/challenges/two-characters

def checkAlternate(string,a,b):
    if (a == b): return False

    expected=''
    count=0
    for char in string:
        if char == a:
            if expected == b: return -1
            expected = b
            count += 1
        elif char == b:
            if expected == a: return -1
            expected = a
            count += 1
        else:
            pass   # ignore other chars

    return count


def test():
    assert(checkAlternate("ab","a","b") == 2)
    assert(checkAlternate("aba","b","a") == 3)
    assert(checkAlternate("abab","a","b") == 4)
    assert(checkAlternate("adbncacb","a","b") == 4)

    assert(checkAlternate("aa","a","b") == -1)
    assert(checkAlternate("abaa","a","b") == -1)

test()

s = input().strip()
charSet = list(set(s))

maxLength=0
for i in range(len(charSet)):
    for j in range(i+1,len(charSet)):
        length = checkAlternate(s,charSet[i],charSet[j])
        maxLength = max(length, maxLength)

print(maxLength)


