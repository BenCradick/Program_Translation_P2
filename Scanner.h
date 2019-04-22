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
    std::list<tokens> nextToken();
    int line;
    std::string buffer;

    FileManager files;
    const std::string tokenNames[31] = {"iter_tk", "void_tk", "var_tk", "return_tk", "scan_tk", "print_tk", "program_tk",
                                  "cond_tk", "then_tk", "let_tk", "int_tk",  "id_tk",  "operator_tk",  "eof_tk",
                                  "equals_tk",  "less_than_tk", "greater_than_tk", "colon_tk", "addition_tk",
                                  "subtraction_tk", "multiplication_tk",  "division_tk",  "percent_tk",  "period_tk",
                                  "left_parenthesis_tk", "right_parenthesis_tk", "left_curly_bracket_tk",
                                  "right_curly_bracket_tk", "semi_colon_tk",  "left_bracket_tk", "right_bracket_tk"
    };
    std::set<char> delims;
private:
    //generates proto token
    tokens getProtoToken();
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
