//
// Created by Ben Cradick on 2019-04-22.
//

#ifndef P1_NODE_H
#define P1_NODE_H


#include <cstdlib>
#include "tokens.h"

struct Node {
    explicit Node(int depth, const std::string name){
        children = nullptr;
        token = nullptr;
        this->depth = depth;
        this->name = name;
    }
    Node** children;
    tokens** token;
    std::string name;

    int depth;


};


#endif //P1_NODE_H
