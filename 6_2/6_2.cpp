#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Node {
    Node *next;
    char _val;
    Node(char val) : _val(val) {};
};

class Stack {
    public:
        Node * top;
        Node * next;
        Stack() :  top(NULL), next(NULL) {}
        void push(char);
        char pop();
        bool empty();

};

char Stack::pop() {
    if(top == NULL) {
        return -1;
    } else {
        Node * tmp = top;
        top = top->next;
        return tmp->_val;
    }
}

void Stack::push(char val) {
    Node * add = new Node(val);
    if(top == NULL) {
        top = add;
        add->next = NULL;
    }
    else {
        add->next = top;
        top = add;
    }
}

bool Stack::empty() {
    return (top == NULL);
}


bool isAnagram(string& str1, string& str2, Stack& st) {
    int i = 0, j = 0;
    while (i < str1.size() && j < str2.size()) {
        if (str1[i] != str2[j]) {
            st.push(str1[i]);
            i++;
        } else {
            i++;
            j++;
        }

    }
    while(!st.empty()) {
            if((st.pop()) != str2[j++]) {
                return 0;
            }
        }
    return 1; 
}

int main(int argc, const char *argv[])
{

    Stack st;
    string str1, str2;
    cin >> str1 >> str2;
    cout << (isAnagram(str1, str2, st) ? "YES" : "NO" );
     
    return 0;
}
