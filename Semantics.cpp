//
// Created by Ben Cradick on 2019-05-14.
//

#include "Semantics.h"

#include <algorithm>
#include <string>
#include <stdexcept>
#include <iostream>


Semantics::Semantics() {
    footer = "";
    expr_count = 0;
    if_count = 0;
    iter_count = 0;
    var_count = 0;
    expr_str = "expr";
    iter_str = "iter";
    if_str = "if";
    var_str ="var";
}


std::string Semantics::Semantics::generateAssembly(Node* root){
    if(root->child_count == 2){
        return block(root->children[1]);
    }
    else{
        return block(root->children[0]);
    }
}

void Semantics::Semantics::setGlobal(Node* root) {
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
        if(root->token[0]->t_type == id_tk)
        {
            if(root->token[1]->t_type == int_tk && global.find(root->token[0]->instance) == global.end() )
            {
                global.insert({root->token[0]->instance, root->token[1]->instance});
            }
            else
            {
                std::fprintf(stderr, "var %s has already been defined in this scope\n", root->token[0]->instance.c_str());
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
std::string Semantics::block(Node* root){
    if(root->child_count == 2){
        return stats(root->children[1]) + "STOP\n";
    }
    else{
        return stats(root->children[0]) + "STOP\n";
    }
}
std::string Semantics::expr(Node* root){
    if(root->children[1] == nullptr){
        return a(root->children[0]);
    }
    else {
        std::string node1 = var_str + std::to_string(var_count);
        std::string slug = expr_str + std::to_string(expr_count);
        footer += slug + ":";
        std::string body = "BR " + slug + "\n" + "outexpr" + std::to_string(expr_count) + ": ";
        std::string back = "BR outexpr" + std::to_string(expr_count) + "\n";
        var_count++;
        expr_count++;
        footer += a(root->children[0]);
        footer += back;

        std::string node2 = var_str + std::to_string(var_count);
        slug = expr_str + std::to_string(expr_count);
        footer += slug + ": ";
        body += "BR " + slug + "\n" + "outexpr" + std::to_string(expr_count) + ": ";
        back = "BR outexpr" + std::to_string(expr_count) + "\n";
        var_count++;
        expr_count++;
        footer += expr(root->children[0]->children[0]);
        footer += back;
        global.insert({node1, "0"});
        global.insert({node2, "0"});

        if(root->children[1]->token[0]->t_type == addition_tk){
            body += "LOAD " + node1 + "\nADD " + node1 + " " + node2 + "\n";
            return body;

        }
        else{
            body += "LOAD " + node1 + "\nSUB " + node2 + "\n";
            return body;
        }


    }
}
std::string Semantics::a(Node *root) {
    if(root->children[1] == nullptr){
        return n(root->children[0]);
    }
    else{
        std::string node1 = var_str + std::to_string(var_count);
        std::string slug = expr_str + std::to_string(expr_count);
        footer += slug + ":";
        std::string body = "BR " + slug + "\n" + "outexpr" + std::to_string(expr_count) + ": ";
        std::string back = "BR outexpr" + std::to_string(expr_count) + "\n";
        expr_count++;
        var_count++;
        footer += n(root->children[0]);
        footer += back;

        std::string node2 = var_str + std::to_string(var_count);
        slug = expr_str + std::to_string(expr_count);
        footer += slug + ": ";
        body += "BR " + slug + "\n" + "outexpr" + std::to_string(expr_count) + ": ";
        back = "BR outexpr" + std::to_string(expr_count) + "\n";
        footer += d(root->children[0]->children[0]);
        footer += back;
        var_count++;
        expr_count++;
        global.insert({node1, "0"});
        global.insert({node2, "0"});

        body += "LOAD " + node1 + "\nDIV " + node2 + "\n";
        return body;
    }
}
std::string Semantics::n(Node* root){
    if(root->children[1] == nullptr){
        return m(root->children[0]);
    }
    else{
        std::string node1 = var_str + std::to_string(var_count);
        std::string slug = expr_str + std::to_string(expr_count);
        footer += slug + ":";
        std::string body = "BR " + slug + "\n" + "outexpr" + std::to_string(expr_count) + ": ";
        std::string back = "BR outexpr" + std::to_string(expr_count) + "\n";
        var_count++;
        expr_count++;
        footer += m(root->children[0]);
        footer += back;

        std::string node2 = var_str + std::to_string(var_count);
        slug = expr_str + std::to_string(expr_count);
        footer += slug + ": ";
        body += "BR " + slug + "\n" + "outexpr" + std::to_string(expr_count) + ": ";
        back = "BR outexpr" + std::to_string(expr_count) + "\n";
        footer += n(root->children[0]->children[0]);
        footer += back;
        var_count++;
        expr_count++;
        global.insert({node1, "0"});
        global.insert({node2, "0"});

        body += "LOAD " + node1 +"\n" + "MULT " + node2 + "\n";

        return body;
    }
}
std::string Semantics::stats(Node *root) {

}
std::string Semantics::equal(std::string& destination){
    return "BRZERO " + destination + "\n";
}
std::string Semantics::greater(std::string& destination){
    return "BRPOS " + destination + "\n";
}
std::string Semantics::lesser(std::string& destination){
    return "BRNEG " + destination + "\n";
}
std::string Semantics::notEqual(std::string& destination){
    return greater(destination) + lesser(destination);
}
std::string Semantics::greaterEqual(std::string& destination) {

    return "BRZPOS " + destination + "\n";
}
std::string Semantics::lesserEqual(std::string& destination){
    return "BRZNEG " + destination + "\n";
}