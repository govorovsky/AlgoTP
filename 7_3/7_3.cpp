#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

class Array {
    public:
        Array(int capacity = 10) : _capacity(capacity), _size(0), data(new int[_capacity]) {}
        void Add(int elem);
        int& Get(int index) const;
        int Size();
        int& operator[](int index) const { return Get(index); }
        void DeleteLast() { _size--; }
    private:
        void resize();
        int _capacity;
        int _size;
        int * data;
};

void Array::Add(int elem) {
    if (_size == _capacity) {
        resize();
    }
    data[_size++] = elem;
}

void Array::resize() {
    _capacity *= 2;
    int * old_data = data;
    data = new int[_capacity];
    for(int i = 0; i < _size; ++i) {
        data[i] = old_data[i];
    }
    delete[] old_data;
}

int& Array::Get(int index) const {
    if (index >= 0 && index < _size) {
        return data[index];
    }  else exit(1);
}

int Array::Size() {
    return _size;
}

void AddToHeap(Array & array, int elem) {
    array.Add(elem);
    int i = array.Size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if( array[i] <= array[parent]) {
            swap(array[i],array[parent]);
        }
            i = parent;
    }
}

void Heapify(Array & array, int i) {
    int left = 2 * i + 1;
    int right= 2 * i + 2;
    int minimal = i;
    if(left < array.Size() && array[left] < array[i])
        minimal = left;
    if(right < array.Size() && array[right] < array[minimal])
        minimal = right;
    if(minimal != i) {
        swap(array[i], array[minimal]);
        Heapify(array, minimal);
    }
}

int GetMin(Array & array) {
    if(array.Size() == 0) {
        return -1;
    }
    int res = array[0];
    array[0] = array[array.Size() - 1];
    array.DeleteLast();
    if(array.Size() != 0) {
        Heapify(array, 0);
    }
    return res;
}

int main(int argc, const char *argv[])
{
    Array a;
    int n, atime, ltime, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> atime >> ltime;
        if(a.Size() == 0) {
        AddToHeap(a, ltime);
        ans++;
        } else {
            int min = a[0];
            if (atime < min + 1) { 
                ans++;
                AddToHeap(a, ltime);
            } else {
                GetMin(a);
                AddToHeap(a, ltime);
            }
        }
    }
    cout << ans;
    return 0;
}
