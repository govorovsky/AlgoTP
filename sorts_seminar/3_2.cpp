#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <ctime>
using namespace std;


int partition(int *a, int n, int k) {
    swap(a[0],a[k]);
    int cnt = 0;
    int i = n - 1, j = n - 1;
    while (j > 0) {
       if(a[j] == a[0]) {
        ++cnt;
        if(cnt % 2) {
            swap(a[j],a[i]);
            i--;
            j--;
        } else j--; 
    } else
        if(a[0] < a[j] ) {
            swap(a[i],a[j]);
            i--; j--;
        } else {
            j--;
        }
    }
    swap(a[i],a[0]);
    return i;
}

int median_of_three(int * arr, int a, int b, int c){
    if((arr[a] > arr[b] && arr[a] < arr[c]) || (arr[a] > arr[c] && arr[a] < arr[b])) return a; // (b a c) || (c a b)
    else if((arr[b] > arr[a] && arr[b] < arr[c]) || (arr[b] > arr[c] && arr[b] < arr[a])) return b; // (a b c) || (c b a)
    else return c; 
 }


int nth_element(int *a, int n, int k) {
  int left = 0; // смещение от левой границы массива
 while(1) {
    int m = median_of_three(a + left, 0, n/2, n-1);
    int pos = partition(a + left, n , m);
    if (pos < k) {
         k -= (pos + 1);
         n -= (pos + 1);
         left += pos + 1;
    } else if (pos > k ) {
         n = pos;
    } else {
         return (pos + left);
    }
 }
}


int main(int argc, const char *argv[])
{
    int n, k;
    cin >> n >> k;
    vector<int> data(n);
    for(int i = 0;i < n; i++) {
        cin >> data[i];
    }
    int nth_el =  nth_element(&data[0], data.size(),k);
    cout << data[nth_el];
        
    return 0;
}
