#include <iostream>
#include <fstream>
#include <cstring>
#include "avl.hpp"

using ull = unsigned long long;

std::string& ToUpper(std::string& str){
    for (size_t i = 0; i < str.size(); i++) { 
        char tmp = toupper(str[i]);
        str[i] = tmp;
    }
    return str;
}

ull ToULL(const std::string& str){
	return stoull(str, 0, 0);
}

int main()
{
	std::ios_base::sync_with_stdio(0);	

	TAVL<std::string, ull> tree;
	
	std::string str1;
	std::string str2;
	std::string str3;


	while(1){
		std::cin >> std::ws;
		if (std::cin.eof()){
			break;
		}
		std::cin >> str1;
		if(str1 == "+"){
			std::cin >> str2;
			if(!isalpha(str2[0])){
				continue;
			}
			std::cin >> str3;
			if (!isdigit(str3[0])){
				continue;
			}
			if(tree.Insert(ToUpper(str2), ToULL(str3))){
				std::cout << "OK" << std::endl;
			}
			else{
				std::cout << "Exist" << std::endl;
			}
		}
		else if(str1 == "-"){
			std::cin >> str2;
			if (!isalpha(str2[0])){
				continue;
			}
			if (tree.Remove(ToUpper(str2))){
				std::cout << "OK" << std::endl;
			}
			else{
				std::cout << "NoSuchWord" << std::endl;
			}
		}
		else if(str1 == "!"){
			std::cin >> str2;
			if(str2 == "Save"){
				std::cin >> str3;
				std::ofstream ofs(str3, std::ios::binary);
				if(ofs){
					tree.Serialize(ofs);
					std::cout << "OK" << std::endl;
				}
				else{
					std::cout << "ERROR: Couldn't create file" << std::endl;
				}
			}
			else if(str2 == "Load"){
				std::cin >> str3;
				std::ifstream ifs(str3, std::ios::binary);
				if (ifs)
				{
					TAVL<std::string, ull> temp;
					if(!temp.Deserialize(ifs)){
						std::cout << "ERROR: Opened file isn't serialized dict" << std::endl;
						continue;
					}
					else{
						tree.Swap(temp);
						std::cout << "OK" << std::endl;
					}
				}
				else{
					std::cout << "ERROR: Couldn't open file" << std::endl;
				}
			}
		}
		else if(isalpha(str1[0])){
			ull *value;
			if((value = tree.Find(ToUpper(str1))) != nullptr){
				std::cout << "OK: " << *value << std::endl;
			}
			else{
				std::cout << "NoSuchWord" << std::endl;
			}
		}
	}

	return 0;
}