#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include "FormsLoader.h"
#include "Utils.h"

using namespace std;

class MapBuilder
{
private:
	string source;
	FormsLoader forms;
	/* save a map for each word that match to forms as key, 
	and a vector of indexes that it apears in input 
	unordered_map preferred from standard map for key searches and inserting */
	unordered_map<string, vector<unsigned int>> map_build;

public:
	MapBuilder(const FormsLoader& forms, const string& source);
	/* Building the map based on forms and input source */
	void BuildMap();
	/* Load an existing map file */
	void LoadFromFile(const string& fileName);
	/* Save a new map file */
	void SaveToFile(const string& fileName);
	
	/* Getters */
	unordered_map<string, vector<unsigned int>> GetMapData();
	FormsLoader GetForms();
};

#endif