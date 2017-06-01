

(a1,a2,n)=[int(c) for c in input().split()]

if (n == 1): 
    print(a1)
    exit()
if (n == 2): 
    print(a2)
    exit()

# a3 = a2**2 + a1 
for i in range(n-2):
    a3 = a2**2+a1
    a1=a2
    a2=a3

print(a3)
