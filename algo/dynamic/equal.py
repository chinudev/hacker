# https://www.hackerrank.com/challenges/equal

# First realize that the operation described is equivalent to reducing 
#  number of chocolates for the selected colleague. So instead of adding to 
#  n-1 colleagues, we can reduce from the selected colleage. 
# Secondly the target will to get all colleagues reduced to be same as minimum
#  colleague, so we can go through each colleague one by one and get them 
#  down to minimum.
# Finally (got this from discussion forum) note that direclty going to minimum
#  colleague is not always the best route. 
#  e.g. 3,7,7. It is better to reduce colleague with 7 to 2, and then reduce 
#    min colleague to 1. 
#  Similarly take example of 4,7,7,7,7. It is better to reduce 7 to 2 and then 
#    reduce 4 to 2. 
#  Forum says we need to try min, min-1, min-2 , min-3, min-4 but I think 
#    min-1 and min-2 is enough.

def getSteps(chocList, target):
    numSteps=0

    #print('For target',target)
    for entry in chocList:
        #print('***',entry,end=' ')

        diff = entry - target
        numSteps += int(diff / 5)   # steps of 5
        #print(numSteps,end=' ')

        diff = diff % 5
        numSteps += int(diff/2)      # steps of 2
        #print(numSteps,end=' ')

        diff = diff % 2
        numSteps += diff             # steps of 1
        #print(numSteps)

    return numSteps


def getMinAnswer(chocList):
    minChoc = min(chocList)
    minAnswer = 2**31              # Init to very large number

    #print("Processing",chocList, " min=", minChoc)
    for i in range(0,3):
        steps = getSteps(chocList, minChoc - i)
        #print("*",i, steps)
        minAnswer = min(minAnswer, steps)
    
    #print("Answer =", minAnswer)

    return minAnswer


        


def test():
    assert(2 == (getMinAnswer([2,2,3,7])));
    assert(7 == (getMinAnswer([4,7,7,7,7,7,7])));
    assert(7 == (getMinAnswer([3,7,7,7,7,7,7])));



numTest = int(input().strip())

for i in range(numTest):
    ignore = input()
    chocList = list(map(int,(input().strip().split())))
    print(getMinAnswer(chocList))


