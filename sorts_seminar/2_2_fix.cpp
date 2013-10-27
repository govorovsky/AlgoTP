#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <set>
using namespace std;


template<typename T>
class QuickSort {
    public:
        QuickSort(T * begin, T * end) {
            if(begin != end)
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


struct date {
    int d, m, y;
    bool isBirth; 
    /* 
     * isBirth determine birth or death date. It's need to compare dates, because
     * if we compare two equals date, such as 2.2.2 and 2.2.2, first 
     * date will be less than second only if it is a birth date 
     * with isBirth = 1.
     */
    int num;
    
};

int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}


bool operator < (const date& d1, const date& d2) {
    if(d1.y != d2.y) return d1.y < d2.y;
    if(d1.m != d2.m) return d1.m < d2.m;
    if(d1.d != d2.d) return d1.d < d2.d;
    return (d1.isBirth && !d2.isBirth);
}

bool operator > (const date& d1, const date& d2) {
    if(d1.y != d2.y) return d1.y > d2.y;
    if(d1.m != d2.m) return d1.m > d2.m;
    if(d1.d != d2.d) return d1.d > d2.d;
    return (!d1.isBirth && d2.isBirth);
}

istream & operator>>(istream &in, date& d) {
    in >> d.d >> d.m >> d.y;
    return in;
}

date operator+(const date & d, int years) {
    /* we only need to add years */
    date result = d;
    result.y = d.y + years;
    return result;
}

date operator-(const date& d, int day) {
    /* we only need to subtract days */
    if(isLeap(d.y)){
        days[2] = 29;
    }
    else {
        days[2] = 28;
    }
    date result = d;
    result.d -= day;
    if(result.d == 0) {
        result.m--;
        if(result.m == 0) {
            result.m = 12;
            result.y--;
        }
        result.d = days[d.m]; /* restore days for month */
    }
    return result;
}


bool checkDate(date &birth, date &death) {
    date s_date = birth + 18;
    date o_date = min( (birth + 80) - 1, death - 1);
    if( s_date < o_date) {
        s_date.isBirth = 1;
        o_date.isBirth = 0;
        birth = s_date;
        death = o_date;
        return 1;
    }
    return 0;
}

void readDates(vector<date>& dates, int num) {
    dates.reserve(2 * num);
    date birth, death;
    for (int i = 0; i < num; i++) { 
    cin >> birth;
    cin >> death;
   //  birth.num = death.num = i; // only if we want to print sets 
    if (checkDate(birth, death)) {
        dates.push_back(birth);  
        dates.push_back(death);    
       }
    }  
}


void findAnswer(vector<date>& dates) {
  //  sort(dates.begin(),dates.end());// STL sort
    QuickSort<date> s(&dates[0], &dates[0] + dates.size());
    bool add = 0;
    bool out = 0;
    int ans = 0;
    int curr = 0;
    for(int i = 0; i < dates.size(); ++i) {
        if(dates[i].isBirth) {
            curr++;
            add = 1;
        }
        else {
            if(add) {
                out = 1;
                ans = max(ans, curr);
            }
            add = 0;
            curr--;
        }
    }
     out ?  cout << ans : cout << out;
   // if(!out) printf("0"); else printf("%d",ans);
}



int main(int argc, const char *argv[])
{
        
    int n;
    vector<date> Dates;
    cin >> n;
    readDates(Dates, n);
    findAnswer(Dates);
    return 0;
}
