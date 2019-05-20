#include <iostream>
#include "Parser.h"
#include "testTree.h"
#include "Semantics.h"
int main(int argc, char** argv) {

    Parser parser(argc, argv);
    auto scope = new Semantics;

    scope->setGlobal(parser.root);
    //parser.scanner.files.~FileManager();
    auto file = new FileManager(argc, argv);

    std::string output = scope->generateAssembly(parser.root);
    for(auto elem : output){
        file->outputFile << elem;
        file->outputFile.flush();
    }
    return 0;
}