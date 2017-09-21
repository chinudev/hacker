# https://www.hackerrank.com/challenges/missing-numbers/problem

def findMissingNumbers(listA,listB):
    if (len(listB) <= 0): return []
    minB = listB[0]
    for elemB in listB:
        minB = min(minB,elemB)

    countList = [0 for i in range(100)]
    for elemB in listB:
        countList[elemB-minB] += 1

    for elemA in listA:
        countList[elemA-minB] -= 1

    answerList = []
    for i in range(100):
        if (countList[i] > 0):
            answerList.append(i+minB)
    return answerList



countA = int(input())
listA =  list(map(int,input().strip().split()))
countB = int(input())
listB =  list(map(int,input().strip().split()))

answer = findMissingNumbers(listA,listB)
print(" ".join(map(str,answer)))


