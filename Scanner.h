//
// Created by Ben Cradick on 2019-03-31.
//

#ifndef P1_SCANNER_H
#define P1_SCANNER_H

#include <set>
#include "tokens.h"
#include "FileManager.h"

class Scanner{
public:
    explicit Scanner(int, char**);
    tokens nextToken();
    int line;
    std::string buffer;

    FileManager files;
    std::set<char> delims;
private:
    //generates proto token
    tokens getProtoToken();
    //routes token to appropriate initial function in FSA
    tokens routeToken(tokens token);
    tokens getKeyWordToken(tokens token);
    tokens verifyInt(tokens token);
};
#endif //P1_SCANNER_H
