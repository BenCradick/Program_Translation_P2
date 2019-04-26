#include <iostream>
#include "parser.h"
#include "testTree.h"
int main(int argc, char** argv) {

    Parser parser(argc, argv);
    testTree(parser.root);

    return 0;
}