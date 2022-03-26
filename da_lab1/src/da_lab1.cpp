#include "sort.hpp"

const int LENGTH_OF_STRING = 2048;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std:: cout.tie(nullptr);
    std::vector<sort::TData> v_data;

    std::string key;
    std::string str;
    while ( std::cin >> key >> str ) {
        sort::TData tmp(key, str);
        v_data.push_back (tmp);
    }

    if (v_data.size() != 0) {
        sort::RadixSort(v_data);
    }

    for (ull i = 0; i < v_data.size(); i++){
        std::cout << v_data[i];
    }
    
    return 0;
}