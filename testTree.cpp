//
// Created by Ben Cradick on 2019-04-26.
//

#include <iostream>
#include "testTree.h"

void testTree(Node* root){
    if(root == nullptr){
        return;
    }
    for(int i = 0; i < root->depth; i++){
        std::cout << "  ";
    }
    int i = 0;
    if(root->token != nullptr) {
        while (i < root->token_count) {

            std::cout << root->name << " token " << i << ": " << root->token[i]->instance << std::endl;
            i++;

        }
    }
    while(i < root->child_count){
        testTree(root->children[i]);
        i++;
    }
}