#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

struct points{
    int x;
    int y; 
};

int x0;
int y_0;
bool xy_less(const points &lhs, const points &rhs) {
    // сортируем по координатам x y
       if(lhs.x == rhs.x)
        return (lhs.y > rhs.y);
       return (lhs.x > rhs.x);
}

bool atan_less(const points &lhs, const points &rhs){
    // сортируем по арктангенсам лучей из точки x0 y0 до всех остальных точек
        if(lhs.y == rhs.y)
          return (lhs.x > rhs.x);
        return (atan((double((lhs.y) - y_0)/((lhs.x) - x0))) < atan((double((rhs.y) - y_0)/((rhs.x) - x0))));
}

void insertion_sort(std::vector<points>& a, bool(*comp)(const points&, const points&)) {
    int i, j;
    int size = a.size();
    for (i = 1; i < size; ++i) {
        j = i;
        while ( j > 0 && comp(a[j-1],a[j])) {
            std::swap(a[j-1], a[j]);
            j--;
        }
    }
}
void print_arr(const std::vector<points> & a) {
    int size = a.size();
    for(int i = 0; i < size; ++i) {
        std::cout << a[i].x << " " << a[i].y << "\n";
    }
}

bool my_less(const int& lhs, const int& rhs) {
    return lhs > rhs;
}

int main(int argc, const char *argv[])
{
    points c_pair;
    int num;
    std::vector<points> nums;
    std::cin >> num;
    for(int i=0;i<num;i++) {
     std::cin >> c_pair.x >> c_pair.y;
        nums.push_back(c_pair);
    }
    insertion_sort(nums,xy_less);
    std::cout << nums[0].x << " " << nums[0].y <<"\n"; // начальная точка из которой идут все лучи
    x0 = nums[0].x;
    y_0 = nums[0].y;
    nums.erase(nums.begin());
    insertion_sort(nums,atan_less);
    print_arr(nums);
    return 0;
}
