//  https://www.hackerrank.com/challenges/simple-text-editor/problem

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;


class Error {
public:
    string message;
    Error(const string& msg) : message(msg) {}
};

class Editor {
private: 
    char* store;
    uint32_t storeSize;
    uint32_t maxSize;

    vector<pair<int,int>> opStack;


public:
    Editor(int maxSize_) : maxSize(maxSize_) {
        store = new char[maxSize];
        storeSize = 0;
    }
    ~Editor() {
        delete[] store;
    }

    void Print() { store[storeSize] = '\0'; cout << store << endl; } 

    void Add(const string& word) {
        int len = word.size();
        if (len + storeSize > maxSize) throw Error("memory exceeded");
        for (char c : word) {
            store[storeSize++] = c;
        }
        opStack.push_back(make_pair(0,len));
    }

    void Del(uint32_t k) {
        if (k > storeSize) throw Error("index out of range");
        storeSize -= k;
        opStack.push_back(make_pair(1,k));
    }

    void Undo() {
        pair<int,int> lastOp =  opStack.back();
        opStack.pop_back();

        if (lastOp.first == 0) {  // add
            storeSize -= lastOp.second;
        } else if (lastOp.first == 1) {  // delete
            storeSize += lastOp.second;
        } else {
            throw Error("Invalid op");
        }
    }
    void Print(uint32_t k) {
        if (k > storeSize || k == 0) throw Error("index out of range");
        cout << store[k-1] << endl;
    }
};



int main()
{

    Editor editor(1000*1000);   // 10^6 max entries

    int numQueries; 
    cin >> numQueries; 
    for (; numQueries > 0; numQueries--) {
        int op;
        cin >> op;


        if (op == 1) {  // add 
            string word;
            cin >> word;
            editor.Add(word);
        } else if (op == 2) { // delete
            int index;
            cin >> index;
            editor.Del(index);
        } else if (op == 3) { // print
            int index;
            cin >> index;
            editor.Print(index);
        } else if (op == 4) { // undo
            editor.Undo();
        } else {
            assert(true);
        }
        cout << "***";
        editor.Print();
    }
}


