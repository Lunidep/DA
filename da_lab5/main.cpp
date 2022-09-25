#include "TSuffixTree.h"
#include <string>
#include <iostream>

int main(void)
{
    string text;
    cin >> text;
    TSuffixTree tree(text + "$");
    int count = 1; 
    vector<int> res;
    while (cin >> text){
        res = tree.Search(text);
        if (!res.empty()) {
            cout << count << ": ";
            for (int i = 0; i < res.size()-1; ++i)
                cout << res[i] << ", ";
            cout << res[res.size()-1] << endl;
        }
        ++count;
    }
    return 0;
}