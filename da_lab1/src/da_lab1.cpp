#include "sort.hpp"

const int LENGTH_OF_STRING = 2048;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std:: cout.tie(nullptr);

    sort::TData tmp;
    std::vector<sort::TData> v_data;

    while (scanf("%s", tmp.key) != EOF) {
        tmp.str = new char[LENGTH_OF_STRING + 1];
        scanf("%s", tmp.str);
        tmp.str = (char *)realloc(tmp.str, sizeof(char) * (strlen(tmp.str) + 1));         
        v_data.push_back(std::move(tmp));
    }


    if (v_data.size()) {
        sort::RadixSort(v_data);
    }

    // for (sort::TData tmp : v_data) {
    //     std::cout << tmp;
    // }

    for (ull i = 0; i < v_data.size(); i++){
        std::cout << v_data[i];
    }
    
    return 0;
}