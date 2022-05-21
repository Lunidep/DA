#include <iostream>
#include <map>
#include <chrono>
#include <string>
#include <new>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cstring>


using TUll = unsigned long long;

template<typename K, typename V>
class TAvl {
protected:
	struct TAvlNode {
		K key;
		V value;
		unsigned long long height;
		TAvlNode *left;
		TAvlNode *right;
		TAvlNode() : key(), value(), height{1}, left{nullptr}, 
							right{nullptr} {};
		TAvlNode(K k, V v) : key{k}, value{v}, height{1}, 
							left{nullptr}, right{nullptr} {};
	};

	TAvlNode *root;

	unsigned long long Height(const TAvlNode *node) {
		return node != nullptr ? node->height : 0;
	}

	int Balance(const TAvlNode *node) {
		return Height(node->left) - Height(node->right);
	}

	void Reheight(TAvlNode *node) {
		node->height = std::max(Height(node->left), Height(node->right)) + 1;
	}

	TAvlNode *RotateLeft(TAvlNode *a) {
		TAvlNode *b = a->right;
		a->right = b->left;
		b->left = a;
		Reheight(a);
		Reheight(b);
		return b;
	}

	TAvlNode *RotateRight(TAvlNode *a) {
		TAvlNode *b = a->left;
		a->left = b->right;
		b->right = a;
		Reheight(a);
		Reheight(b);
		return b;
	}

	TAvlNode *BigRotateLeft(TAvlNode *a) {
		a->right = RotateRight(a->right);
		return RotateLeft(a);
	}

	TAvlNode *BigRotateRight(TAvlNode *a) {
		a->left = RotateLeft(a->left);
		return RotateRight(a);
	}

	TAvlNode *Rebalance(TAvlNode *node) {
		if (node == nullptr) {
			return nullptr;
		}
		Reheight(node);
		int balanceRes = Balance(node);
		if (balanceRes == -2) {
			if (Balance(node->right) == 1) {
				return BigRotateLeft(node);
			}
			return RotateLeft(node);
		}
		else if (balanceRes == 2) {
			if (Balance(node->left) == -1) {
				return BigRotateRight(node);
			}
			return RotateRight(node);
		}
		return node;
	}

	TAvlNode *InsertPrint(TAvlNode *node, K k, V v) {
		if (node == nullptr) {
			try {
				node = new TAvlNode(std::move(k), v);
			}
			catch (std::bad_alloc &e) {
				std::cout << "ERROR: " << e.what() << "\n";
				return nullptr;
			}
			std::cout << "OK\n";
			return node;
		}
		if (k < node->key) {
			node->left = InsertPrint(node->left, k, v);
		}
		else if (k > node->key) {
			node->right = InsertPrint(node->right, k, v);
		}
		else {
			std::cout << "Exist\n";
		}
		return Rebalance(node);
	}

	TAvlNode *Insert(TAvlNode *node, K k, V v) {
		if (node == nullptr) {
			try {
				node = new TAvlNode(k, v);//попробуй потом std::move(key)
			}
			catch (std::bad_alloc &e) {
				return nullptr;
			}
			return node;
		}
		if (k < node->key) {
			node->left = Insert(node->left, k, v);
		}
		else if (k > node->key) {
			node->right = Insert(node->right, k, v);
		}
		return Rebalance(node);
	}

	TAvlNode *RemoveMin(TAvlNode *node, TAvlNode *tempNode) {
		if (tempNode->left != nullptr) {
			tempNode->left = RemoveMin(node, tempNode->left);
		}
		else {
			TAvlNode *rightChild = tempNode->right;
			node->key = std::move(tempNode->key);
			node->value = tempNode->value;
			delete tempNode;
			tempNode = rightChild;
		}
		return Rebalance(tempNode);
	}

	TAvlNode *Remove(TAvlNode *node, K k) {
		if (node == nullptr) {
			return nullptr;
		}
		if (k < node->key) {
			node->left = Remove(node->left, k);
		}
		else if (k > node->key) {
			node->right = Remove(node->right, k);
		}
		else {
			TAvlNode *leftChild = node->left;
			TAvlNode *rightChild = node->right;
			if (leftChild == nullptr && rightChild == nullptr) {
				delete node;
				return nullptr;
			}
			if (rightChild == nullptr) {
				delete node;
				return leftChild;
			}
			if (leftChild == nullptr) {
				delete node;
				return rightChild;
			}
			node->right = RemoveMin(node, rightChild);
		}
		return Rebalance(node);
	}

	TAvlNode *RemovePrint(TAvlNode *node, K k) {
		if (node == nullptr) {
			std::cout << "NoSuchWord\n";
			return nullptr;
		}
		if (k < node->key) {
			node->left = RemovePrint(node->left, k);
		}
		else if (k > node->key) {
			node->right = RemovePrint(node->right, k);
		}
		else {
			TAvlNode *leftChild = node->left;
			TAvlNode *rightChild = node->right;
			if (leftChild == nullptr && rightChild == nullptr) {
				delete node;
				std::cout << "OK\n";
				return nullptr;
			}
			if (rightChild == nullptr) {
				delete node;
				std::cout << "OK\n";
				return leftChild;
			}
			if (leftChild == nullptr) {
				delete node;
				std::cout << "OK\n";
				return rightChild;
			}
			node->right = RemoveMin(node, rightChild);
			std::cout << "OK\n";
		}
		return Rebalance(node);
	}

	TAvlNode *Search(TAvlNode *node, K k) {
		if (node == nullptr) {
			return nullptr;
		}
		for (TAvlNode *iter = node; iter != nullptr; ) {
			if (k < iter->key) {
				iter = iter->left;
			}
			else if (k > iter->key) {
				iter = iter->right;
			}
			else {
				return iter;
			}
		}
		return nullptr;
	} 

	void PrintTree(TAvlNode *node) {
		static int cnt = 0;
		if (node != nullptr) {
			cnt++;
			PrintTree(node->right);
			cnt--;
			for (int i = 0; i < cnt; i++) {
				std::cout << "\t";
			}
			std::cout << node->key << "\n";
			cnt++;
			PrintTree(node->left);
			cnt--;
		}
	}

public:
	TAvl() : root(nullptr) {};

	void Add(K k, V v) {
		root = Insert(root, std::move(k), v);
	}

	void AddPrint(K k, V v) {
		root = InsertPrint(root, std::move(k), v);
	}

	void Delete(K k) {
		root = Remove(root, std::move(k));
	}

	void DeletePrint(K k) {
		root = RemovePrint(root, std::move(k));
	}

	TAvlNode *Find(K k) {
		return Search(root, std::move(k));
	}

	void Print() {
		PrintTree(root);
	}

	void TreeDelete(TAvlNode *node) {
		if (node != nullptr) {
			TreeDelete(node->left);
			TreeDelete(node->right);
			delete node;
		}
	}

	~TAvl() {
		TreeDelete(root);
	}
};

class TDetailAvl : public TAvl<std::string, TUll> {

	void Lower(std::string &str) {
		int strSize = str.size();
		for (int i = 0; i < strSize; i++) {
			str[i] = std::tolower(str[i]);
		}
	}

	void Save(std::ostream &os, const TAvlNode *node) {
		if (node == nullptr) {
			return;
		}
		int keySize = node->key.size();
		os.write(reinterpret_cast<char *>(&keySize), sizeof(keySize));
		os.write(node->key.c_str(), keySize);
		os.write((char *)&node->value, sizeof(node->value));

		bool hasLeft = node->left != nullptr;
		bool hasRight = node->right != nullptr;

		os.write(reinterpret_cast<char *>(&hasLeft), sizeof(hasLeft));
		os.write(reinterpret_cast<char *>(&hasRight), sizeof(hasRight));

		if (hasLeft) {
			Save(os, node->left);
		}
		if (hasRight) {
			Save(os, node->right);
		}
	}

	TAvlNode *Load(std::istream &is) {
		TAvlNode *root = nullptr;

		int keySize;
		is.read(reinterpret_cast<char *>(&keySize), sizeof(keySize));

		if (is.gcount() == 0) {
			return root;
		}

		char *key = new char[keySize + 1];
		key[keySize] = '\0';
		is.read(key, keySize);

		TUll value;
		is.read(reinterpret_cast<char *>(&value), sizeof(value));

		bool hasLeft = false;
		bool hasRight = false;
		is.read(reinterpret_cast<char *>(&hasLeft), sizeof(hasLeft));
		is.read(reinterpret_cast<char *>(&hasRight), sizeof(hasRight));

		root = new TAvlNode();
		root->key = std::move(key);
		root->value = value;

		if (hasLeft) {
			root->left = Load(is);
		}
		else {
			root->left = nullptr;
		}

		if (hasRight) {
			root->right = Load(is);
		}
		else {
			root->right = nullptr;
		}

		return root;
	}

	bool OpenFileSave(std::string &fileName) {
		std::ofstream os{fileName.c_str(), std::ios::binary | std::ios::out};
		if (os) {
			Save(os, root);
		} 
		else {
			return false;
		}
		os.close();
		return true;
	}

	bool OpenFileLoad(std::string &fileName) {
		std::ifstream is{fileName.c_str(), std::ios::binary | std::ios::in};
		if (is) {
			TreeDelete(root);
			root = Load(is);
		}
		else {
			return false;
		}
		is.close();
		return true;
	}

public:
	void DetailInsert() {
		std::string key;
		TUll value = 0;

		std::cin >> key >> value;
		Lower(key);

		AddPrint(std::move(key), value);
	}

	void DetailRemove() {
		std::string key;

		std::cin >> key;
		Lower(key);

		DeletePrint(std::move(key));
	}

	void DetailFind(const std::string &k) {
		std::string key{k};

		Lower(key);

		TAvlNode *resFind = Find(std::move(key));
		if (resFind != nullptr) {
			std::cout << "OK: " << resFind->value << "\n"; 
		}
		else {
			std::cout << "NoSuchWord\n";
		}

	}

	void SaveLoad() {
		std::string cmd;
		std::string fileName;

		std::cin >> cmd >> fileName;
		if (cmd[0] == 'S') {
			if (!OpenFileSave(fileName)) {
				std::cout << "ERROR: can't open file\n";
				return;
			}
		}
		else {
			if (!OpenFileLoad(fileName)) {
				std::cout << "ERROR: can't open file\n";
				return;
			}
		}
		std::cout << "OK\n";
	}


};

using duration_t = std::chrono::microseconds;
using ull = unsigned long long;
int numder_of_nodes = 1000;


int main() {
    std::map<std::string, ull> rb_tree;

    TDetailAvl avl_tree;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t rb_ts = 0, avl_ts = 0;

    while(numder_of_nodes <= 1000000){
        std::cout << "----------------" << "numder_of_nodes = " << numder_of_nodes << " ----------------\n";
        
    
        for (int i = 0; i <= numder_of_nodes; i++) {
            {
                start = std::chrono::system_clock::now();
                rb_tree.insert( {std::to_string(i), i} );
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                avl_tree.Add( std::to_string(i), i );
                end = std::chrono::system_clock::now();
                avl_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
        std::cout << "Insert:\n" << "std::map ms=" << rb_ts << "\navl ms=" << avl_ts;

        rb_ts = avl_ts = 0;
        for (int i = 0; i <= numder_of_nodes; i++) {
            {
                start = std::chrono::system_clock::now();
                rb_tree.find( std::to_string(i) );
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                avl_tree.Find( std::to_string(i) );
                end = std::chrono::system_clock::now();
                avl_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
        std::cout << "\n\nFind:\n" << "std::map ms=" << rb_ts << "\navl ms=" << avl_ts;

        rb_ts = avl_ts = 0;
        for (int i = 0; i <= numder_of_nodes; i++) {
            {
                start = std::chrono::system_clock::now();
                rb_tree.erase( std::to_string(i) );
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
                rb_tree.insert( {std::to_string(i), i} );
            }
            {
                start = std::chrono::system_clock::now();
                avl_tree.Delete( std::to_string(i) );
                end = std::chrono::system_clock::now();
                avl_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
                avl_tree.Add( std::to_string(i), i );
            }
        }
        std::cout << "\n\nDelete:\n" << "std::map ms=" << rb_ts << "\navl ms=" << avl_ts << "\n\n";

        numder_of_nodes *= 10;
    }
}