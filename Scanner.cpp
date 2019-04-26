//
// Created by Ben Cradick on 2019-03-31.
//

#include "Scanner.h"
#include "FileManager.h"
#include <string.h>

//Helper functions prototypes for "Filter2" in suggestions









Scanner::Scanner(int argc, char **argv) : files(argc, argv){
    line = 1;
    std::getline(files.inputFile, buffer);
    char delimArray[20] = {'=',  '<',  '>',  ':',   '+',  '-',  '*',  '/',   '%',  '.', '(',  ')',
                           ',', '{', '}',  ';', '[',  ']', '&'};
    for(int i = 0; i <= 19; i++)
    {
        delims.insert(delimArray[i]);
    }

}
tokens Scanner::nextToken()
{
    tokens token;
    if(token_list.empty()) {


         token = getProtoToken();

        token_list.splice(token_list.end(), routeToken(token));
    }
    token = *token_list.begin();
    token_list.pop_front();

    return token;
}

//This function is the first filter to remove the white space and comments.
tokens Scanner::getProtoToken()
{
    //cBuff can be refactored to use STRING.at();
    size_t begin = 0;
    size_t end = 0;
    tokens proto;
    const char* cBuff = buffer.c_str();
    size_t i = 0;
    size_t comment_loc;
    if((comment_loc = buffer.find('&')) != std::string::npos){
        buffer.erase(buffer.begin() + comment_loc, buffer.end());
    }
    buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
    if(files.inputFile.eof() && buffer.empty())
    {
        proto.t_type = eof_tk;
        proto.line = line;
        proto.instance = "";
        return proto;
    }
    // ignore any lines who's remaining content is whitespace or a comment.
    if(buffer.empty())
    {
        std::getline(files.inputFile, buffer);
        line++;
        return getProtoToken();
    }
    try {
        while (delims.find(buffer.at(i)) == delims.end()) {

            end = i++;
        }
    }catch(const std::out_of_range& e){
        end++;
    }

    if(begin == end)
    {
        proto.instance = buffer.at(begin);
        buffer.erase(buffer.begin());
    }
    else
    {
        proto.instance = buffer.substr(begin, end + 1);
        buffer.erase(0, end + 1);
    }
    determineTokenType(&proto);
    proto.line = line;

    return proto;
}
std::list<tokens> Scanner::routeToken(tokens token)
{
    std::list<tokens> temp; // "token" list of tokens
    temp.push_back(token); // here because compiler didnt like this in the switch statement.
    switch (token.t_type)
    {
        case id_tk :
            return verifyId(token);
        case int_tk :
            return verifyInt(token);
        case operator_tk :
            return determineOperatorToken(token);
        case eof_tk :
            return temp;
        default:
            std::cerr << "Scanner Error: Invalid token" << token.instance << " at line " << token.line << std::endl;
            exit(EXIT_FAILURE);
    }
}
std::list<tokens> Scanner::Scanner::getKeyWordToken(tokens token)
{
    switch (token.instance.at(0))
    {
        case 'i' :
            return iKeyWord(token);
        case 'v' :
            return vKeyWord(token);
        case 'r' :
            return rKeyWord(token);
        case 's' :
            return sKeyWord(token);
        case 'p' :
            return pKeyWord(token);
        case 'c' :
            return cKeyWord(token);
        case 't' :
            return tKeyWord(token);
        case 'l' :
            return lKeyWord(token);
        default:
            std::list<tokens> temp; // "token" list of tokens
            temp.push_back(token);
            return temp;
    }
}
std::list<tokens> Scanner::verifyInt(tokens token)
{
    unsigned int i = 0;
    while(i < token.instance.size())
    {
        if(!isdigit(token.instance.at(i))) //if character i is not an integer.
        {
            std::cerr << "Scanner Error: Invalid integer representation " << token.instance << " at line " << token.line << std::endl;
            exit(EXIT_FAILURE);
        }
        i++;
    }
    std::list<tokens> temp; // "token" list of tokens
    temp.push_back(token);
    return temp;

}
std::list<tokens> Scanner::verifyId(tokens token)
{
    unsigned int i = 0;
    if(!islower(token.instance.at(i)))
    { //not lower case
        std::cerr << "Scanner Error: Token " << token.instance << " at line " << token.line
        << " is an invalid must start with lowercase letter" << std::endl;
        exit(EXIT_FAILURE);
    }
    i++;
    while(i < token.instance.size())
    {
        if(!isalnum(token.instance.at(i))) //if character at i is not alphanumeric
        {
            std::cerr << "Scanner Error: Identifier " << token.instance << " at line " << token.line << std::endl;
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return getKeyWordToken(token);
}
// [charScanner::]KeyWord helper functions, acts as filter2
std::list<tokens> Scanner::iKeyWord(tokens token)
{
    // parent list because i'll call functions recursively to build a list of all tokens that were generated from this proto token
    std::list<tokens> parent;
    if(token.instance.substr(0, 3) == "int")
    {
        token.t_type = int_tk;
        if(token.instance.length() == 3){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(3, std::string::npos);
        next.line = token.line;
        token.instance = "int";
        determineTokenType(&next);
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next)); //Route token recursion means the remainder of the token gets scanned independently.
    }
    else if(token.instance.substr(0, 4) == "iter")
    {
        token.t_type = iter_tk;
        if(token.instance.length() == 4){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(4, std::string::npos);
        next.line = token.line;
        token.instance = "iter";
        parent.push_back(token);
        determineTokenType(&next);
        parent.splice(parent.end(), routeToken(next));
    }
    else{
        parent.push_back(token);
    }

    return parent;
}
std::list<tokens> Scanner::vKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 4) == "void")
    {
        token.t_type = void_tk;
        if(token.instance.length() == 4){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(4, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "void";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next)); //Route token recursion means the remainder of the token gets scanned independently.
    }
    else if(token.instance.substr(0, 3) == "var")
    {
        token.t_type = var_tk;
        if(token.instance.length() == 3){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(3, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "var";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next)); //Route token recursion means the remainder of the token gets scanned independently.
    }
    else{
        parent.push_back(token);
    }
    return parent;

}
std::list<tokens> Scanner::rKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 6) == "return")
    {
        token.t_type = return_tk;
        if(token.instance.length() == 6){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(6, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "return";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next)); //Route token recursion means the remainder of the token gets scanned independently.
    }
    else{
        parent.push_back(token);
    }
    return parent;

}
std::list<tokens> Scanner::sKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 4) == "scan")
    {
        token.t_type = scan_tk;
        if(token.instance.length() == 4){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(4, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "scan";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next)); //Route token recursion means the remainder of the token gets scanned independently.
    }
    else{
        parent.push_back(token);
    }

    return parent;

}
std::list<tokens> Scanner::pKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 5) == "print")
    {
        token.t_type = print_tk;
        if(token.instance.length() == 5){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(5, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "print";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next)); //Route token recursion means the remainder of the token gets scanned independently.
    }
    else if(token.instance.substr(0, 7) == "program")
    {
        token.t_type = program_tk;
        if(token.instance.length() == 7){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(7, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "program";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next));
    }
    else{
        parent.push_back(token);
    }
    return parent;

}
std::list<tokens> Scanner::cKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 4) == "cond")
    {
        token.t_type = cond_tk;
        if(token.instance.length() == 4){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(4, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "cond";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next));
    }
    else{
        parent.push_back(token);
    }
    return parent;
}
std::list<tokens> Scanner::tKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 4) == "then")
    {
        token.t_type= then_tk;if(token.instance.length() == 4){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(4, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "then";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next));
    }
    else{
        parent.push_back(token);
    }

    return parent;
}
std::list<tokens> Scanner::lKeyWord(tokens token)
{
    std::list<tokens> parent;
    if(token.instance.substr(0, 3) == "let")
    {
        token.t_type = let_tk;
        if(token.instance.length() == 3){
            parent.push_back(token);
            return parent;
        }
        tokens next;
        next.instance = token.instance.substr(3, std::string::npos);
        next.line = token.line;
        determineTokenType(&next);
        token.instance = "let";
        parent.push_back(token);
        parent.splice(parent.end(), routeToken(next));

    }
    else{
        parent.push_back(token);
    }
    return parent;
}
void Scanner::determineTokenType(tokens *token){
    if(delims.find(token->instance.at(0)) != delims.end()){
        token->t_type = operator_tk;
    }
    else if(isdigit(token->instance.at(0))) {
        token->t_type = int_tk;
    }
    else{
        token->t_type = id_tk;
    }
}
std::list<tokens> Scanner::determineOperatorToken(tokens token){
    std::list<tokens> op_token;
    switch(token.instance.at(0)){
        case '=' :
            token.t_type = equals_tk;
            break;
        case '<' :
            token.t_type = less_than_tk;
            break;
        case '>' :
            token.t_type = greater_than_tk;
            break;
        case ':' :
            token.t_type = colon_tk;
            break;
        case '+' :
            token.t_type = addition_tk;
            break;
        case '-' :
            token.t_type = subtraction_tk;
            break;
        case '*' :
            token.t_type = multiplication_tk;
            break;
        case '/' :
            token.t_type = division_tk;
            break;
        case '%' :
            token.t_type = percent_tk;
            break;
        case '.' :
            token.t_type = period_tk;
            break;
        case '(' :
            token.t_type = left_parenthesis_tk;
            break;
        case ')' :
            token.t_type = right_parenthesis_tk;
            break;
        case '{' :
            token.t_type = left_curly_bracket_tk;
            break;
        case '}' :
            token.t_type = right_parenthesis_tk;
            break;
        case '[' :
            token.t_type = left_bracket_tk;
            break;
        case ']' :
            token.t_type = right_bracket_tk;
            break;
        case ';' :
            token.t_type = semi_colon_tk;
            break;
        default:
            std::cerr << "Scanner::determineOperatorToken: unknown character: " << token.instance.at(0) << std::endl;
            exit(EXIT_FAILURE);
    }
    op_token.push_back(token);
    return op_token;
}