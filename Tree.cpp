//
// Created by ted19 on 22/11/2019.
//

#include "Tree.h"

void Tree::deleter(Node *root) {
    if(root==nullptr)
        return;
    deleter(root->left);
    deleter(root->right);
    delete root;
}

Tree::~Tree() {
    deleter(root);
}
