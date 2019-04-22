//
// Created by Ben Cradick on 2019-03-11.
//

#ifndef P1_FILEMANAGER_H
#define P1_FILEMANAGER_H

#include <iostream>
#include <fstream>


class FileManager {
public:

    explicit FileManager(int, char**);
    ~FileManager();

    std::fstream inputFile;

    std::string fileName;
    std::string inputFileName;

    bool tempFile = false;


};


#endif //P1_FILEMANAGER_H
