str = input().strip()
keepLooping=True

while (keepLooping):
    keepLooping=False
    for i in range(len(str)-1):
        if (str[i] == str[i+1]):
            str = str[:i] + str[i+2:]
            keepLooping=True
            break

if str == '': 
    print('Empty String')
else:
    print(str)
