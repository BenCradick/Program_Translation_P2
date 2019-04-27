//
// Created by Ben Cradick on 2019-04-26.
//

#include <iostream>
#include "testTree.h"

void testTree(Node* root){
    std::string tokenNames[31] = {"iter_tk", "void_tk", "var_tk", "return_tk", "scan_tk", "print_tk", "program_tk",
                                  "cond_tk", "then_tk", "let_tk",  "operator_tk",  "eof_tk", "equals_tk",
                                  "less_than_tk", "greater_than_tk", "colon_tk", "addition_tk","subtraction_tk",
                                  "multiplication_tk",  "division_tk",  "period_tk", "right_parenthesis_tk",
                                  "left_curly_bracket_tk","right_curly_bracket_tk", "semi_colon_tk",  "left_bracket_tk",
                                  "right_bracket_tk", "left_parenthesis_tk", "int_tk","id_tk", "percent_tk"
    };
    if(root == nullptr){
        return;
    }
    for(int i = 0; i < root->depth; i++){
        std::cout << "  ";
    }
    int i = 0;

    std::cout << root->name;
    while (i < root->token_count) {

        if(root->token[i] != nullptr) {
            std::cout << " Token " << i << ": " << " instance: " <<
                      root->token[i]->instance << " Token Type: " << tokenNames[root->token[i]->t_type];
        }
        i++;

    }
    std::cout << std::endl;
    i = 0;

    while(i < root->child_count){
        testTree(root->children[i]);
        i++;
    }
    return;
}