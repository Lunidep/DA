#include "TSuffixTree.h"

TSuffixTree::TSuffixTree(string str){
    text = str;
    root = new TNode(text.end(), text.end());
    lastAdded  = root;
    activeNode = root;
    activeLen  = 0;
    activeEdge = text.begin();
    remainder  = 0;
    root->sufflink = root;

    for (string::iterator it = text.begin(); it != text.end(); ++it) {
        AddLetter(it);
    }
}

TNode::TNode(string::iterator begin, string::iterator end): 
    begin(begin), end(end), sufflink(nullptr) {}

TSuffixTree::~TSuffixTree(){
    RecursiveDestroy(root);
}

void TSuffixTree::RecursiveDestroy(TNode *node){
    for (auto it = node->to.begin(); it != node->to.end(); ++it)
        RecursiveDestroy(it->second);
    delete node;
}


void TSuffixTree::AddLetter(string::iterator add){
    lastAdded = root;
    ++remainder;
    while (remainder) {
        if (activeLen == 0) {
            activeEdge = add;
        }
        //search from activeNode common letters??
        map<char, TNode *>::iterator it = activeNode->to.find(*activeEdge);
        TNode *next;

        //search -> false
        if (it == activeNode->to.end()) {
            TNode *leaf = new TNode(add, text.end());
            activeNode->to[*activeEdge] = leaf;

            
            if (lastAdded != root){// ПРАВИЛО 2
                //cout << "SL 1\n";
                lastAdded->sufflink = activeNode; 
            }    
            lastAdded = activeNode;
            /*
            Если ребро разделяется и вставляется новая вершина, 
            и если это не первая вершина, созданная на текущем шаге, 
            ранее вставленная вершина и новая вершина соединяются через 
            специальный указатель, суффиксную ссылку.
            */
        } 
        
        //search -> true
        else {
            next =  it->second; //вершина, куда мы идем
            
            //можем ли мы пройти это ребро целиком?
            if (CheckEdge(add, next)) {
                continue;
            }

            //мы внутри ребра и при сравнении его с текстом все хорошо =)
            if (*(next->begin + activeLen) == *add) {
                ++activeLen;
                
                if (lastAdded != root) {// ПРАВИЛО 2
                    //cout << "SL 2\n";
                    lastAdded->sufflink = activeNode;    
                }  
                       
                lastAdded = activeNode;  
                break;
            }
            //мы внутри ребра и текст престал совпадать с текстом ребра =)
            TNode *split = new TNode(next->begin, next->begin + activeLen);
            TNode *leaf = new TNode(add, text.end());
            activeNode->to[*activeEdge] = split;

            split->to[*add] = leaf;
            next->begin += activeLen;
            split->to[*next->begin] = next;

            
            if (lastAdded != root)  {// ПРАВИЛО 2
                //cout << "SL 3\n";  
                lastAdded->sufflink = split; 
            }
            lastAdded = split;
            cout << "SPLIT" << endl;
        }


        --remainder;
        
        // ПРАВИЛО 1
        if (activeNode == root && activeLen != 0) {
            --activeLen;
            activeEdge = add - remainder + 1;
            //activeEdge становится первым символом нового суффикса, который нужно вставить
        } 
        // ПРАВИЛО 3
        else {
            activeNode = activeNode->sufflink; 
            /*
            После разделения ребра из активная_вершина, которая не является корнем, 
            переходим по суффиксной ссылке, выходящей из этой вершины, 
            если таковая имеется активная_вершина устанавливается вершиной, 
            на которую она указывает. Если суффиксная ссылка отсутствует, 
            активная_вершина устанавливается корнем. 
            активное_ребро и активная_длина остаются без изменений.
            */
        }
    }
}

bool TSuffixTree::CheckEdge(string::iterator position, TNode *next){
    int edgeLen;
    if (position + 1 < next->end)// наша позиция не последняя
        //inside edge
        edgeLen = position + 1 - next->begin;
    else
        edgeLen = next->end - next->begin;


    //checking if we can go through entire edge
    if (activeLen >= edgeLen) {
        activeEdge += edgeLen;
        activeLen -= edgeLen;
        activeNode = next;
        //successfully passed edge
        return true;
    }
    //need to apply some rule
    //which one checked in main function
    return false;
}



void TSuffixTree::SearchLeafs(TNode *node, vector<int> &answer, int patternLocation){
    if (node->end == text.end()) { 
        //leaf found
        answer.push_back(text.size() - patternLocation + 1);
    } else{
        TNode* child;
        int addDepth;
        //run through all eddges from this node
        //and run dfs at them
        for (auto it = node->to.begin(); it != node->to.end(); ++it) {
            child = it -> second;
            addDepth = child -> end - child->begin; //edge length
            SearchLeafs(child, answer,  patternLocation + addDepth);
        }
    }
}

vector<int> TSuffixTree::Search(string pattern){
    vector<int> answer;
    //string::iterator patPos = pattern.begin();
    int patternLocation = 0; //symbols passed at edges
    TNode *node = root; ///starts from root
    if (pattern.size() > text.size()) {
        //pattern larger than text
        return answer;
    }
    //search for all pattern
    for (string::iterator patPos = pattern.begin(); patPos != pattern.end(); ++patPos) {
        auto pathTo = node->to.find(*patPos);
        if(pathTo == node->to.end()) {
            //mismatch
            //no such symbol from node
            return answer;
        }
        node = pathTo->second;
        patternLocation += node->end - node->begin;     
        for(string::iterator edgePos = node->begin; edgePos != node->end && patPos != pattern.end(); ++edgePos, patPos++){
            if(*edgePos != *patPos){
                //mismatch inside edge
                return answer;
            }
        }        
        if(patPos==pattern.end())
            //exactly at node
            break;
        --patPos;
    }
    //node found run dfs for it
    SearchLeafs(node, answer, patternLocation);  
    //sort pattern indexes 
    sort(answer.begin(), answer.end());    
    return answer;
}