//
// Created by Ben Cradick on 2019-03-11.
//

#ifndef P1_TOKENS_H
#define P1_TOKENS_H

#include <string>

enum token_type{ iter_tk,void_tk,var_tk,return_tk,scan_tk,print_tk,program_tk,cond_tk,then_tk,let_tk,int_tk,id_tk,
        num_tk, op_delim_tk, eof_tk
};

struct tokens
{
    token_type t_type;
    std::string instance;
    int line;

};

#endif //P1_TOKENS_H
