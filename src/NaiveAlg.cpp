#include "NaiveAlg.h"

NaiveAlg::NaiveAlg(const string& input, const string& search_words, float min_similarity)
    : InexactSearch(input, search_words, min_similarity) { }

void NaiveAlg::SearchImplementation()
{
    // iterate over every group in size of search word and check if it match
    for (unsigned int i = 0; i <= input_size - search_len; i++)
    {
        DetermineMatch(i);
    }
}

string NaiveAlg::Name()
{
    return "Naive Algorithm";
}
