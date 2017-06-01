#include <bits/stdc++.h>

using namespace std;


// Partition input vector around supplied pivot. 
//   vector[0..K] will contain values <= pivot
//   vector[K+1,N] contains value > pivot
//   returns iterator pointing to index K+1
partition(vector<long>::iterator begin, 
          vector<long>::iterator end, 
          long pivot)
{
        long size = end - begin;
        assert(size > 0);
        long pivot = begin[int(size/2)];

        end--; // end starts off pointing beyond the vector end
        while (1) {
                while (*begin <= pivot) begin++;
                while (*end > pivot) end--;

                // swap 
                long temp = *end;
                *end = *begin;
                *begin = temp;

                if (begin 
                begin++;end--;

        }
        return begin;
}

long findMedian(const vector<long> numVector) 
{
        if (numVector.size() == 0) 
        return numVector[0];
}

int main() 
{
        vector<long> test1 = {0,1,2,4,6,5,3};
        cout << findMedian(test1) << endl;

}
