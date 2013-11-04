#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <set>
using namespace std;


template<typename T>
void _sort(T * a, int N) {
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


template<typename T>
void QuickSort(T *begin, T *end) {
    if(begin != end) 
        _sort<T>(begin, (end - begin - 1));
}


struct date {
    bool isBirth; 
    /* 
     * isBirth - тип события. необходим для сравнения дат,
     * если две даты равны то сравниваем по нему
     */
    int date_int; 
    
};

bool operator < (const date& d1, const date& d2) {
    if(d1.date_int != d2.date_int) return d1.date_int < d2.date_int;
    return (d1.isBirth && !d2.isBirth);
}

bool operator > (const date& d1, const date& d2) {
    if(d1.date_int != d2.date_int) return d1.date_int > d2.date_int;
    return (!d1.isBirth && d2.isBirth);
}

istream & operator>>(istream &in, date& dat) {
    int y,m,d;
    in >> d >> m >> y;
    dat.date_int = y*1000 + m * 50 + d;
    return in;
}

date addYear(const date& d, int years) {
    date result = d;
    result.date_int = d.date_int + 1000*years;
    return result;
}

date substractDays(const date& d, int day) {
    date result = d;
    result.date_int -= day;
    return result;
}

bool CheckAndModifyDate(date &birth, date &death) {
    /* проверяем интервал и если человек дееспособен, 
     * заменяем даты рожденения и смерти границами дееспособности
     * в соответствии с условием задачи
     */
    date s_date = addYear(birth, 18);
    date o_date = min( substractDays(addYear(birth, 80), 1), substractDays(death,1));
    if( s_date < o_date) {
        s_date.isBirth = 1;
        o_date.isBirth = 0;
        birth = s_date;
        death = o_date;
        return 1;
    }
    return 0;
}

void readAllDates(vector<date>& dates, int num) {
    dates.reserve(2 * num);
    date birth, death;
    for (int i = 0; i < num; i++) { 
    cin >> birth;
    cin >> death;
    if (CheckAndModifyDate(birth, death)) {
        dates.push_back(birth);  
        dates.push_back(death);    
       }
    }  
}


int findIntersectionSets(vector<date>& dates) {
  //  sort(dates.begin(),dates.end());// STL sort
    QuickSort(&dates[0], &dates[0] + dates.size());
    int ans = 0;
    int curr = 0;
    for(int i = 0; i < dates.size(); ++i) {
        if(dates[i].isBirth) {
            curr++; // увеличиваем размер множества
        }
        else {
            ans = max(ans, curr); // берем максимальный размер множества
            curr--;
        }
    }
    return ans;
}



int main(int argc, const char *argv[])
{ 
    int n;
    vector<date> Dates;
    cin >> n;
    readAllDates(Dates, n);
    int ans = findIntersectionSets(Dates);
    cout << ans;
    return 0;
}
