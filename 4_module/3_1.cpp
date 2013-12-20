#include <fstream>
#include <iostream>
 
using namespace std;
 
long int **a; // a[n][m] - количеством пирамид из n кубиков со слоями не меньше m

void allocateTable(int size) {
    size++;
    a = new long int*[size];
    for(int i = 0; i < size; i++) 
        a[i] = new long int[size];
}

void initTable(int size) {
 for (int cubes = 1; cubes <= size; cubes++)
        a[cubes][0] = 0 ; // если ширина слоя 0 то не построим ни одной пирамиды
    for (int width = 0; width <= size; width++)
        a[0][width] = 1; //  елси кубиков 0 то есть только 1 вариант построить пирамиду
}

int get_number_of_pyramids(int size) {
 for (int cn = 1; cn <= size; cn++) {
    for (int c = 1; c <= cn; c++)
        a[cn][c] = a[cn][c - 1] + a[cn - c][c];
    for (int c = cn+1; c <= size; c++)
        a[cn][c] = a[cn][cn];
}
   return a[size][size];
}

int main()
{
    int n;
    cin >> n;
    allocateTable(n); 
    initTable(n);  
    cout << get_number_of_pyramids(n);
    return 0;
}
