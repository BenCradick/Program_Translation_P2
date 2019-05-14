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

struct Scope {

        std::map<std::string, std::string> global;

    public:


        void setGlobal(Node* root);




};


#endif //P1_SCOPE_H
