//
// Created by Ben Cradick on 2019-04-22.
//

#include "parser.h"

Parser::Parser(int argc, char **argv) : scanner(argc, argv) {
    root = program(0);
    token = scanner.nextToken();
    if(token.t_type != eof_tk){
        error(token, eof_tk);
    }
}


//<program>       ->      <vars> <block>
Node* Parser::program(int depth){
    Node* node = new Node(depth, "<program>");
    depth++;
    token = scanner.nextToken();

    if(token.t_type == var_tk){
        token = scanner.nextToken();
        node->children = (Node**)malloc(sizeof(Node*) * 2);
        node->children[0] = vars(depth);
        node->children[1] = block(depth);


    }
    else if(token.t_type == void_tk) {
        //token = scanner.nextToken();
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = block(depth);

    }
    else {
        error(token, var_tk, void_tk);

    }
    return node;
}
//<block>         ->      void <vars> <stats> return
Node* Parser::block(int depth){
    Node* node = new Node(depth, "<block>");
    depth++;
    //token = scanner.nextToken();
    if(token.t_type == void_tk){
        token = scanner.nextToken();
        if(token.t_type == var_tk){
            node->children = (Node**)malloc(sizeof(Node*) * 2);
            token = scanner.nextToken();
            node->children[0] = vars(depth);
            //token = scanner.nextToken();
            node->children[1] = stats(depth);
        }
        else{
            node->children = (Node**)malloc(sizeof(Node*));
            node->children[0] = stats(depth);
        }
        //token = scanner.nextToken();
        if(token.t_type != return_tk){
            error(token, return_tk);
        }
        else{
            token = scanner.nextToken();
        }
        return node;
    }
    else{
        error(token, void_tk);
    }
    exit(EXIT_FAILURE);
}
//<vars>          ->      empty | var Identifier : Integer <vars>
Node* Parser::vars(int depth){
    Node* node = new Node(depth, "<vars>");
    depth++;
    //token = scanner.nextToken();
    if(token.t_type == id_tk){
        node->token = (tokens**)malloc(sizeof(tokens*)*2);
        node->token[0] = &token;
        token = scanner.nextToken();
        if(token.t_type == colon_tk){
            token = scanner.nextToken();
            if (token.t_type == int_tk){
                node->token[1] = &token;
                node->children = (Node**)malloc(sizeof(Node*));
                token = scanner.nextToken();
                if(token.t_type == var_tk) {
                    token = scanner.nextToken();
                    node->children[0] = vars(depth);
                }
                return node;
            }
            else{
                error(token, int_tk);
            }
        }
        else{
            error(token, colon_tk);
        }
    }
    return nullptr; //if empty
}
//<expr>          ->      <A> <phrase>
Node* Parser::expr(int depth){
    Node* node = new Node(depth, "<expr>");
    depth++;
    node->children = (Node**)malloc(sizeof(Node*)*2);
    node->children[0] = a(depth);

    node->children[1] = phrase(depth);

    return node;



}
//<phrase>        ->      + <expr> | - <expr> | empty
Node* Parser::phrase(int depth){
    Node* node = new Node(depth, "<phrase>");
    depth++;
    if(token.t_type == addition_tk || token.t_type == subtraction_tk){
        node->token = (tokens**)malloc(sizeof(tokens*));
        node->children = (Node**)malloc(sizeof(Node*));

        node->token[0] = &token;
        token = scanner.nextToken();
        node->children[0] = expr(depth);
        return node;
    }
    return nullptr;

}
//<A>             ->      <N> <D>
Node* Parser::a(int depth){
    Node* node = new Node(depth, "<A>");
    depth++;

    node->children  = (Node**)malloc(sizeof(Node*)*2);
    node->children[0] = n(depth);

    node->children[1] = d(depth);

    return node;
}
//<D>             ->      / <A> | empty
Node* Parser::d(int depth){
    Node* node = new Node(depth, "<D>");
    depth++;

    if(token.t_type == division_tk){
        node->token = (tokens**)malloc(sizeof(tokens*));
        node->children = (Node**)malloc(sizeof(Node*));

        node->token[0] = &token;
        token = scanner.nextToken();

        node->children[0] = a(depth);
        return node;
    }
    else{
        return nullptr;
    }
}
//<N>             ->      <M> <L>
Node* Parser::n(int depth){
    Node* node = new Node(depth, "<N>");
    depth++;

    node->children = (Node**)malloc(sizeof(Node*)*2);
    node->children[0] = m(depth);

    // done this way because <L> can be empty;
    node->children[1] = l(depth);

    return node;
}
//<L>             ->      * <N> | empty
Node* Parser::l(int depth){
    Node* node = new Node(depth, "<L>");
    depth++;
    if(token.t_type == multiplication_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        token = scanner.nextToken();
        node->children[0] = n(depth);
        return node;
    }

    return nullptr;
}
//<M>             ->      % <M> |  <R>
Node* Parser::m(int depth){
    Node* node = new Node(depth,"<M>");
    depth++;
    node->children = (Node**)malloc(sizeof(Node*));
    if(token.t_type == percent_tk){
        node->token = (tokens**)malloc(sizeof(tokens*));
        node->token[0] = &token;
        token = scanner.nextToken();
        node->children[0] = m(depth);

    }
    else if(token.t_type >= left_parenthesis_tk && token.t_type <= id_tk){
        node->children[0] = r(depth);
    }
    else{
        error(token);
    }
    return node;
}
//<R>             ->      ( <expr> ) | Identifier | Integer
Node* Parser::r(int depth){
    Node* node = new Node(depth, "<R>");
    depth++;


    if(token.t_type == left_parenthesis_tk){
        node->token = (tokens**)malloc(sizeof(tokens*)*2);
        node->children = (Node**)malloc(sizeof(Node*));


        node->token[0] = &token;

        token = scanner.nextToken();
        node->children[0] = expr(depth);



        if(token.t_type == right_bracket_tk){
            node->token[1] = &token;
            token = scanner.nextToken();
            return node;
        }
        else{
            error(token, right_parenthesis_tk);
        }

    }
    else{
        node->token = (tokens**)malloc(sizeof(tokens*));
        if(token.t_type == id_tk || token.t_type == int_tk) {
            node->token[0] = &token;
            token = scanner.nextToken();
            return node;
        }
        else{
            error(token);
        }
    }
    error(token);
    exit(EXIT_FAILURE);
}
//<stats>         ->      <stat> ; <mStat>
Node* Parser::stats(int depth){
    Node* node = new Node(depth, "<stats>");
    depth++;
    node->children = (Node**)malloc(sizeof(Node*)*2);

    node->children[0] = stat(depth);


    if(token.t_type == semi_colon_tk){
        node->token = (tokens**)malloc(sizeof(tokens*));
        node->token[0] = &token;

        token = scanner.nextToken();
        node->children[1] = mStat(depth);
        return node;
    }
    else{
        error(token);
        exit(EXIT_FAILURE);
    }



}
//<mStat>         ->      empty |  <stat>  ;  <mStat>
Node* Parser::mStat(int depth){
    Node* node = new Node(depth, "<mStat>");
    depth++;

    if(token.t_type == scan_tk || token.t_type == print_tk || token.t_type == cond_tk
    || token.t_type == iter_tk || token.t_type == id_tk || token.t_type == void_tk){
        node->children = (Node**)malloc(sizeof(Node*)*2);
        node->children[0] = stat(depth);
        if(token.t_type == semi_colon_tk){
            token = scanner.nextToken();
            node->children[1] = mStat(depth);
        }
        else{
            error(token);
        }
        return node;
    }
    return nullptr;

}
//<stat>          ->      <in> | <out> | <block> | <if> | <loop> | <assign>
Node* Parser::stat(int depth){ //DO NOT iterate token after match the functioins called will

    Node* node = new Node(depth, "<stat>");
    depth++;

    if(token.t_type == scan_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = in(depth);
    }
    else if(token.t_type == print_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = out(depth);
    }
    else if(token.t_type == void_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = block(depth);
    }
    else if(token.t_type == cond_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = _if(depth);
    }
    else if(token.t_type == iter_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = loop(depth);
    }
    else if(token.t_type == id_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = assign(depth);
    }
    else{
        error(token);
    }
    return node;
}
//<in>            ->      scan  Identifier
Node* Parser::in(int depth){
    Node* node = new Node(depth, "<in>");

    if(token.t_type == scan_tk){
        node->token = (tokens**)malloc(sizeof(tokens*));
        token = scanner.nextToken();
        if(token.t_type == id_tk){
            node->token[0] = &token;
            token = scanner.nextToken();
        }
        else{
            error(token, id_tk);
        }
    }
    else{
        error(token, scan_tk);
    }
    return node;
}
//<out>           ->      print  <expr>
Node* Parser::out(int depth){
    Node* node = new Node(depth, "<out>");
    depth++;
    if(token.t_type == print_tk){
        token = scanner.nextToken();
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = expr(depth);
    }
    else{
        error(token, print_tk);
    }
    return node;
}
//<if>            ->      cond [ <expr> <RO> <expr> ] <stat>
Node* Parser::_if(int depth){
    Node* node = new Node(depth, "<if>");
    depth++;
    if(token.t_type == cond_tk){
        token = scanner.nextToken();
        if(token.t_type == left_bracket_tk){
            node->token = (tokens**)malloc(sizeof(tokens*)*2);
            node->token[0] = &token;

            token = scanner.nextToken();

            node->children = (Node**)malloc(sizeof(Node*)*4);

            node->children[0] = expr(depth);
            node->children[1] = ro(depth);
            node->children[2] = expr(depth);

            if(token.t_type == right_bracket_tk){
                token = scanner.nextToken();
                node->children[3] = stat(depth);
            }
            else{
                error(token, right_bracket_tk);
            }
        }
        else{
            error(token, left_bracket_tk);
        }
    }
    else{
        error(token, cond_tk);
    }
    return node;
}
//<loop>          ->      iter [ <expr> <RO> <expr> ] <stat>
Node* Parser::loop(int depth){
    Node* node = new Node(depth, "<loop>");
    depth++;
    if(token.t_type == iter_tk){
        token = scanner.nextToken();
        if(token.t_type == left_bracket_tk){
            node->children = (Node**)malloc(sizeof(Node*)*4);
            node->token = (tokens**)malloc(sizeof(tokens*)*2);

            node->token[0] = &token;
            token = scanner.nextToken();
            node->children[0] = expr(depth);
            node->children[1] = ro(depth);
            node->children[2] = expr(depth);

            if(token.t_type == right_bracket_tk){
                node->token[1] = &token;
                token = scanner.nextToken();
                node->children[3] = stat(depth);
            }else{
                error(token, right_bracket_tk);
            }
        }
        else{
            error(token, left_bracket_tk);
        }
    }
    else{
        error(token, iter_tk);
    }
    return node;
}
//<assign>        ->      Identifier  = <expr>
Node* Parser::assign(int depth){
    Node* node = new Node(depth, "<assign>");
    depth++;

    if(token.t_type == id_tk){
        node->token = (tokens**)malloc(sizeof(tokens*)*2);
        node->token[0] = &token;

        token = scanner.nextToken();

        if(token.t_type == equals_tk){
            node->token[1] = &token;

            token = scanner.nextToken();

            node->children = (Node**)malloc(sizeof(Node*));
            node->children[0] = expr(depth);
        }
        else{
            error(token, equals_tk);
        }
    }
    else{
        error(token, id_tk);
    }
    return node;
}
//<RO>            ->      <LT> | <EQ>  | >
Node* Parser::ro(int depth){
    Node* node = new Node(depth, "<RO>");
    depth++;
    if(token.t_type == greater_than_tk){
        node->token = (tokens**)malloc(sizeof(tokens*));
        node->token[0] = &token;
    }
    else if(token.t_type == equals_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = eq(depth);
    }
    else if(token.t_type == less_than_tk){
        node->children = (Node**)malloc(sizeof(Node*));
        node->children[0] = lt(depth);
    }
    else{
        error(token, greater_than_tk, less_than_tk, equals_tk);
    }
    return node;
}
//<EQ>            ->      < | > | empty
Node* Parser::eq(int depth){
    Node* node = new Node(depth, "<EQ>");
    depth++;
    tokens temp = token;
    token = scanner.nextToken();
    if(token.t_type == less_than_tk || token.t_type == greater_than_tk){
        node->token = (tokens**)malloc(sizeof(tokens*)*2);
        node->token[0] = &temp;
        node->token[1] = &token;
        token = scanner.nextToken();
    }
    else {
        node->token = (tokens**) malloc(sizeof(tokens*));
        node->token[0] = &temp;

    }
    return node;
}
//<LT>            ->      empty |  >
Node* Parser::lt(int depth){
    Node* node = new Node(depth, "<LT>");
    depth++;

    tokens temp = token;
    token = scanner.nextToken();

    if(token.t_type == greater_than_tk){
        node->token = (tokens**)malloc(sizeof(tokens*)*2);
        node->token[0] = &temp;
        node->token[1] = &token;
        token = scanner.nextToken();
    }
    else{
        node->token = (tokens**)malloc(sizeof(tokens*));
        node->token[0] = &temp;

    }
    return node;
}

void Parser::error(tokens token, token_type type){
    fprintf(stderr, "%d: Token of type %s expected received %s\n",token.line, tokenNames[type].c_str(),
            tokenNames[token.t_type].c_str());
    exit(EXIT_FAILURE);
}
void Parser::error(tokens token , token_type type1, token_type type2) {
    fprintf(stderr, "%d: Token of type %s or %s expected received %s\n",token.line, tokenNames[type1].c_str(),
            tokenNames[type2].c_str(), tokenNames[token.t_type].c_str());
    exit(EXIT_FAILURE);
}
void Parser::error(tokens token , token_type type1, token_type type2, token_type type3){
    fprintf(stderr, "%d: Token of type %s or %s or %s expected received %s\n",token.line, tokenNames[type1].c_str(),
            tokenNames[type2].c_str(), tokenNames[type3].c_str(), tokenNames[token.t_type].c_str());
    exit(EXIT_FAILURE);
}
void Parser::error(tokens token){
    fprintf(stderr, "%d: Unknown error occurred when trying to parse token of type %s\n",
            token.line, tokenNames[token.t_type].c_str());
    exit(EXIT_FAILURE);
}


//    void allocateChildren(int count, Node* node){
//    *node->children = (Node*)malloc(sizeof(Node*) * count);
//    for(int i = 0; i < count; i++){
//        node->children[i] =
//    }
