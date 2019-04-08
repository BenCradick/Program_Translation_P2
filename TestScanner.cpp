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
        token = scanner.nextToken();
        printf("%-15s%-10s%-6d\n",  tokenNames[token.t_type].c_str(), token.instance.c_str(), token.line);
    }while(token.t_type != eof_tk);
}
