#ifndef FORMSLOADER_H
#define FORMSLOADER_H

#include <vector>
#include <string>
#include <algorithm>
#include "Utils.h"

#define ARRAY_FORM_SIZE 21
#define FILE_FORM_LENGTH 43 // the length of form template in file (include spaces)
using namespace std;


class FormsLoader
{
private:
	vector<string> form_data;
	
public:
	/* Load a form from existing file */
	void LoadFromFile(const string& file);
	/* Add form manually in syntax of 1 or 0, ex: "110011" */
	void AddFormManually(const string& form);

	/* Getter */
	vector<string>& GetFormData();
};

#endif