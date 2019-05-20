//
// Created by Ben Cradick on 2019-05-14.
//

#include "Semantics.h"

#include <algorithm>
#include <string>
#include <stdexcept>
#include <iostream>


Semantics::Semantics()
{
    tos = -1;
    iter_count = 0;
    iter_str = "iter";
}

std::string Semantics::Semantics::generateAssembly(Node* root)
{
    global.insert({"T", "0"});
    if(root->child_count == 2)
    {
        return "LOAD 0\nPUSH\nSTACKW " + std::to_string(++tos) + block(root->children[1]) + "STOP";
    }

    else
    {
        return "LOAD 0\nPUSH\nSTACKW " + std::to_string(++tos) + block(root->children[0]) + "STOP";
    }
}

void Semantics::Semantics::setGlobal(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    if(root->token_count == 2)
    {
        if(root->token[1] == nullptr)
        {
            for(int i = 0; i < root->child_count; i++)
            {
                setGlobal(root->children[i]);
            }
            return;
        }
        if(root->token[0]->t_type == id_tk)
        {
            if(root->token[1]->t_type == int_tk && global.find(root->token[0]->instance) == global.end() )
            {
                global.insert({root->token[0]->instance, root->token[1]->instance});
            }
            else
            {
                std::fprintf(stderr, "var %s has already been defined in this scope\n", root->token[0]->instance.c_str());
                exit(EXIT_FAILURE);
            }
        }
        else if(root->token[1]->t_type == id_tk)
        {
            if(global.find(root->token[1]->instance) == global.end())
            {
                std::fprintf(stderr, "Trying to use var %s before initialization\n", root->token[1]->instance.c_str());
                exit(EXIT_FAILURE);
            }
        }
//        else
//        {
//            std::fprintf(stderr, "var %s is already defined in the global scope\n", root->token[0]->instance.c_str());
//            exit(EXIT_FAILURE);
//        }
    }

    else if(root->token_count == 1)
    {
        if(root->token[0]->t_type == id_tk && global.find(root->token[0]->instance) == global.end())
        {
            std::fprintf(stderr, "Trying to use var %s before initialization\n", root->token[0]->instance.c_str());
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < root->child_count; i++)
    {
        setGlobal(root->children[i]);
    }
}
std::string Semantics::block(Node* root)
{
    //pushing to the stack would happen here for any variables local to this block
    if(root->child_count == 2)
    {
        return stats(root->children[1]);
    }

    else
    {
        return stats(root->children[0]);
    }
}
std::string Semantics::expr(Node* root)
{
    return a(root->children[0]) + phrase(root->children[1]);
}
std::string Semantics::a(Node *root)
{
    return n(root->children[0]) + d(root->children[1]);
}
std::string Semantics::phrase(Node* root)
{
    if(root == nullptr)
    {
        return "";
    }

    else
    {
        return arithmetic(root);
    }
}
std::string Semantics::n(Node* root)
{
    return m(root->children[0]) + l(root->children[1]);
}
std::string Semantics::l(Node* root)
{
    if(root == nullptr)
    {
        return "";
    }
    return arithmetic(root);
}
std::string Semantics::d(Node* root)
{
    if(root == nullptr)
    {
        return "";
    }
    return arithmetic(root);
}
std::string Semantics::m(Node* root)
{
    if(root->token_count == 0)
    {
        return r(root->children[0]);
    }
    return arithmetic(root);
}
std::string Semantics::r(Node* root)
{
    if(root->token_count == 0)
    {
        return expr(root->children[0]);
    }
    return root->token[0]->instance;
}
std::string Semantics::mStat(Node *root)
{
    if(root == nullptr)
    {
        return "";
    }
    return stat(root->children[0]) + mStat(root->children[1]);
}
std::string Semantics::stats(Node *root)
{
    return mStat(root);
}
std::string Semantics::stat(Node *root)
{
    if(root->children[0]->name == "<in>")
    {
        return in(root->children[0]);
    }

    else if(root->children[0]->name == "<out>")
    {
        return out(root->children[0]);
    }

    else if(root->children[0]->name == "<block>")
    {
        return block(root->children[0]);
    }

    else if(root->children[0]->name == "<if>")
    {
        return _if(root->children[0]);
    }

    else if(root->children[0]->name == "<loop>")
    {
        return loop(root->children[0]);
    }

    else if(root->children[0]->name == "<assign>")
    {
        return assign(root->children[0]);
    }
    else
    {
        std::cerr << "Semantic Error: invalid expresssion type  found in statement\n";
        exit(EXIT_FAILURE);
    }
}
std::string Semantics::in(Node *root)
{
    return "READ " + root->token[0]->instance;
}
std::string Semantics::out(Node *root)
{
    return expr(root->children[0]) + "STORE T\nWRITE T\n";
}
std::string Semantics::_if(Node *root)
{
    std::string slug = conditionalHelper(root);
    std::string conditional = ro(root->children[1]);
    std::string iter = iter_str + std::to_string(iter_count);
    std::string out = "out" + std::to_string(iter_count);
    iter_count++;
    slug += conditional + "BR " + out +"\n" + iter + ": " + stat(root->children[3]);
    slug += out + ": ";
    return slug;

}
std::string Semantics::loop(Node *root)
{
    std::string slug = conditionalHelper(root);
    std::string conditional = ro(root->children[1]);
    std::string iter = iter_str + std::to_string(iter_count);
    std::string out = "out" + std::to_string(iter_count);
    iter_count++;
    slug += conditional + "BR " + out +"\n" + iter + ": " + stat(root->children[3]);
    slug += conditional + out +": ";
    return slug;
}
std::string Semantics::assign(Node* root){
    std::string slug = expr(root->children[0]) + "STORE T\n";
    slug +=  "COPY " + root->token[0]->instance + " T\n";
    return slug;

}
std::string Semantics::conditionalHelper(Node *root)
{
    std::string slug = expr(root->children[2]) + "STORE T\n";
    slug += expr(root->children[0]);
    slug += "SUB T\n";
    return slug;

}
std::string Semantics::ro(Node* root)
{
    if(root->token[0]->t_type == less_than_tk)
    {
        return lt(root->children[0]);
    }

    else if(root->token[0]->t_type == equals_tk)
    {
        return eq(root->children[0]);
    }

    else if(root->token[0]->t_type == greater_than_tk)
    {
        return greater();
    }

    else
    {
        std::cerr << "Semantics Error: Unknown token instead of relational operator.\n";
        exit(EXIT_FAILURE);
    }
}
std::string Semantics::eq(Node *root)
{
    if(root->token_count == 1)
    {
        if(root->token[0]->t_type == equals_tk)
        {
            return equal();
        }
        else
        {
            std::cerr << "Semantics Error: Unexpected token type found when generating semantics\n";
            exit(EXIT_FAILURE);
        }
    }

    else if(root->token_count == 2)
    {
         if (root->token[1]->t_type == less_than_tk)
         {
            return lesserEqual();
         }
         else if (root->token[1]->t_type == greater_than_tk)
         {
            return greaterEqual();
         }
         else
         {
             std::cerr << "Semantics Error: Unexpected token type found when generating semantics\n";
             exit(EXIT_FAILURE);
         }
    }

    else
    {
        std::cerr << "Semantics Error: Wrong number of relational operators found when generating semantics\n";
        exit(EXIT_FAILURE);
    }
}
std::string Semantics::lt(Node *root)
{
    if(root->token[0]->t_type == less_than_tk)
    {
        if(root->token_count == 1)
        {
            return lesser();
        }
        else if(root->token_count == 2)
        {
            if(root->token[1]->t_type == greater_than_tk)
            {
                return notEqual();
            }
        }
    }
    std::cerr << "Semantics Error: Unknown operator found when generating semantics\n";
    exit(EXIT_FAILURE);
}
std::string Semantics::equal()
{
    return "BRZERO " + iter_str + std::to_string(iter_count) + "\n";
}
std::string Semantics::greater()
{
    return "BRPOS " + iter_str + std::to_string(iter_count) + "\n" ;
}
std::string Semantics::lesser()
{
    return "BRNEG " + iter_str + std::to_string(iter_count) + "\n";
}
std::string Semantics::notEqual()
{
    return greater() + lesser();
}
std::string Semantics::greaterEqual()
{
    return "BRZPOS " + iter_str + std::to_string(iter_count) + "\n";
}
std::string Semantics::lesserEqual()
{
    return "BRZNEG " + iter_str + std::to_string(iter_count) + "\n";
}
//helper method that writes all mathematical operations, used so that stack operations have one point of failure in compiler.
std::string Semantics::arithmetic(Node *root)
{
    std::string prefix = "PUSH\nSTACKW " + std::to_string(++tos) + "\n";
    //broken up so that tos gets modified before call to expr
    prefix += arithHelper(root) + "\n" + "STORE T\n STACKR " + std::to_string(tos--) + "\nPOP\n";

    switch(root->token[0]->t_type)
    {
        case subtraction_tk :
            return prefix + "SUB T\n";
        case addition_tk :
            return prefix + "ADD T\n";
        case multiplication_tk :
            return prefix + "MULT T\n";
        case division_tk :
            return prefix  + "DIV T\n";
        case percent_tk :
            return prefix + mod();
        default:
            std::cerr << "Invalid semantics: unknown arithmetic token encountered\n";
            exit(EXIT_FAILURE);
    }
}
std::string Semantics::mod()
{
    std::string iteration_point = iter_str + std::to_string(iter_count);
    std::string slug = iteration_point + ": ";
    slug += "SUB T\n";
    slug += "BRZNEG " + iteration_point +"\n";
    slug += "MULT -1\n";
    iter_count++;
    return slug;
}
std::string Semantics::arithHelper(Node *root)
{
    switch(root->token[0]->t_type)
    {
        case subtraction_tk :
        case addition_tk :
            return expr(root->children[0]);
        case multiplication_tk :
            return n(root->children[0]);
        case division_tk :
            return a(root->children[0]);
        case percent_tk :
            return m(root->children[0]);
        default:
            std::cerr << "Invalid semantics: unknown arithmetic token encountered\n";
            exit(EXIT_FAILURE);
    }

}