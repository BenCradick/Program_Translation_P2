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
    std::string footer;
    int expr_count;
    int iter_count;
    int if_count;
    int var_count;
    std::string expr_str;
    std::string iter_str;
    std::string if_str;
    std::string var_str;

    std::string block(Node* root);

    std::string notEqual(std::string, std::string);
    std::string greater(std::string& destination);
    std::string lesser(std::string& destination);
    std::string greaterEqual(std::string& destination);
    std::string lesserEqual(std::string& destination);
    std::string equal(std::string& destination);
    std::string notEqual(std::string& destination);

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
    std::string RO(Node* root);
    std::string eq(Node* root);
    std::string lt(Node* root);






};


#endif //P1_SCOPE_H
