#https://www.hackerrank.com/contests/w32/challenges/geometric-trick
import math

class FactorClass:
    # we will be asked to factor a number <= maxN
    def __init__(self, maxN):
        "Create a prime store with primes <= sqrt(maxN)"
        self.maxN = maxN
        self.sqrtN = int(math.sqrt(maxN))
        self.numList = [1 for i in range(0,maxN+1)]
        self.numList[1] = 0

        # mark all non-primes as 0
        for i in range(2,self.sqrtN+1):
            if self.numList[i] == 0: continue
            for j in range(2*i,maxN+1,i): self.numList[j]=0

        # convert prime into a linked list 
        prevPrime=2
        for i in range(3,self.maxN+1):
            if self.numList[i] != 0:
                self.numList[prevPrime]=i
                prevPrime=i



    def isPrime(self, n):
        if n > self.maxN:
            raise Exception("range exceeded")
        return self.numList[n] != 0

    def getFactor(self,n):
        "Return a list of prime factors and their powers for n" 
        " 18 => 2^1*3^2 => [2,1, 3,2] " 

        primeFactors = []
        maxPrimeToTest = int(math.sqrt(n))

        prime = 2
        while (prime <= maxPrimeToTest):
            if (n % prime == 0):
                count = 0
                while (n % prime == 0) : 
                    n = int(n / prime)
                    count=count+1
                primeFactors.append(prime)
                primeFactors.append(count)
            # follow linked list of prime to get next prime
            prime = self.numList[prime]

        if (n != 1) :
            primeFactors.append(n)
            primeFactors.append(1)

        return primeFactors

def testFactor():
    f = FactorClass(5*10**5)
    print("20",f.getFactor(20))
    print("200",f.getFactor(200))
    print("93",f.getFactor(93))
    print("31",f.getFactor(31))



def brute_force(s):
    s="x"+s
    count=0
    for i in range(1,len(s)):
        if (s[i] == 'b'): continue
        if (s[i] == 'a'): rightChar='c'
        else: rightChar='a'

        for j in range(i+1,len(s)):
            if (s[j] != 'b'): continue 
            k = int((j*j)/i)
            if (k*i != j*j): continue 
            assert(k > i+1)
            if (k  >= len(s)): continue

            if (s[k] == rightChar):
                print(i,j,k,s[i],s[j],s[k])
                count += 1

    return count

def brute_force2(s):
    s="x"+s
    factorObj = FactorClass(5*10**5)
    count=0

    for k in range(len(s)-1,0,-1):
        if (s[k] == 'b'): continue
        if (s[k] == 'a'): leftChar='c'
        else: leftChar='a'

        factors = factorObj.getFactor(k)
        delta = 1
        for index in range(1,len(factors),2):
            power=int((factors[index]+1)/2) 
            delta = delta * (factors[index-1] ** power)

        #print(k,delta,factors)

        for j in range(k-delta,0,-delta):
            if (s[j] != 'b'): continue 

            i = int((j*j)/k)
            if (k*i != j*j): continue   # make sure these are even multiples
            if (i  >= j): continue      # skip if i is too big

            if (s[i] == leftChar):
                #print("  match",i,j,k,s[i],s[j],s[k])
                count += 1

    return count



def geometricTrick(s):
    factorObj = FactorClass(5*10**5)
    s="X"+s
    count=0


    for i in range(1,len(s)):
        if s[i] != 'b': continue 

        factors = factorObj.getFactor(i)
        for index in range(1,len(factors),2):
            factors[index] *= 2                # double since we square 
        #print("Found b at ",i,factors)

        # iterate through all divisors 
        # 
        workingFactors=factors.copy()   # make a copy that will change
        workingNumber=i*i
        while True:

            # process this combination
            #print("process",workingNumber, workingFactors)
            if (workingNumber < len(s) and s[workingNumber] == 'a'):
                secondNumber = int(i*i/workingNumber)
                if secondNumber < len(s) and s[secondNumber] == 'c':
                    #print("    found match",workingNumber,i,secondNumber)
                    count += 1

            if workingNumber == 1: 
                break
            
            # pick next combination
            for index in range(1,len(factors),2):
                if workingFactors[index] == 0: continue

                if workingFactors[index] != 0: 
                    workingFactors[index] -= 1
                    workingNumber = int(workingNumber / workingFactors[index-1])
                    for revIndex in range(index-2,0,-2):
                        workingFactors[revIndex] = factors[revIndex]
                        workingNumber =workingNumber * (factors[revIndex-1]**factors[revIndex])
                    break


    return count


#n = int(input().strip())
#s = input().strip()
s="cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca"
#print(brute_force(s))
#print(geometricTrick(s))
#print("expected 154")

s='ccaabbbcccbbaaccccbbbccaaabbabccccabbbbbbbbbbbbbbbb'
print(len(s))
print(brute_force2(s))
print(geometricTrick(s))

s='cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca' \
'cbaababaacccacabcbbabacccbaaccbacccaabaabbaacbbaabcaacabcabaababacbaabacbcccbbcccbcbaaacccccbaacbaacaabcabbaabcaabcababbccbbbabbbacacbcacbbbaabbbbcbabacbbbbaacbbabcacabbbccbbcbacccbcaaabacabccabaaabbcacbcaccbcbbbcabcacacacbccacaaacaccccaaabbaccbaccaccbbbbabbccaabcbaacaaccbccbabacbbaccabcaccbcabcabcbaaaacccaccbcacacbccabababbcaaaacbccaaababacaacabbabccccaabbbababbcbaaabaaaabbbabaaaacabacaacaaaaacaacccaacccbbbbaaabbcaaabccaccacbccbcbabbbbaabbbaacbabbabcaabbabcccabcacbabacccaaccacaacbbcbabbbbcbbcaccbabacbababbaaacbccccccbcabbbababbacacbcaccccacbcaabcbacabaccabccaccbbbacabaaccbaabcbbbcbbbcbccaacabbbcaaaaabbaacbbcabbccacacbaccbbacbbbaccababbbcbcbcbabcabacacaabbbcbaacccbbbaaccccabacabbaabacbccacbccbbacbaaabaccacabaaacaacbccaaaaaccabccbbacaacbccabacaabbbbccabcccbbcbbbacbbbacabcaccabbbaaababaaabbccaacaaaccacacccaacccbccaacabaaacbaacacbcacccabacbbaacaaccccabbaaacaaabbacaccaaccbababaabbccacbcbccaaccbcaabaccbbccacbccaabcbbbaabaababcaaabccbbbcaaccacbcccacaccaccaabbcbcbbbbacaabcbbbcbbbcbccabcbabaca'
#print("len=",len(s))
#print(brute_force(s))
print(geometricTrick(s))
print(brute_force2(s))
print("expected 2256")
