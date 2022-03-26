#include "sort.hpp"

using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

const int LENGTH_OF_STRING = 2048;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    sort::TData tmp;
    std::vector<sort::TData> v_data;

    while (scanf("%s", tmp.key) != EOF) {
        tmp.str = new char[LENGTH_OF_STRING + 1];
        scanf("%s", tmp.str);
        tmp.str = (char *)realloc(tmp.str, sizeof(char) * (strlen(tmp.str) + 1));         
        v_data.push_back(std::move(tmp));
    }

    std::vector<sort::TData> v_data2 = v_data;
    // for (ull i = 0; i < v_data.size(); i++){
    //     std::cout << v_data[i];
    // }
    // for (ull i = 0; i < v_data2.size(); i++){
    //     std::cout << v_data2[i];
    // }

    std::cout << "Count of lines is " << v_data.size() << std::endl;

    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    RadixSort(v_data);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t counting_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    start_ts = std::chrono::system_clock::now();
    std::sort(std::begin(v_data2), std::end(v_data2));
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();/**/

    std::cout << "Radix sort time: " << counting_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL Sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;/**/
    return 0;
}