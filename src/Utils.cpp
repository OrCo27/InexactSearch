#include "Utils.h"

string Utils::GetFileString(const string& fileName)
{
    ifstream inFile;
    inFile.open(fileName); //open the input file

    stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    string str = strStream.str(); //str holds the content of the file

    return str;
}

vector<string> Utils::GetFileLines(const string& fileName)
{
    vector<string> lines;
    // Open the File
    ifstream in(fileName.c_str());
    // Check if object is valid
    if (!in)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return lines;
    }
    
    string str;
    // Read the next line from File untill it reaches the end.
    while (getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            lines.push_back(str);
    }
    //Close The File
    in.close();
    return lines;
}

vector<string> Utils::SplitLineByDelimeter(const string& line, const char& delimeter)
{
    vector<string> tokens;

    istringstream iss(line);
    string token;
    while (std::getline(iss, token, delimeter))
        tokens.push_back(token);

    return tokens;
}

void Utils::CreateFileWithRandomLetters(const string& fileName, unsigned int size)
{
    ofstream rand_letters_file;
    rand_letters_file.open(fileName);

    for (unsigned int i = 0; i < size; i++)
    {
        char rand_ch = 'a' + rand() % 26;
        rand_letters_file << rand_ch;
    }

    rand_letters_file.close();
}

bool Utils::FileIsExists(const string& fileName)
{
    ifstream infile(fileName);
    return infile.good();
}