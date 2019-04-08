//
// Created by Ben Cradick on 2019-03-31.
//

#include "Scanner.h"
#include "FileManager.h"
#include <string.h>

//Helper functions prototypes for "Filter2" in suggestions

tokens iKeyWord(tokens token);
tokens vKeyWord(tokens token);
tokens rKeyWord(tokens token);
tokens sKeyWord(tokens token);
tokens pKeyWord(tokens token);
tokens cKeyWord(tokens token);
tokens tKeyWord(tokens token);
tokens lKeyWord(tokens token);


Scanner::Scanner(int argc, char **argv) : files(argc, argv){
    line = 1;
    std::getline(files.inputFile, buffer);
    char delimArray[21] = {'=',  '<',  '>',  ':',   '+',  '-',  '*',  '/',   '%',  '.', '(',  ')',
                           ',', '{', '}',  ';', '[',  ']', ' ', '\n', '&'};
    for(int i = 0; i <= 21; i++)
    {
        delims.insert(delimArray[i]);
    }

}
tokens Scanner::nextToken()
{
    tokens token = getProtoToken();
    token = routeToken(token);
    return token;
}

//This function is the first filter to remove the white space and comments.
tokens Scanner::getProtoToken()
{
    //cBuff can be refactored to use STRING.at();
    int begin = 0;
    int end = 0;
    tokens proto;
    const char* cBuff = buffer.c_str();
    int i = 0;
    if(cBuff[i] == ' ')
    {
        while (cBuff[i] == ' ')
        {
            i++;
            begin = i;
        }
        buffer.erase(0, (unsigned long) begin);
        return getProtoToken();
    }
    if(files.inputFile.eof() && buffer.empty())
    {
        proto.t_type = eof_tk;
        proto.line = line;
        proto.instance = "";
        return proto;
    }
    // ignore any lines who's remaining content is whitespace or a comment.
    if(cBuff[i] == '&' || buffer.empty())
    {
        std::getline(files.inputFile, buffer);
        line++;
        return getProtoToken();
    }
    while(delims.find(cBuff[i]) == delims.end())
    {
        end = i;
        i++;
    }
    if(delims.find(buffer.at(0)) != delims.end()){
        proto.t_type = operator_tk;
    }
    else {
        proto.t_type = id_tk;
    }
    if(begin == end)
    {
        proto.instance = cBuff[begin];
        buffer.erase(0, (unsigned long)end + 1);
    }
    else
    {
        proto.instance = buffer.substr((unsigned long)begin,(unsigned long)(end + 1 - begin));
        buffer.erase(0, (unsigned long) end + 1);
    }
    proto.line = line;

    return proto;
}
tokens Scanner::routeToken(tokens token)
{
    switch (token.t_type)
    {
        case id_tk :
            return verifyId(token);
        case int_tk :
            return verifyInt(token);
        case operator_tk :
            return token;
        case eof_tk :
            return token;
        default:
            std::cerr << "Scanner Error: Invalid token" << token.instance << " at line " << token.line << std::endl;
            exit(EXIT_FAILURE);
        }
}
tokens Scanner::getKeyWordToken(tokens token)
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
            return token;
    }
}
tokens Scanner::verifyInt(tokens token)
{
    int i = 0;
    while(i < token.instance.size())
    {
        if(!isnumber(token.instance.at(i))) //if character i is not an integer.
        {
            std::cerr << "Scanner Error: Invalid integer representation " << token.instance << " at line " << token.line << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return token;
}
tokens Scanner::verifyId(tokens token)
{
    int i = 0;
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
// [char]KeyWord helper functions, acts as filter2
tokens iKeyWord(tokens token)
{
    if(token.instance == "int")
    {
        token.t_type = int_tk;
    }
    else if(token.instance == "iter")
    {
        token.t_type = iter_tk;
    }

    return token;


}
tokens vKeyWord(tokens token)
{
    if(token.instance == "void")
    {
        token.t_type = void_tk;
    }
    else if(token.instance == "var")
    {
        token.t_type = var_tk;
    }
    return token;

}
tokens rKeyWord(tokens token)
{
    if(token.instance == "return")
    {
        token.t_type = return_tk;
    }
    return token;

}
tokens sKeyWord(tokens token)
{
    if(token.instance == "scan")
    {
        token.t_type = scan_tk;
    }

    return token;

}
tokens pKeyWord(tokens token)
{
    if(token.instance == "print")
    {
        token.t_type = print_tk;
    }
    else if(token.instance == "program")
    {
        token.t_type = program_tk;
    }
    return token;

}
tokens cKeyWord(tokens token)
{
    if(token.instance == "cond")
    {
        token.t_type = cond_tk;
    }
    return token;
}
tokens tKeyWord(tokens token)
{
    if(token.instance == "then")
    {
        token.t_type= then_tk;
    }

    return token;
}
tokens lKeyWord(tokens token)
{
    if(token.instance == "let")
    {
        token.t_type = let_tk;

    }
    return token;
}