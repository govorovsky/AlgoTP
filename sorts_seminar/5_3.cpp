#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define BITS_NUM 63

bool digit(long long int a, int pos) {
    return ((a >> pos) & 1LL);
}
void partition(long long int *a, int j, int i, int w) {
    while(j!=i) {
        while(digit(a[i],w) == 0 && (i < j)) i++;
        while(digit(a[j],w) == 1 && (j > i)) j--;
        swap(a[i],a[j]);
    }
}
void quickSortBinary(long long int *a,int l,int r,int w) {
    int i = l, j = r;
    if(r<=l || w < 0) return; 
    partition(a,j,i,w);
    if(digit(a[r],w) == 0) j++;
    quickSortBinary(a,l,j-1,w-1);
    quickSortBinary(a,j,r,w-1);
}
int main(int argc, const char *argv[])
{
    int n;
    cin >> n;
    long long int *a = new long long int[n];
    for(int i=0; i< n; i++) {
        cin >> a[i];
    }
    quickSortBinary(a,0,n-1,BITS_NUM);
    for(int i=0; i< n; i++) {
        cout << a[i] << " ";
    }

        
    return 0;
}
