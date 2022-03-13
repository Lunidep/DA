#include <iostream>
#include <ctime>
#include <vector>
#include <string>

typedef unsigned long long ull;
typedef struct TData {
    char key[33];
    char str[2048];
} TData;


std::ostream& operator<< (std::ostream& out, const TData& td) {
    std::cout << td.key << "\t" << td.str << '\n';
    return out;
}


const size_t CONVERT_CONST_TO_HEX_SISTEM = 10;

int CharToNum(int inc_idx) {
    if ('a' <= inc_idx && inc_idx <= 'f') {                 //letter
        return inc_idx - 'a' + CONVERT_CONST_TO_HEX_SISTEM;
    }
    else if ('0' <= inc_idx && inc_idx <= '9'){             //number
        return inc_idx - '0';
    }
    return 0;
}


const size_t SIZE_OF_COUNTING_MASSIVE = 16;

void CountingSort(std::vector<TData>* vec, size_t digit_num) {
    TData res[vec->size()];
    size_t count[SIZE_OF_COUNTING_MASSIVE] = { 0 };

    for (size_t i = 0; i < vec->size(); i++) {
        TData tmp = (*vec)[i];
        size_t incremental_idx = tmp.key[digit_num];

        count[CharToNum(incremental_idx)]++;
    }

    for (int i = 1; i < SIZE_OF_COUNTING_MASSIVE; i++) {
        count[i] += count[i - 1];
    }

    for (int i = vec->size() - 1; i >= 0; i--) {
        TData tmp = (*vec)[i];
        size_t sort_num = tmp.key[digit_num];

        size_t idx = CharToNum(sort_num);
        
        res[count[idx] - 1] = (*vec)[i];

        count[idx]--;
    }

    for (int i = 0; i < vec->size(); i++){
        (*vec)[i] = res[i];
    }
}


void RadixSort(std::vector<TData>* vec) {
    for (int digit_num = 31; digit_num >= 0; digit_num--) {
        CountingSort(vec, digit_num);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std:: cout.tie(nullptr);

    TData tmp;
    std::vector<TData> v;
    while (std::cin >> tmp.key && std::cin >> tmp.str) {
        v.push_back(tmp);
    }

    if (v.size() != 0) {
        RadixSort(&v);
    }

    for (TData tmp : v) {
        std::cout << tmp;
    }
    return 0;
}