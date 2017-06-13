

def andProduct(num1, num2):

    pow2 = 1 << 31
    prefix = 0
    # express num1 and num2 in binary form. Find the common
    #  prefix sequence

    while 1:
        #print(" iterating {},{}  {}".format(num1,num2,pow2))
        if ((num1 < pow2) and (num2 < pow2)): 
            # this bit pos is zero for both
            pass
        elif ((num1 >= pow2) and (num2 >= pow2)): 
            # this bit pos is one for both
            num1 -= pow2
            num2 -= pow2
            prefix += pow2
        else:
            # found first diff
            break
        pow2 = pow2 >> 1

    return prefix


def test():
    assert(12 == andProduct(12,15))
    assert(2  == andProduct(2,3))
    assert(8  == andProduct(8,13))
    assert(0  == andProduct(15,17))
    assert(0  == andProduct(10,22))


#test()

numTest = int(input())

for i in range(numTest):
    a,b = list(map(int,input().split()))
    print(andProduct(a,b))

