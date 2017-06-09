# https://www.hackerrank.com/challenges/crossword-puzzle

import copy

NUM_ROWS = 10
NUM_COLS = 10

def printCrossword(crossword):
    for row in range(len(crossword)):
        print(''.join(crossword[row]))


def tryFitting(wordList, crossword, acrossList, downList, currentWord, row, col, acrossFlag):

    length = len(currentWord)

    crossword = copy.deepcopy(crossword)
    acrossList = copy.deepcopy(acrossList)
    downList = copy.deepcopy(downList)
    wordList = copy.deepcopy(wordList)


    if acrossFlag == True:
        # Check if this word will fit in crossword
        for wordIndex in range(length):
            if (crossword[row][col+wordIndex] == '-'): continue
            if (crossword[row][col+wordIndex] != currentWord[wordIndex]): 
                return None
        # add word to crossword
        for wordIndex in range(length):
            crossword[row][col+wordIndex] = currentWord[wordIndex]
        return recurseSolve(wordList, crossword, acrossList, downList)

    else:
        # Check if this word will fit in crossword
        for wordIndex in range(length):
            if (crossword[row+wordIndex][col] == '-'): continue
            if (crossword[row+wordIndex][col] != currentWord[wordIndex]): 
                return None
        # add word to crossword
        for wordIndex in range(length):
            crossword[row+wordIndex][col] = currentWord[wordIndex]
        return recurseSolve(wordList, crossword, acrossList, downList)



# returns None if no solution, else the solved cross-word
def recurseSolve(wordList, crossword, acrossList, downList):
    # take first word and try to fit in different possible location

    if len(wordList) == 0: return crossword

    #print("recursing", wordList)
    #printCrossword(crossword)
    currentWord = wordList.pop()

    # try fitting this word in acrossList
    for listIndex in range(len(acrossList)):
        (length, row, col) = acrossList[listIndex]
        #print("trying across {} at ({},{},{})".format(currentWord,length,row,col)); 

        if (length == len(currentWord)):
            # new list without current entry
            newAcross = acrossList[:listIndex] + acrossList[listIndex+1:]  
            solution = tryFitting(wordList,crossword,newAcross,downList,currentWord,row,col,True)
            if solution != None: return solution


    # try fitting this word in downList
    for listIndex in range(len(downList)):
        (length, row, col) = downList[listIndex]
        #print("trying down {} at ({},{},{})".format(currentWord,length,row,col)); 
        if (length == len(currentWord)):

            # new list without current entry
            newDown = downList[:listIndex] + downList[listIndex+1:]  
            solution = tryFitting(wordList,crossword,acrossList,newDown,currentWord,row,col,False)
            if solution != None: return solution


    return None




# brute force 
def solve(wordList, crossword):
    # create two lists for words across and down
    #  for each word slot store (length, row, col)

    acrossList = []
    for row in range(NUM_ROWS):
        col = 0
        while (col < NUM_COLS):
            if (crossword[row][col] == '-'): 
                startCol = col
                while ((col < NUM_COLS) and (crossword[row][col] == '-')):
                    col += 1

                length = col-startCol
                if length > 1:
                    acrossList.append([length, row,startCol])
            col += 1

    downList = []
    for col in range(NUM_COLS):
        row = 0
        while (row < NUM_ROWS):
            if (crossword[row][col] == '-'): 
                startRow = row
                while ((row < NUM_ROWS) and (crossword[row][col] == '-')):
                    row += 1

                length = row - startRow
                if length > 1:
                    downList.append([length, startRow, col])
            row += 1

    assert(len(acrossList) + len(downList) == len(wordList))

    return recurseSolve(wordList, crossword, acrossList, downList)






cword = []
for i in range(NUM_ROWS):
    line = input().strip()
    cword.append(list(line))

wordList = input().strip().split(';')

soln = solve(wordList,cword)
printCrossword(soln)
