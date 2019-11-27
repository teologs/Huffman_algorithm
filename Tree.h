//
// Created by ted19 on 22/11/2019.
//

#ifndef HUFFMAN_ALGORITHM_TREE_H
#define HUFFMAN_ALGORITHM_TREE_H

struct Node {
    int data;
    Node* left;
    Node* right;
};

class Tree {
private:
    Node* root;
public:
~Tree();
void deleter(Node* root);

};


#endif //HUFFMAN_ALGORITHM_TREE_H
