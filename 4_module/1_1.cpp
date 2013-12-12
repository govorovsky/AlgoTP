/* hash table with quadratic probes */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

size_t hash_func(const string & key) {
  size_t c = 12343;
  size_t a = 31247;
  size_t b = 42589;

  size_t value = c;
  size_t multiplier = 1;
  for (size_t i = 0; i < key.size(); ++i) {
    value += key[i] * multiplier;
    value = value % b;
    multiplier = (multiplier * a) % b;
  }

  return value % b;
}

enum State { EMPTY=0, ACTIVE, DELETED };

class CHashNode {
    public:
        string value;
        State state;
        CHashNode(const string & s, State st) : value(s), state(st) {}
        CHashNode() : state(EMPTY) {}
};

class CHashTable {
    public:
        bool Add(const string&);
        bool Delete(const string&);
        bool Contains(const string& s) { return table[findPos(s)].state == ACTIVE; }
        CHashTable(size_t size = 11) : table(size), cSize(0) {}
    private:
        int findPos(const string &);
        vector<CHashNode> table;
        void rehash();
        size_t cSize; // текущий размер Хэш-таблицы
};


void CHashTable::rehash() {
    vector<CHashNode> old_table = table;
    table.resize(2 * table.size());
    //cout << "RESIZE" << table.size() << " ";
    cSize = 0;
    for(int i = 0; i < table.size(); ++i) table[i].state = EMPTY; // очищаем таблицу
    for(int i = 0; i < old_table.size(); ++i) {
        if(old_table[i].state == ACTIVE) {
            Add(old_table[i].value);
        }
    } 
}


int CHashTable::findPos(const string & s) {
/* ищем индекс элемента с ключем s, либо если его нет то возвращаем 
 * индекс пустой ячейки для вставки */
    int current_pos = hash_func(s) % table.size();
    int offset = 1;
    /* ищем только пустую ячейку чтобы не допустить дублирования элементов */
    while(table[current_pos].state != EMPTY && table[current_pos].value != s) {
        /* пробируем с квадратичным шагом 1, 4, 9, 16 ...*/
        current_pos = (current_pos + offset) % table.size();
        offset +=2;
    }
    return current_pos;
}

bool CHashTable::Add(const string& val) {
    int pos = findPos(val);
    if(table[pos].state == ACTIVE) return false; // если уже есть такое значение то не добавляем
    table[pos] = CHashNode(val, ACTIVE); // добавили 
    cSize++;
    if(cSize > table.size() / 2) rehash(); // перестраиваем таблицу когда она заполнится наполовину
    return true;
}

bool CHashTable::Delete(const string& s) {
    int pos = findPos(s);   
    if(table[pos].state != ACTIVE) return false; // нет такого элемента
    table[pos].state = DELETED; // иначе просто меняем состояние элемента
    return true;
}


int main(int argc, const char *argv[])
{
    CHashTable t;
    char cmd;
    string val;
    while(!cin.eof() ) {
        cin >> cmd >> val;
        if(cin.good() ) {
        if(cmd == '+') cout << (t.Add(val) ? "OK\n" : "FAIL\n");
        else if(cmd == '-') cout  << (t.Delete(val) ? "OK\n" : "FAIL\n");
        else cout << (t.Contains(val) ? "OK\n" : "FAIL\n");
        }

    }
    return 0;
}
