#ifndef BASICALG_H
#define BASICALG_H

#include "InexactSearch.h"
#include "FormsLoader.h"
#include "MapBuilder.h"

class BasicAlg : public InexactSearch
{
private:
	FormsLoader forms;
	unordered_map<string, vector<unsigned int>> map_text_input;

public:
	BasicAlg(MapBuilder map_text_builder, const string& input, const string& search_words, float min_similarity = 0.75);

	string Name();

protected:
	void SearchImplementation();
};

#endif