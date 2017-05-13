

def getWaysSimple(n,c): 

    numWays = [0 for i in range(n+1)]
    numWays[0]=1

    # To start with assume there is only one type of coin and find
    #  all possible values that can be realized with it. All possible value
    #  will have only one combination at this stage. 
    # Then add another coin value and figure out how many new combination 
    #  values can be added. 
    # 
    for coin in c:
        for i in range(n+1-coin):
            numWays[i+coin] += numWays[i]
        
    return numWays[n]

# This is the first approach I thought off but it didn't work very well
#  
def getWays(n,coinList):

    coinList.sort()
    cache=[[-1 for minCoinIndex in range(len(coinList))] for value in range(n+1)]
    for coinIndex in range(len(coinList)):
        cache[0][coinIndex]=1;

    # this routine will use function variables : cache and coinList
    # figure out possible ways to compute n given you are not allowed to 
    #  use any coin below coinList[minCoinIndex]
    def recurseGetWays(n, minCoinIndex):
        if (cache[n][minCoinIndex] != -1):
            return cache[n][minCoinIndex];
        
        numWays=0
        for coinIndex in range(minCoinIndex,len(coinList)):
            coinValue = coinList[coinIndex]
            if (coinValue > n): break
            numWays += recurseGetWays(n-coinValue, coinIndex)

        cache[n][minCoinIndex]=numWays

        return numWays

    return recurseGetWays(n,0)


n=10
c=[2,5,3,6]
print(getWays(n,c))
