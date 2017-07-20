

MaxN = 8000


def findCount(arr, x, y):
    
    trailingCount = [0 for i in range(MaxN*2+1)]
    zeroOffset = MaxN

    runningCount = 0

    for num in arr:
        trailingCount[zeroOffset] += 1
        if num == x: 
            zeroOffset += 1
        if num == y: 
            zeroOffset -= 1

        runningCount += trailingCount[zeroOffset]

    return runningCount



if __name__ == "__main__":
    n, q = input().strip().split(' ')
    n, q = [int(n), int(q)]
    arr = list(map(int, input().strip().split(' ')))
    for a0 in range(q):
        x, y = input().strip().split(' ')
        x, y = [int(x), int(y)]
        print(findCount(arr, x, y))


