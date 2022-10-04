#ifndef TSUFTREE_H
#define TSUFTREE_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;
#define endl '\n';

class TNode
{
public:
    map<char, TNode *> to;
    string::iterator begin, end;
    TNode *sufflink;
    TNode(string::iterator begin, string::iterator end);
    ~TNode() {};
};

class TSuffixTree
{
public:
    TSuffixTree(string str);
    vector<int> Search(string pattern);
    virtual ~TSuffixTree();
private:
    string text;
    TNode *root;
    TNode *lastAdded, *activeNode;
    int activeLen;
    string::iterator activeEdge;
    
    int remainder;    
    void RecursiveDestroy(TNode *node);
    bool CheckEdge(string::iterator position, TNode *node);
    void AddLetter(string::iterator add);
    void SearchLeafs(TNode *node, vector<int> &answer, int patternLocations);
};



#endif