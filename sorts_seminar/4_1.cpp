#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

void AddToHeap(vector<int> & array, int elem) {
    array.push_back(elem);
    int i = array.size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if( array[i] >= array[parent]) {
            swap(array[i],array[parent]);
        }
            i = parent;
    }
}

void Heapify(vector<int> & array, int i) {
    int left = 2 * i + 1;
    int right= 2 * i + 2;
    int minimal = i;
    if(left < array.size() && array[left] > array[i])
        minimal = left;
    if(right < array.size() && array[right] > array[minimal])
        minimal = right;
    if(minimal != i) {
        swap(array[i], array[minimal]);
        Heapify(array, minimal);
    }
}

int GetMin(vector<int> & array) {
    if(array.size() == 0) {
        return -1;
    }
    int res = array[0];
    array[0] = array[array.size() - 1];
    array.pop_back();
    if(array.size() != 0) {
        Heapify(array, 0);
    }
    return res;
}

void BuildHeap(vector<int> & arr) {
    for(int i = arr.size()/2-1; i >= 0; --i) 
        Heapify(arr,i);
}

int main(int argc, const char *argv[])
{
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    arr.reserve(k); // O(k) memory

    for(int i = 0; i < k; i++) {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    BuildHeap(arr);
   
    for(int i = 0; i < n - k; i++) {
        int tmp;
        cin >> tmp;
        if (tmp < arr[0]) {
            GetMin(arr);
            AddToHeap(arr,tmp);
        }
    }
    sort(arr.begin(),arr.end());
    for(int i = 0; i < k; ++i)
        cout << arr[i] << " ";
    return 0;
}
