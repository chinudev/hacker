#include <iostream>
#include <vector>
#include <assert.h>
#include <stdint.h>
#include <string>

using namespace std;

class Trie
{
public:
    uint64_t value;
    vector<Trie*> children;

public: 
    Trie(uint64_t value_=0) : value(value_), children(26,nullptr) {}

    void Add(string gene, uint64_t geneValue) 
    {
        Trie *node = this;
        for (char& c : gene) {
            int ord = c-'a';
            if (node->children[ord] == nullptr) {
                node->children[ord] = new Trie(0);
            }
            node = node->children[ord];
        }
        node->value += geneValue;
    }

    uint64_t FindValue(string str)
    {
        return FindValue(str.begin(), str.end());
    }

    uint64_t FindValue(string::const_iterator curr, const string::const_iterator end) 
    {
        uint64_t totalValue=0;
        Trie *node = this;
        while (curr != end) {
            int ord = *curr - 'a';
            if (node->children[ord] == nullptr) break;

            node = node->children[ord];
            totalValue += node->value;
            curr++;
        }
        return totalValue;
    }
};

void testTrie() 
{
    Trie root;
    assert(root.FindValue("a") == 0);
    assert(root.FindValue("abcd") == 0);
    assert(root.FindValue("") == 0);

    root.Add("a",1);
    root.Add("abc",10);
    assert(root.FindValue("a") == 1);
    assert(root.FindValue("ab") == 1);
    assert(root.FindValue("abc") == 11);
    assert(root.FindValue("abcd") == 11);

    root.Add("b",2);
    root.Add("b",10);
    assert(root.FindValue("bcd") == 12);
}


uint64_t getGeneHealth(const vector<string>& geneStringList, 
                       const vector<uint64_t>& geneValueList,
                       uint64_t start, uint64_t end,
                       const string& dna) 
{
    Trie root;
    for (uint64_t geneIndex=start; geneIndex <= end; ++geneIndex) { 
        root.Add(geneStringList[geneIndex], geneValueList[geneIndex]);
    }

    uint64_t totalValue=0;
    for (string::const_iterator dnaIter = dna.begin(); dnaIter != dna.end(); ++dnaIter) {
        totalValue += root.FindValue(dnaIter, dna.end());
    }
    return totalValue;
}

void testGeneHealth()
{
    vector<string> geneStrings  = {"a","b","c","aa","d","b"};
    vector<uint64_t> geneValues = {1,2,3,4,5,6};

    assert(19 == getGeneHealth(geneStrings, geneValues, 1,5, "caaab"));
    assert(0 == getGeneHealth(geneStrings, geneValues, 0,4, "xyz"));
    assert(11 == getGeneHealth(geneStrings, geneValues, 2,4, "bcdybc"));
    assert(22 == getGeneHealth(geneStrings, geneValues, 0,5, "aabndc"));
}


int main()
{
    //testTrie();
    //testGeneHealth();

    int numGenes;
    cin >> numGenes;

    vector<string> geneStrings(numGenes);
    for (int i=0; i < numGenes; i++) {
        cin >> geneStrings[i];
    }

    vector<uint64_t> geneHealth(numGenes);
    for (int i=0; i < numGenes; i++) {
        cin >> geneHealth[i];
    }

    int numDna;
    cin >> numDna;

    uint64_t leastHealth = 0xfffffff;
    uint64_t mostHealth = 0;

    for (; numDna > 0; numDna--) {
        int first, last;
        string dna;
        cin >> first >> last >> dna;

        //cout << "dna " << first << " " << last << " " << dna <<  endl;

        uint64_t health = getGeneHealth(geneStrings, geneHealth, first, last, dna);
        //cout << "    got health " << health <<  endl;

        if (health < leastHealth) leastHealth = health;
        if (health > mostHealth) mostHealth = health;
    }

    cout << leastHealth << " " << mostHealth << endl;
    

}



