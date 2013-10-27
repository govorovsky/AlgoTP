#include <iostream>
#include <string>
#include <vector>

template<typename T>
class QuickSort {
    public:
        QuickSort(T * begin, T * end) {
            _sort(begin, (end - begin - 1));
        }
    private:
       void _sort(T * begin, int N);

};

template<typename T>
void QuickSort<T>::_sort(T * a, int N) {
    int j = N;
    int i = 0;
    T tmp, center;
    center = a[ N >> 1 ];

  do {
    while ( a[i] < center ) i++;
    while ( a[j] > center ) j--;

    if (i <= j) {
        std::swap(a[i],a[j]);
      i++; j--;
    }
  } while ( i<=j );

  if ( j > 0  ) _sort(a, j);
  if ( N > i ) _sort(a + i, N-i);
}

void print_arr(const std::vector<int>& a) {
    int size = a.size();
    for(int i = 0; i < size; ++i) {
        std::cout << a[i] << "\n";
    }
}


int main(int argc, const char *argv[])
{
    int num;
    std::vector<int> nums;
    while( std::cin >> num) {
        nums.push_back(num);
    }
    QuickSort<int> s(&nums[0],&nums[0] + nums.size());
    print_arr(nums);
    return 0;
}
