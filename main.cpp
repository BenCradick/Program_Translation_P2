#include <iostream>
#include "Parser.h"
#include "testTree.h"
#include "Semantics.h"
int main(int argc, char** argv) {

    Parser parser(argc, argv);
    auto scope = new Semantics;

    scope->setGlobal(parser.root);
    return 0;
}