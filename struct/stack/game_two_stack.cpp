#include <stdint.h>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;


uint64_t findMax(const vector<uint64_t>& vectorA,
                 const vector<uint64_t>& vectorB,
                 uint64_t maxSum) 
{
    // track max number of elements that add up to less than maxSum
    uint64_t maxElems=0;

    uint64_t currentSum=0;
    int indexA,indexB;

    // Add up leading elements until sum is just under maxSum
    // We may exit loop with no elements selected from vectorA or
    //   with all elements selected
    for (indexA=0; indexA < vectorA.size(); indexA++) {
        currentSum += vectorA[indexA];
        if (currentSum > maxSum) {
            currentSum -= vectorA[indexA]; 
            break;
        }
    }

    maxElems = indexA; 
    indexA--;   // indexA is now pointing to last value added
                // if indexA==-1, nothing was added

    // Start adding elements from vectorB
    for (indexB=0; indexB < vectorB.size(); indexB++) {

        currentSum += vectorB[indexB];

        if (currentSum > maxSum) {
            // The previous iteration had sum less than maxSum. 
            //  check if that qualifies as having max elements
            int numElems = indexA+1 + indexB;
            if (numElems > maxElems) maxElems = numElems; 

            // lower value by removing elements from vectorA
            while ((currentSum > maxSum) && (indexA >= 0)) {
                currentSum -= vectorA[indexA];
                indexA--;
            }

            // No point in adding any more elements from vector B
            if ((currentSum > maxSum) && (indexA < 0)) break;
        }
    }

    // final check to ensure we cover the case when all elements of
    //  vectorB are used without going over maxSum
    if (currentSum <= maxSum) {
        int numElems = indexA+1 + indexB;
        if (numElems > maxElems) maxElems = numElems; 
    }

    return maxElems;
}

void testMax() 
{
    // no match 
    assert(findMax({}, {}, 0) == 0);  
    assert(findMax({2,1}, {2,3}, 1) == 0);  

    // match left side
    assert(findMax({2,1}, {2,3}, 2) == 1); 
    assert(findMax({2,1}, {2,3}, 3) == 2);
    assert(findMax({2,1}, {}, 3) == 2);

    // match right side
    assert(findMax({8,2}, {1,1}, 1) == 1);
    assert(findMax({8,2}, {1,1}, 2) == 2);
    assert(findMax({8,2}, {1,1}, 3) == 2);

    assert(findMax({5,4}, {5,4}, 9) == 2);
    assert(findMax({5,4}, {5,4}, 18) == 4);
}

int main()
{

    testMax();

    int numGames; 
    cin >> numGames; 
    for (; numGames > 0; numGames--) {
        int numElemA, numElemB;
        uint64_t maxSum;

        cin >> numElemA >> numElemB >> maxSum;

        vector<uint64_t> vectorA;
        vector<uint64_t> vectorB;

        for (; numElemA > 0; numElemA--) {
            uint64_t elem;
            cin >> elem;
            vectorA.push_back(elem);
        }
        for (; numElemB > 0; numElemB--) {
            uint64_t elem;
            cin >> elem;
            vectorB.push_back(elem);
        }

        cout << findMax(vectorA, vectorB, maxSum) << endl;
    }
}


