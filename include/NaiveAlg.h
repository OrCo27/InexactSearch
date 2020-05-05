#ifndef NAIVEALG_H
#define NAIVEALG_H

#include "InexactSearch.h"

class NaiveAlg : public InexactSearch
{
public:
	NaiveAlg(const string& input, int search_word_size, float min_similarity = 0.75);

	string Name();

protected:
	void SearchImplementation(int start_search_word_idx);
};

#endif