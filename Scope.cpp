//
// Created by Ben Cradick on 2019-05-14.
//

#include "Scope.h"

#include <algorithm>
#include <string>
#include <stdexcept>
#include <iostream>


void Scope::setGlobal(Node* root) {
    if (root == nullptr){
        return;
    }

    if(root->token_count == 2)
    {
        if(root->token[1] == nullptr){
            for(int i = 0; i < root->child_count; i++)
            {
                setGlobal(root->children[i]);
            }
            return;
        }
        if(global.find(root->token[0]->instance) == global.end() && root->token[0]->t_type == id_tk)
        {
            if(root->token[1]->t_type == int_tk)
            {
                global.insert({root->token[0]->instance, root->token[1]->instance});
            }
            else
            {
                std::fprintf(stderr, "Trying to use uninitialized var: %s\n", root->token[0]->instance.c_str());
                exit(EXIT_FAILURE);
            }
        }
        else if(root->token[1]->t_type == id_tk)
        {
            if(global.find(root->token[1]->instance) == global.end()){
                std::fprintf(stderr, "Trying to use var %s before initialization\n", root->token[1]->instance.c_str());
                exit(EXIT_FAILURE);
            }
        }
//        else
//        {
//            std::fprintf(stderr, "var %s is already defined in the global scope\n", root->token[0]->instance.c_str());
//            exit(EXIT_FAILURE);
//        }
    }
    else if(root->token_count == 1)
    {
        if(root->token[0]->t_type == id_tk && global.find(root->token[0]->instance) == global.end())
        {
            std::fprintf(stderr, "Trying to use var %s before initialization\n", root->token[0]->instance.c_str());
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < root->child_count; i++)
    {
        setGlobal(root->children[i]);
    }
}