//
// Created by Ben Cradick on 2019-03-31.
//

#include "Scanner.h"
#include "FileManager.h"
#include <string.h>


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
    return token;
}

//This function is the first filter to remove the white space and comments.
tokens Scanner::getProtoToken()
{
    int begin = 0;
    int end = 0;
    tokens proto;
    const char* cBuff = buffer.c_str();
    int i = 0;
    if(cBuff[i] == ' ')
    {
        while (cBuff[i] == ' ') {
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
    proto.t_type = id_tk;
    return proto;
}
tokens Scanner::routeToken(tokens token)
{
switch (token.t_type){
    case id_tk :
        return getKeyWordToken(token);
    case int_tk :
        return verifyInt(token);
    case op_delim_tk :
        return token;
    case eof_tk :
        return token;
    default:
        std::cerr << "Invalid token" << token.instance << " at line " << token.line << std::endl;
        exit(EXIT_FAILURE);
    }
}
tokens Scanner::getKeyWordToken(tokens token) {}
tokens Scanner::verifyInt(tokens token){}

