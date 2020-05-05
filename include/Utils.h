#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>

using namespace std;

class Utils
{
private:
    Utils();

public:
    /* Get all content of the file into string */
    static string GetFileString(const string& fileName);
    /* Get content of file into lines save on vector of strings */
    static vector<string> GetFileLines(const string& fileName);
    /* Split a line by a specific delimeter and get a vector of tokens */
    static vector<string> SplitLineByDelimeter(const string& line, const char& delimeter);
    /* Create a file with random letters */
    static void CreateFileWithRandomLetters(const string& fileName, int letters_num, unsigned int size);
    /* Check if map file is already exists */
    static bool FileIsExists(const string& fileName);
};

#endif