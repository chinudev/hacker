# https://www.hackerrank.com/challenges/the-great-xor/problem

def theGreatXor(a): 

    #print("Handling ",a)
    combos = 0
    foundMSB = False 
    for bitPos in range(63,-1,-1):
        bitMask = 2**bitPos
        bitPresent = bitMask & a
        #print("==",bitMask, bitPresent, foundMSB)
        if (foundMSB == False):
            if (bitPresent):
                foundMSB = True
            continue  

        if (bitPresent == 0): 
            combos += bitMask 

    return combos

def unitTest():
    assert(1 == (theGreatXor(2)))
    assert(5 == (theGreatXor(10)))

unitTest()

q = int(input().strip())
for a0 in range(q):
    x = int(input().strip())
    result = theGreatXor(x)
    print(result)
