//
// Created by Ben Cradick on 2019-05-14.
//

#ifndef P1_SCOPE_H
#define P1_SCOPE_H

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "Node.h"

struct Semantics {

        std::map<std::string, std::string> global;

    public:

        explicit Semantics();
        void setGlobal(Node* root);
        std::string generateAssembly(Node* root);


private:


    int iter_count;

    int tos;
    std::string iter_str;

    std::string block(Node* root);


    std::string greater();
    std::string lesser();
    std::string greaterEqual();
    std::string lesserEqual();
    std::string equal();
    std::string notEqual();

    std::string stats(Node* root);
    std::string expr(Node* root);
    std::string phrase(Node* root);
    std::string a(Node* root);
    std::string d(Node* root);
    std::string n(Node* root);
    std::string l(Node* root);
    std::string m(Node* root);
    std::string r(Node* root);
    std::string mStat(Node* root);
    std::string stat(Node* root);
    std::string in(Node* root);
    std::string out(Node* root);
    std::string _if(Node* root);
    std::string loop(Node* root);
    std::string assign(Node* root);
    std::string ro(Node* root);
    std::string eq(Node* root);
    std::string lt(Node* root);

    std::string arithmetic(Node *root);
    std::string arithHelper(Node* root);
    std::string conditionalHelper(Node* root);
    std::string mod();






};


#endif //P1_SCOPE_H
