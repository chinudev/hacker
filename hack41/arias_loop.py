#https://www.hackerrank.com/contests/101hack41/challenges/arias-loops





(n,k) = [int(arr_temp) for arr_temp in input().strip().split(' ')]

mod=10**9+7
total=0

# start from index 1, instead of 0
#  one extra at end to help in math
lowerLayer=[n-i+1 for i in range(n+2)]

#print("layer",k, " = ",lowerLayer)

# start from bottom loop/layer and move up 
for layer in range(k-1,0,-1):

    currentLayer=[0 for i in range(n+2)]
    layerMin = int(layer*(layer-1)/2)+1

    # start from last iteration(n) and compute
    for j in range(n,layerMin-1,-1):
    #for j in range(n,0,-1):
        if (j+layer <= n):
            currentLayer[j]= (currentLayer[j+1]+lowerLayer[j+layer]) % mod
            #currentLayer[j]= (currentLayer[j+1]+lowerLayer[j+layer]) 

    #print("layer",layer, " = ",currentLayer)
    lowerLayer=currentLayer

print(lowerLayer[1])

    


 
