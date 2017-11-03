# https://www.hackerrank.com/challenges/lego-blocks


cache = [-1 for i in range(1001)]
MOD = 1000000007

def numCombos(width):
    if (width < 0): return 0
    if (width == 0): return 1
    if (cache[width] > -1): return cache[width]

    combos = numCombos(width-1) + \
             numCombos(width-2) + \
             numCombos(width-3) + \
             numCombos(width-4)

    cache[width] = combos % MOD
    return combos
    

def blockCombos(height, width):
    combos = numCombos(width)

    # Calculate total combos for all layers about first one
    totalCombos = 1
    for i in range(height-1):  
        totalCombos = (totalCombos * combos) % MOD

    # special handling for the last layer to avoid a stragiht vertical line
    totalCombos = combos * (totalCombos - 1)  

    if (width <= 4): totalCombos += 1

    print(" {},{} = {} {}".format(height,width,totalCombos,combos))
    return totalCombos


def test():
    assert(1 == blockCombos(10,1))
    assert(3 == blockCombos(2,2))
    assert(7 == blockCombos(3,2))
    assert(9 == blockCombos(2,3))
    assert(3375 == blockCombos(4,4))



test()

numTest = int(input())
for i in range(numTest):
    (height, width) = list(map(int,input().split()))

