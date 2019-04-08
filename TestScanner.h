//
// Created by Ben Cradick on 2019-04-07.
//

#ifndef P1_TESTSCANNER_H
#define P1_TESTSCANNER_H

#include "Scanner.h"
class TestScanner {

public:
    explicit TestScanner(int argc, char **argv);
    void test();

private:
    std::string tokenNames[14] = {"iter_tk", "void_tk", "var_tk", "return_tk", "scan_tk", "print_tk", "program_tk",
                                  "cond_tk", "then_tk", "let_tk", "int_tk",  "id_tk",  "operator_tk",  "eof_tk" };
    Scanner scanner;

};


#endif //P1_TESTSCANNER_H
