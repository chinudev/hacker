

def charIndex(c):
    return ord(c) - ord('a');

def number_needed(str1, str2):

    letterCount = [0 for i in range(26)]

    for c in str1:
        letterCount[charIndex(c)] = letterCount[charIndex(c)] + 1

    for c in str2:
        letterCount[charIndex(c)] = letterCount[charIndex(c)] - 1

    answer=0
    for count in letterCount:
        answer += abs(count)

    return answer



print("abd-def =", number_needed("abd", "def"))
print("aba-radef =", number_needed("aba", "radef"))
