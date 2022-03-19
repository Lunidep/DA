#include "sort.hpp"


const int CONVERT_CONST_TO_HEX_SISTEM = 10;

const int SIZE_OF_COUNTING_MASSIVE = 16;

namespace sort{

int CharToNum(int inc_idx) {
    if ('a' <= inc_idx && inc_idx <= 'f')  {             //letter
        return inc_idx - 'a' + CONVERT_CONST_TO_HEX_SISTEM;
    }
    else if ('0' <= inc_idx && inc_idx <= '9')  {        //number
        return inc_idx - '0';
    }
    return 0;
}


void CountingSort(std::vector<TData>& v_data, size_t digit_num) {
    std::vector<TData> res(v_data.size());
    ull count[SIZE_OF_COUNTING_MASSIVE] = { 0 };

    for (size_t i = 0; i < v_data.size(); i++) {
        size_t incremental_idx = v_data[i].key[digit_num];
        count[CharToNum(incremental_idx)]++;
    }

    for (int i = 1; i < SIZE_OF_COUNTING_MASSIVE; i++) {
        count[i] += count[i - 1];
    }

    for (int i = v_data.size() - 1; i >= 0; i--) {
        size_t idx = CharToNum(v_data[i].key[digit_num]);
        res[count[idx] - 1] = v_data[i];
        count[idx]--;
    }

    v_data = res;
}


void RadixSort(std::vector<TData>& v_data) {
    for (int digit_num = NUMBER_OF_DIGIT - 1; digit_num >= 0; digit_num--) {
        CountingSort(v_data, digit_num);
    }
}

}