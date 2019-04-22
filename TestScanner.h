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

    Scanner scanner;

};


#endif //P1_TESTSCANNER_H
