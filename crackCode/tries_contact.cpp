#include <iostream>
#include <vector>
#include <assert.h>
#include <string>

using namespace std;

class Trie {
    vector<Trie*> childVector;
    int count;

public: 
    Trie() : childVector(26,nullptr), count(0) {}

    void Add(const string str, int pos=0) 
    {
        assert(str.size() >= pos);

        count++;
        if (str.size() == pos) return;


        int offset = str[pos] - 'a';
        assert(offset < 26 && offset >= 0);
        if (childVector[offset] == nullptr) {
            childVector[offset] = new Trie();
        }

        childVector[offset]->Add(str,pos+1);
    }

    int Find(const string str, int pos=0) 
    {
        assert(str.size() >= pos);

        if (str.size() == pos) {
            if (str.size() == 0) return 0;
            return count;
        }

        int offset = str[pos] - 'a';
        assert(offset < 26 && offset >= 0);
        if (childVector[offset] == nullptr) return 0;

        return childVector[offset]->Find(str,pos+1);
    }

};

void unitTest() 
{
    Trie root;
    root.Add("a");
    root.Add("boo");
    cout << root.Find("c") << endl;
    cout << root.Find("a") << endl;
    cout << root.Find("ab") << endl;
    cout << root.Find("bo") << endl;
    root.Add("bob");
    cout << root.Find("bo") << endl;
    cout << root.Find("bob") << endl;
}

int main() 
{
    //unitTest();

    int numTest;
    cin >> numTest;
    Trie root;

    for (; numTest > 0; numTest--) {
        string cmd; string str;
        cin >> cmd;
        cin >> str;

        if (cmd == "add") {
            root.Add(str);
        } else if (cmd == "find") {
            cout << root.Find(str) << endl;
        } else {
            assert("unexpected command");
        }

    }
}
