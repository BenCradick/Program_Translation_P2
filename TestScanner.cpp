//
// Created by Ben Cradick on 2019-04-07.
//

#include "TestScanner.h"
TestScanner::TestScanner(int argc, char **argv) : scanner(argc, argv) {
}
void TestScanner::test()
{
    tokens token;
    do {
        std::list<tokens> token_list;
        token_list = scanner.nextToken();
        do {
            token = *token_list.begin();
            printf("%-25s%-20s%-6d\n", scanner.tokenNames[token.t_type].c_str(), token.instance.c_str(), token.line);
            if(token.t_type == eof_tk)
            {
                break;
            }
            token_list.pop_front();
        }while(!token_list.empty());
    }while(token.t_type != eof_tk);
}
