# https://www.hackerrank.com/challenges/the-power-sum

def compute(targetNumber,power):

    # This array tracks how many ways we can achieve a given number
    # At start there is 0 ways, except for 0 itself 
    possibilityList = [0 for i in range(targetNumber+1)]
    possibilityList[0]=1

    #print(0, possibilityList)
    # we will break long before we reach targetNumber
    for i in range(1,targetNumber):
        num = i**power
        if num > targetNumber: break

        newList = possibilityList.copy()

        # Add num to old possibilities and calculate new possible
        #  values
        # we only need to process till targetNumber-1
        for j in range(targetNumber):
            if (possibilityList[j] > 0):
                newTotal = j+num
                if newTotal <= targetNumber:
                    newList[newTotal] += possibilityList[j]

        possibilityList = newList
        #print(i, possibilityList)

    return possibilityList[targetNumber]


           

#print(compute(10,2))
X=int(input().strip())
N=int(input().strip())
print(compute(X,N))



