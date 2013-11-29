#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct SparseTable {
    SparseTable(int *src, int size);
    int RMQ(int l, int h);
    int secondmin(int l, int r);
    const int * array;
    int ** table;
};

SparseTable::SparseTable(int *src, int size) : array(src) {
    int logn = ceil(log2(size));
    table = new int * [size];
    for(int i = 0;i< size ;i++) {
        table[i] = new int[logn+1];
    }
    //создали, заполняем таблицу
    
    for(int i = 0;i < size; i++)
        table[i][0]=i;

    for(int j = 1; 1 << j <= size; j++){
        for(int i = 0; i + (1 << (j - 1) ) < size; i++){
            if(src[table[i][j-1]] <= src[table[i + (1 << (j - 1))][j - 1]])
                table[i][j]=table[i][j - 1];
            else
                table[i][j]=table[i + (1 << (j - 1))][j-1];
        }
    }
}

int SparseTable::RMQ(int l, int r) {
    if(l==r) return l;
    int k = log2(r-l+1);
    if(array[table[l][k]]<=array[table[r - (1 << k) + 1][k]])
        return table[l][k];
    return table[r - (1 << k) + 1][k];
    
}
int SparseTable::secondmin(int l, int r) {
    /* ищем вторую порядковую статистику двумя запросами RMQ
     * время запроса О(1) */
    int ans;
    int i = RMQ(l,r);
    if(i==l)  { 
        ans = array[RMQ(l + 1, r)];
    } else if(i == r) { 
        ans = array[RMQ(l, r - 1)];
    }
    else { 
        ans = min(array[RMQ(l, i - 1)], array[RMQ(i + 1, r)]);
    }
    return ans; 
}

int main(int argc, const char *argv[])
{
    int n,m;
    cin >> n >> m;
    int * array = new int[n];
    for(int i = 0; i<n; i++) cin >> array[i]; 
    SparseTable t = SparseTable(array,n);
    for(int i = 0; i < m; i++) {
        int l,r;
        cin >> l >> r;
        cout << t.secondmin(--l,--r) << "\n";
    } 
    return 0;
}
