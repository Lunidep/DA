#include <iostream>
#include <chrono>
#include "TSuffixTree.h"

vector<int> StandartFind(string const& text, string const& pattern){
    vector<int> arr;
    size_t n_pos = text.find(pattern, 0);
    arr.push_back(n_pos);
    while(n_pos != string::npos) {
        n_pos = text.find(pattern, n_pos + 1);
        if(n_pos != string::npos) { 
            arr.push_back(n_pos); 
        }
    }
    
    return arr;
}

int main()
{
    string text, pattern;
    chrono::time_point<chrono::system_clock> start, end;
    uint64_t create_time = 0;
    uint64_t myfind_time = 0;
    uint64_t find_time = 0;

    cin >> text;
    start = chrono::system_clock::now();
    TSuffixTree tree(text + "$");
    end = chrono::system_clock::now();
    create_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    while(cin >> pattern) {
        start = chrono::system_clock::now();
        vector<int> res_sa = tree.Search(pattern);
        end = chrono::system_clock::now();
        myfind_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        start = chrono::system_clock::now();
        vector<int> res_find = StandartFind(text, pattern);
        end = chrono::system_clock::now();
        find_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    cout << "Time for create suffix tree: " << create_time << " ms" << endl;
    cout << "Time for my find: " << myfind_time << " ms" << endl;
    cout << "Time for standart find: " << find_time << " ms" << endl;
    return 0;
}