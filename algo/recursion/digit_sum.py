#https://www.hackerrank.com/challenges/recursive-digit-sum

def digitSum(numStr):
    digitSum=0
    for digit in numStr:
        digitSum += int(digit)
    return digitSum


def superDigit(num):
    while (num > 10):
        num=digitSum(str(num))
    return num



(numStr, k) = input().split()
number=digitSum(numStr)*int(k)
print(superDigit(number))


