#include <iostream>
#include "Parser.h"
#include "testTree.h"
#include "Scope.h"
int main(int argc, char** argv) {

    Parser parser(argc, argv);
    auto scope = new Scope;

    scope->setGlobal(parser.root);
    return 0;
}