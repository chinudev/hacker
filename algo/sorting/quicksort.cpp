//https://www.hackerrank.com/challenges/big-sorting
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm> 

using namespace std;


// partition array between indices left,right inclusive
int partition(vector<int>&  ar, int left, int right) 
{
   int pivotValue = ar[right];
   int pivotIndex=left;

   for (int i=left; i <= right; i++) {
       if (ar[i] <= pivotValue) {
           swap(ar[pivotIndex], ar[i]);
           pivotIndex++;
       }
   }
   for (auto elem : ar) cout << elem <<  " ";
   cout << endl;
   return pivotIndex-1;
}

void quickSort(vector <int>& arr, int left, int right) 
{
    if (right - left <= 0) return;
    int pivot = partition(arr,left,right);

    quickSort(arr,left,pivot-1);
    quickSort(arr,pivot+1,right);
} 

void quickSort(vector <int>& arr)
{
    quickSort(arr,0,arr.size()-1);
}


int main(void) 
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    //partition(arr);
    quickSort(arr);

    return 0;
}    


