#include "NaiveAlg.h"

NaiveAlg::NaiveAlg(const string& input, int search_word_size, float min_similarity)
    : InexactSearch(input, search_word_size, min_similarity) { }

void NaiveAlg::SearchImplementation(int start_search_word_idx)
{
    // iterate over every group in size of search word and check if it match
    for (int start_match_word_idx = 0; start_match_word_idx <= input_size - search_len; start_match_word_idx++)
    {
        DetermineMatch(start_match_word_idx, start_search_word_idx);
    }
}

string NaiveAlg::Name()
{
    return "Naive Algorithm";
}
