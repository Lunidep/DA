#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <cstring>

#include <chrono>
#include <algorithm>

typedef unsigned long long ull;

const int NUMBER_OF_DIGIT = 32;

namespace sort {

struct TData {
    char key[NUMBER_OF_DIGIT + 1];
    char* str;  
    
    TData& operator= (const TData& tmp) {
        for (int i = 0; i < NUMBER_OF_DIGIT; i++)
            this->key[i] = tmp.key[i];
        str = tmp.str;
        return *this;
    }  

    friend bool operator<(const sort::TData& lhs, const sort::TData& rhs){
        return !strcmp(lhs.key, rhs.key);
    }

    friend std::ostream& operator<< (std::ostream& out, const TData& td) {
        std::cout << td.key << "\t" << td.str << '\n';
        return out;
    }

};



int CharToNum(int inc_idx);
void CountingSort(std::vector<TData>& v_data, size_t digit_num);
void RadixSort(std::vector<TData>& v_data);

}