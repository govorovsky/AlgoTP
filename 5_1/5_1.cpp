/* copyright Andrew G */

#include <iostream>


using std::cin;
using std::cout;
using std::endl;

struct Queue {
    Queue(int);
    int pop();
    int push(int);
    void resize();
    int * data;
    int first; /* element to pop */
    int last; /* size of queue == last pushed element */
    int capacity;
};

Queue::Queue(int cpc = 10) : capacity(cpc), data(new int[cpc]), first(0), last(0) { }

int Queue::pop() {
    if(first==last) return -1;
    return data[first++];
}

void Queue::resize() {
    if (first != 0) { /* we can avoid allocating new size by shifting array */
        for(int i = 0,j = first; j < last; i++, j++) {
            data[i] = data[j];
        }
        last = last - first;
        first = 0;
    } else {
        capacity *= 2;    
        int * old_data = data;
        data = new int[capacity];
        for(int i = 0; i < last; i++) {
            data[i] = old_data[i];
        }
        delete[] old_data;
    }
}

int Queue::push(int val) {
    if (last >= capacity) {
        resize();
    }
    data[last++] = val;
}

int main(int argc, const char *argv[]) {

    int n,a,b;
    cin >> n;
    if(n==0) cout << "NO";
    else {
    Queue Myq(1);
    for(int i = 0; i < n; i++) {
        cin >> a >> b;
        if(a==3) Myq.push(b);
        else if(a==2) { 
            int res = Myq.pop();
         //   cout << res << "\n";
            if (b != res) {
            cout << "NO";
            return 0;
            }
        }
    }
    cout << "YES";
    }
    return 0;
}
