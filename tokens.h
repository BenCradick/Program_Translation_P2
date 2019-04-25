//
// Created by Ben Cradick on 2019-03-11.
//

#ifndef P1_TOKENS_H
#define P1_TOKENS_H

#include <string>

enum token_type{ iter_tk,void_tk,var_tk,return_tk,scan_tk,print_tk,program_tk,cond_tk,then_tk,let_tk,
        operator_tk, eof_tk, equals_tk,  less_than_tk, greater_than_tk, colon_tk, addition_tk,  subtraction_tk,
        multiplication_tk,  division_tk, period_tk, right_parenthesis_tk, left_curly_bracket_tk, right_curly_bracket_tk,
        semi_colon_tk,  left_bracket_tk, right_bracket_tk , left_parenthesis_tk, int_tk, id_tk, percent_tk
};


struct tokens
{
    token_type t_type;
    std::string instance;
    int line;

};

#endif //P1_TOKENS_H
