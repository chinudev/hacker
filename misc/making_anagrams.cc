#include <iostream>
#include <string>
#include <array>


using namespace std;

int number_needed(string str1, string str2)
{
        std::array<int,26> countLetters {};

        for (char& c : str1) 
                countLetters[int(c-'a')]++;
        
        for (char& c : str2) 
                countLetters[int(c-'a')]--;

        int sum=0;
        for (auto& count: countLetters) {
                sum += abs(count);
        }

        return sum;

}


int main()
{
        cout << "abc-def " << number_needed("abc", "def") << endl;
        cout << "abac-acabdeef " << number_needed("abac", "acabdeef") << endl;
}
