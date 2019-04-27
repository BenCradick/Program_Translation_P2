//
// Created by Ben Cradick on 2019-04-22.
//

#ifndef P1_PARSER_H
#define P1_PARSER_H


#include "Node.h"
#include "Scanner.h"

//variables that are local to this set of functions
struct Parser {
    explicit Parser(int argc, char** argv);
    tokens token;
    Scanner scanner;
    Node* root;
    const std::string tokenNames[31] = {"iter_tk", "void_tk", "var_tk", "return_tk", "scan_tk", "print_tk", "program_tk",
                                        "cond_tk", "then_tk", "let_tk",  "operator_tk",  "eof_tk", "equals_tk",
                                        "less_than_tk", "greater_than_tk", "colon_tk", "addition_tk","subtraction_tk",
                                        "multiplication_tk",  "division_tk",  "period_tk", "right_parenthesis_tk",
                                        "left_curly_bracket_tk","right_curly_bracket_tk", "semi_colon_tk",  "left_bracket_tk",
                                        "right_bracket_tk", "left_parenthesis_tk", "int_tk","id_tk", "percent_tk"
    };


    //<program>       ->      <vars> <block>
    Node *program(int);

    //<block>         ->      void <vars> <stats> returnd
    Node *block(int);

    //<vars>          ->      empty | var Identifier : Integer <vars>
    Node *vars(int);

    //<expr>          ->      <A> <phrase>
    Node *expr(int);

    //<phrase>        ->      + <expr> | - <expr> | empty
    Node *phrase(int);

    //<A>             ->      <N> <D>
    Node *a(int);

    //<D>             ->      / <A> | empty
    Node *d(int);

    //<N>             ->      <M> <L>
    Node *n(int);

    //<L>             ->      * <N> | empty
    Node *l(int);

    //<M>             ->      % <M> |  <R>
    Node *m(int);

    //<R>             ->      ( <expr> ) | Identifier | Integer
    Node *r(int);

    //<stats>         ->      <stat> ; <mStat>
    Node *stats(int);

    //<mStat>         ->      empty |  <stat>  ;  <mStat>
    Node *mStat(int);

    //<stat>          ->      <in> | <out> | <block> | <if> | <loop> | <assign>
    Node *stat(int);

    //<in>            ->      scan  Identifier
    Node *in(int);

    //<out>           ->      print <expr>
    Node *out(int);

    //<if>            ->      cond [ <expr> <RO> <expr> ] <stat>
    Node *_if(int);

    //<loop>          ->      iter [ <expr> <RO> <expr> ] <stat>
    Node *loop(int);

    //<assign>        ->      Identifier  = <expr>
    Node *assign(int);

    //<RO>            ->      < | = <  | >  | = > | < >   |   =
    Node *ro(int);

    //<EQ>            ->      < | > | empty
    Node *eq(int);

    //<LT>            ->      empty | < >
    Node *lt(int);

    void error(tokens, token_type);
    void error(tokens, token_type, token_type);
    void error(tokens token , token_type type1, token_type type2, token_type type3);
    void error(tokens);
};


#endif //P1_PARSER_H
