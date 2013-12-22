#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<pair<int,int> > s;
    while( !cin.eof() ) {
        int tx,ty;
        cin >> tx;
        cin >> ty;
        if(cin.good() ) {
        s.push_back(pair<int,int>(tx,ty));
        }
    }
    sort(s.begin(),s.end()); // сортировка сначала по m потом по s
 //   for(int i= 0; i < s.size(); i++) {
  //      cout << s[i].first << " " << s[i].second << endl;
   // }
    long int cW = 0 ;
    int cnt= 0;
    vector<int> tmp;
    for(int i = 0; i < s.size() ; i++ ) {
        if(s[i].second >= cW ) {
            cW += s[i].first;;
            cnt++;
       }
    }
    cout << cnt;
    return 0;
}
