#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <istream>
#include <fstream>
#include <queue>
#include <bitset>
#include <sys/stat.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

typedef vector<pair<unsigned char, string> > HuffmanCodeTable; // таблица кодов Хаффмана

struct TreeNode {
    /* Элемент дерева Хаффмана */
    TreeNode * left;
    TreeNode * right;
    size_t frequency;
    unsigned char data;
    TreeNode ( size_t freq, unsigned char dat ) : frequency(freq), data(dat), left(0), right(0) {} 
    TreeNode (  TreeNode * l, TreeNode * r ) : frequency(l->frequency + r->frequency), data(0), left(l), right(r) {} 
};

struct NodeCmp {
    bool operator() (const TreeNode * lhs, const TreeNode * rhs) const { return lhs->frequency > rhs->frequency; }
};

struct FreqTable {
    /* Таблица частоты встречаемости символов */
    int * data;
    size_t size;
    FreqTable(size_t sz) : data(new int[sz]() ), size(sz) { } 
    ~FreqTable() { delete[] data; }
};

void getFrequencies (istream& is, FreqTable& freqtable) {
   char dat[1];
   int cnt=0;
   while(1) {
        is.read(dat,1);
        cnt++;
       // cout << (int)(unsigned char)dat[0] <<"\n";
        if(is.eof() ) break;
        freqtable.data[(int)(unsigned char)dat[0]]++;
   }
 //  cout << "READED" << cnt << "BYTES";
}

TreeNode * BuildHuffmanTree(FreqTable& ft) {
    priority_queue<TreeNode*, vector<TreeNode*>,  NodeCmp> pq;
    for(size_t i = 0; i < ft.size; ++i) {
        // заполняем очередь
        if(ft.data[i]) {
//            cout << "Symb" << char(i) << " freq: " << ft.data[i] <<"\n";
            pq.push(new TreeNode(ft.data[i], (unsigned char)i)); 
        }
    }
    // строим дерево 
    while(pq.size() != 1) {
        TreeNode * tleft = pq.top();
        pq.pop();
        TreeNode * tright = pq.top();
        pq.pop();
        pq.push(new TreeNode(tleft, tright));
    }
    return pq.top();
}

void getHuffmanCodes(TreeNode * tree, HuffmanCodeTable& table, string code) {
    if(tree->left == 0 && tree->right == 0) {
        if(code.empty()) code="0"; // если входная последовательность содежрит одинаковые байты то кодируем одним символом
        table.push_back(make_pair(tree->data,code));
    } else {
        code +='0';
        getHuffmanCodes(tree->left,table,code);
        code.erase(code.end()-1);
        code+='1';
        getHuffmanCodes(tree->right,table,code);
    }
}

string int2bin(int num) {
    string res = "";
    int bc = 0;
    while ( num > 0 ) {
        if ( num % 2 ) {
            res+='1';
        } else {
            res+='0';
        }
        num = num / 2;
        bc++;
    }
    if(bc != 8) {
        for(int i = bc; i < 8; i++) res+='0';
    }
    reverse(res.begin(), res.end());
   // cout << res << "\n";
    return res; 
}


int getHuffmanHeaderCode(TreeNode * tree, string& code) {
   static int tree_size = 1; /* Всегда есть хотя бы одна вершина */
    if(tree->left == 0 && tree->right == 0) {
        code += '1';
        code += int2bin(int(tree->data));
        tree_size+=8; /* добавляем байт */
    } else {
        code +='0';
        tree_size = getHuffmanHeaderCode(tree->left,code) + 1;
        tree_size = getHuffmanHeaderCode(tree->right,code) + 1;
    }
    return tree_size;
}


void writeHeader(const string& code, ostream& out) {
    int size = code.size();
    out.write((char*) (&size), sizeof(int) );
    unsigned char acc = 0;
    unsigned char * bytes;
    unsigned char bitcount = 1;
    int bytes_count = 0;
    if(size % 8) { 
        size = ((size / 8) + 1) * 8;
    } 
    bytes = new unsigned char[size / 8](); // Сохраняемш размер дерева +само дерево
    for(int i = 0; i < code.size(); ++i, ++bitcount) {
        if(code[i] == '0') {
            acc |= (0 << ( bitcount - 1));
        } else {
            acc |= (1 << ( bitcount - 1));
        }
        if(!(bitcount % 8)) { // заполнили байт
           // cout <<"OK BYTE: " << int2bin((int)acc) << "\n";
            bytes[bytes_count++] |= acc;     
            bitcount = 0;
            acc = 0;
        }
    }
    if (bytes_count * 8 != size) {
        bytes[size / 8 - 1] |= acc;
        bytes_count++;
    } 
    cout << "\n";
    for(int i = 0; i < bytes_count; i++) {
        cout << int2bin ( (int)(unsigned char)bytes[i] );
    }
    out.write((char*)bytes, bytes_count);
//    cout << "WROTE" << bytes_count << "SIZE:" << size;
}


void TreeRead(istream & in) {
    int tree_size;
    in.read((char*)&tree_size,sizeof(int));
    string code;
    for(size_t i = 0; i < tree_size / 8; i++) {
        char node;
        in.read(&node, sizeof(char));
        cout << int2bin(node);
    }

}


int main(int argc, const char *argv[])
{
    FreqTable ft(256); // каджый символ - один байт
    HuffmanCodeTable table;
    string code;
    if(argc != 2) return 1;
    string fname(argv[1]);
    cout << fname;
    ifstream ifs(fname.c_str(),ifstream::binary);
    if(ifs){

        getFrequencies(ifs,ft);

        TreeNode* hufftree = BuildHuffmanTree(ft);

        getHuffmanCodes(hufftree, table, string() );

        sort(table.begin(),table.end());

        for(int i = 0; i < table.size(); ++i) 
            cout << "symbol: " << table[i].first << " code: " << table[i].second << "\n"; 
        string::size_type len=0;
        for(int i = 0; i < table.size(); ++i) len+=ft.data[(int)(table[i].first)] * table[i].second.size();
        len+=32;
    string cod;
    int s = getHuffmanHeaderCode(hufftree, cod);
    for(int i = 0; i < cod.size(); i++) cout << cod[i];
    cout << "\n\n" << s << " " << cod.size();
    string outfile = fname+".huf";
    ofstream ofs(outfile.c_str(), ofstream::binary);
    writeHeader(cod,ofs);
    ofs.close();

        struct stat st;
        stat(fname.c_str(), &st);
        size_t size = st.st_size;
        cout <<endl;
        cout << setw(43) << left << "Estimating encoded file size ( bits ): " << setfill(' ') << len+s << endl;
        cout << setw(43) << left <<  "Original file size:" << setfill(' ') << size*8 << endl;
        cout << setw(43) << left  << "Saves: " << setfill(' ') << 100 - (double)(len+s) / (size*8) * 100 << "%" << endl;


    ifstream is(outfile.c_str(), ofstream::binary);

        TreeRead(is);

    }
    return 0;
}
