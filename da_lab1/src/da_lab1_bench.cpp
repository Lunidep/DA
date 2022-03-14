#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <cstring>


#include <chrono>
#include <algorithm>

const int NUMBER_OF_DIGIT = 32;

typedef unsigned long long ull;
typedef struct TData {
    char key[NUMBER_OF_DIGIT + 1];
    char* str;

    TData& operator= (const TData& tmp) {
        for (int i = 0; i < NUMBER_OF_DIGIT; i++)
            this->key[i] = tmp.key[i];
        str = tmp.str;
        return *this;
    }
} TData;

bool operator<(const TData& lhs, const TData& rhs){
    return !strcmp(lhs.key, rhs.key);
}

std::ostream& operator<< (std::ostream& out, const TData& td) {
    std::cout << td.key << "\t" << td.str << '\n';
    return out;
}


const int CONVERT_CONST_TO_HEX_SISTEM = 10;

int CharToNum(int inc_idx) {
    if ('a' <= inc_idx && inc_idx <= 'f')  {             //letter
        return inc_idx - 'a' + CONVERT_CONST_TO_HEX_SISTEM;
    }
    else if ('0' <= inc_idx && inc_idx <= '9')  {        //number
        return inc_idx - '0';
    }
    return 0;
}


const int SIZE_OF_COUNTING_MASSIVE = 16;

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


const int LENGTH_OF_STRING = 2048;

/*int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std:: cout.tie(nullptr);

    TData tmp;
    std::vector<TData> v_data;

    while (scanf("%s", tmp.key) != EOF) {
        tmp.str = new char[LENGTH_OF_STRING + 1];
        scanf("%s", tmp.str);
        tmp.str = (char *)realloc(tmp.str, sizeof(char) * (strlen(tmp.str) + 1));         
        v_data.push_back(std::move(tmp));
    }


    if (v_data.size()) {
        RadixSort(v_data);
    }

    for (TData tmp : v_data) {
        std::cout << tmp;
    }

    return 0;
}*/

using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    TData tmp;
    std::vector<TData> v_data;

    while (scanf("%s", tmp.key) != EOF) {
        tmp.str = new char[LENGTH_OF_STRING + 1];
        scanf("%s", tmp.str);
        tmp.str = (char *)realloc(tmp.str, sizeof(char) * (strlen(tmp.str) + 1));         
        v_data.push_back(std::move(tmp));
    }

    std::vector<TData> v_data2 = v_data;
    for (TData tmp : v_data) {
        std::cout << tmp;
    }
    for (TData tmp : v_data2) {
        std::cout << tmp;
    }

    std::cout << "Count of lines is " << v_data.size() << std::endl;

    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    RadixSort(v_data);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t counting_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    start_ts = std::chrono::system_clock::now();
    std::sort(std::begin(v_data2), std::end(v_data2));
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();/**/

    std::cout << "Counting sort time: " << counting_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL Sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;/**/
    return 0;
}