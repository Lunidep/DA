#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
 
using namespace std;
 
void ParseLineTo(const string& line, vector<uint32_t>& vec) {
	uint32_t tmp = 0;
	bool isSpaces = true;
	for (char c : line) {
		if ('0' <= c && c <= '9') {
			tmp = tmp * 10 + c - '0';
			isSpaces = false;
		}
		else {
			if (!isSpaces) {
				vec.push_back(tmp);
				tmp = 0;
			}
			isSpaces = true;
		}
	}
	if (!isSpaces) {
		vec.push_back(tmp);
	}
}
 
class TBadLetterRule {
public:
	TBadLetterRule(const vector<uint32_t>& pattern) :
		patt_size(pattern.size()) {
		for (int i = patt_size - 1; i >= 0; --i) {
			rule[pattern[i]].push_back(i);
		}
		//getter();
	}
 
	int Use(uint32_t letter, size_t idx_patt) const {
		auto it = rule.find(letter);
		if (it == rule.end()) {
			return patt_size - idx_patt;
		}
		const vector<uint32_t>& idxs = it->second;
		for (uint32_t i : idxs) {
			if (i > idx_patt){
				return 1;
			}
			else if (i < idx_patt) {
				return idx_patt - i;
			}
		}
		return patt_size;
	}
 
	void getter() {
		for (auto const& pair : rule) {
			cout << "{" << pair.first << ": ";
			for (uint32_t lol : pair.second) {
				cout << lol << " ";
			}
			cout << "}\n";
		}
	}
 
private:
	unordered_map<uint32_t, vector<uint32_t>> rule;
	size_t patt_size;
};
 
 
vector<size_t> ZFunction(const vector<uint32_t>& pattern) {
	size_t n = pattern.size();
	vector<size_t> res(n, 0);
	size_t l = 0;
	size_t r = 0;
	for (size_t i = 1; i < n; ++i) {
		if (i <= r) {
			res[i] = min(r - i + 1, res[i - l]);
		}
		while (i + res[i] < n && pattern[res[i]] == pattern[i + res[i]]) {
			++res[i];
		}
		if (i + res[i] - 1 > r) {
			l = i;
			r = i + res[i] - 1;
		}
	}
	return res;
}
 
vector<size_t> NFunction(vector<uint32_t> pattern) {
	reverse(pattern.begin(), pattern.end());
	size_t n = pattern.size();
	vector<size_t> z_func = ZFunction(move(pattern));
	vector<size_t> res(n);
	for (size_t i = 0; i < n; ++i) {
		res[i] = z_func[n - i - 1];
	}
	return res;
}
 
const size_t UNDEFINED = -1;
 
vector<size_t> LFunction(const vector<uint32_t>& pattern, size_t& gp_size) {
	gp_size = 0;
	size_t n = pattern.size();
	vector<size_t> res(n, UNDEFINED);
	vector<size_t> n_func = NFunction(move(pattern));
	for (size_t i = 0; i < n; ++i) {
		size_t j = n - n_func[i];
		if (j != n) {
			res[j] = i;
			if (i == n - j - 1) {
				gp_size = i + 1;
			}
		}
	}
	return res;
}
 
class TGoodSuffix {
public:
	TGoodSuffix(const vector<uint32_t>& pattern) : patt_size(pattern.size())
	{
		rule = LFunction(pattern, gp_size);
		//getter();
	}
 
	int Use(size_t idx_patt) const {
		if (idx_patt >= patt_size) {
			return 1;
		}
		if (rule[idx_patt] == UNDEFINED) {
			return patt_size - gp_size;
		}
		return patt_size - rule[idx_patt] - 1;
	}
 
	size_t Getgp_size() const {
		return gp_size;
	}
 
	void getter() {
		for (int lol : rule) {
			cout << lol << " ";
		}
	}
private:
	vector<size_t> rule;
	size_t patt_size;
	size_t gp_size = 0;
};
 
 
 
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
 
	string line;
	getline(cin, line);
	vector<uint32_t> pattern;
	ParseLineTo(move(line), pattern);
 
	//cout << "\n\n---------------------------0------------------------------\n";
	TBadLetterRule bl_rule(pattern);
	//cout << "\n\n---------------------------1------------------------------\n";
	TGoodSuffix gs_rule(pattern);
	//cout << "\n\n---------------------------2------------------------------\n";
 
	size_t word_count = 0;
	vector<int> words_in_line;
	vector<uint32_t> text;
	while (getline(cin, line)) {
		ParseLineTo(move(line), text);
		word_count += text.size() - word_count;
		words_in_line.push_back(word_count);
	}
 
 
	for (uint32_t k = pattern.size() - 1; k < text.size();) {
		int i = (int)k;
		bool isOk = true;
		for (int j = pattern.size() - 1; j >= 0; --j) {
			if (text[i] != pattern[j]) {
				int offset = max(bl_rule.Use(text[i], j), gs_rule.Use(j + 1));
				k += offset;
				isOk = false;
				break;
			}
			--i;
		}
		if (isOk) {
			int idx = k - pattern.size() + 1;
			auto it = upper_bound(words_in_line.begin(), words_in_line.end(), idx);
			cout << distance(words_in_line.begin(), it) + 1 << ", ";
			if (it == words_in_line.begin()) {
				cout << idx + 1;
			}
			else {
				cout << idx + 1 - *prev(it);
			}
			cout << "\n";
			k += pattern.size() - gs_rule.Getgp_size();
		}
	}
 
	return 0;
}
