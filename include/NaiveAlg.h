#ifndef NAIVEALG_H
#define NAIVEALG_H

#include "InexactSearch.h"

class NaiveAlg : public InexactSearch
{
public:
	NaiveAlg(const string& input, const string& search_words, float min_similarity = 0.75);

	string Name();

protected:
	void SearchImplementation();
};

#endif