

n, k = map(int, input().strip().split(' '))
a = list(map(int, input().strip().split(' ')))

assert(len(a) == n)

index = k % n         

for i in range(n):
    print(a[index],' ',end="")
    index = (index +1) % n

print('')
