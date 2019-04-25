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

        printf("%-25s%-20s%-6d\n", scanner.tokenNames[token.t_type].c_str(), token.instance.c_str(), token.line);
    }while(token.t_type != eof_tk);
}
