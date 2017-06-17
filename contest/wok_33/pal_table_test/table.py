# generate test for pal_table.cpp

import random

#print("Enter number of rows and cols and press enter e.g. 10 10 ")
numRows, numCols = list(map(int,input().split()))

print(numRows, numCols);

for i in range(numRows):
    #numList = [str(random.randint(0,9)) for k in range(numCols)]
    numList = ['0' for k in range(numCols)]
    print(' '.join(numList))
