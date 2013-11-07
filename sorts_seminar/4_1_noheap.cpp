#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

void merge(int *a, int *b, int size_a, int size_b, int * res, int kmax) {
    int i=0,j=0,k=0;
    while(i < size_a && j < size_b && k < kmax) {
        if(a[i] <= b[j]) {
            res[k++] = a[i++];
        } else {
            res[k++] = b[j++];
        }
    }
     while(i<size_a && k < kmax) res[k++] = a[i++];
     while(j<size_b && k < kmax) res[k++] = b[j++];
}

int main(int argc, const char *argv[])
{
    int n,k;
    cin >> n >> k;
    int *a = new int[k];
    int *b = new int[k];
    int *r = new int[k];

    for(int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    sort(a,a+k);
    int size = 0;
    for(int i = 0; i < n - k; ++i) {
          cin >> b[size++];
        if(size == k) {
          sort(b,b+size);
          merge(a,b,k,size,r,k);  
          memcpy(a,r,k*sizeof(a));
          size = 0;
        }
    }
    if(size != 0) {
          sort(b,b+size);
          merge(a,b,k,size,r,k);
          memcpy(a,r,k*sizeof(int));
    }
    for(int i = 0; i < k; ++i) {
        cout << a[i] << " ";
    }
    return 0;
}
