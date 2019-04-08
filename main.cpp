#include <iostream>
#include "Scanner.h"
int main(int argc, char** argv) {
    Scanner s(argc, argv);

    tokens token;
    do {
        token = s.nextToken();
        std::cout << token.instance << token.line << std::endl;
    }while(token.t_type != eof_tk);
    return 0;
}