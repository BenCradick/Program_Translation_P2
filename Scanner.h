//
// Created by Ben Cradick on 2019-03-31.
//

#ifndef P1_SCANNER_H
#define P1_SCANNER_H

#include <set>
#include <list>
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

    std::list<tokens> token_list;
    //routes token to appropriate initial function in FSA
    std::list<tokens> routeToken(tokens token);
    std::list<tokens> getKeyWordToken(tokens token);
    std::list<tokens> verifyInt(tokens token);
    std::list<tokens> verifyId(tokens token);


    std::list<tokens> iKeyWord(tokens token);
    std::list<tokens> vKeyWord(tokens token);
    std::list<tokens> rKeyWord(tokens token);
    std::list<tokens> sKeyWord(tokens token);
    std::list<tokens> pKeyWord(tokens token);
    std::list<tokens> cKeyWord(tokens token);
    std::list<tokens> tKeyWord(tokens token);
    std::list<tokens> lKeyWord(tokens token);
    std::list<tokens> determineOperatorToken(tokens token);

    void determineTokenType(tokens* token);




};
#endif //P1_SCANNER_H
