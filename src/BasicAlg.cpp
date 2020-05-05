#include "BasicAlg.h"

BasicAlg::BasicAlg(MapBuilder map_text_builder, const string& input, int search_word_size, float min_similarity)
    : InexactSearch(input, search_word_size, min_similarity)
{
    map_text_input = map_text_builder.GetMapData();
    forms = map_text_builder.GetForms();
}

void BasicAlg::SearchImplementation(int start_search_word_idx)
{
    // build a map for the search words
    string search_word = input.substr(start_search_word_idx, search_len);
    MapBuilder map_search_builder(forms, search_word);
    map_search_builder.BuildMap();

    // get map generated on search words
    unordered_map<string, vector<unsigned int>> map_search = map_search_builder.GetMapData();

    // iterate over every word template in search map 
    for (auto& x : map_search)
    {
        string pattern = x.first;
        unsigned int pattern_index = x.second[0]; // take only the first occures

        // if word template found in the big map of original input, check every index that stored
        if (map_text_input.find(pattern) != map_text_input.end())
        {
            // current sub word found in the map
            vector<unsigned int> map_indexes = map_text_input[pattern];

            // iterate over each index that stored by current sub word
            for (unsigned int map_idx : map_indexes)
            {
                // get the position of start search word
                int start_match_index = map_idx - pattern_index;

                // in case of negative index
                if (start_match_index < 0)
                    continue;

                // check if there is a match, only when we didn't pass it yet
                bool exists = false;
                if (this->search_words_results.find(start_search_word_idx) != this->search_words_results.end())
                {
                    unordered_map<int, int> search_matches = this->search_words_results[start_search_word_idx];
                    if (search_matches.find(start_match_index) != search_matches.end())
                    {
                        exists = true;
                    }
                }
               
                if (!exists)
                {
                    DetermineMatch(start_match_index, start_search_word_idx);
                }
            }
        }
    }
}

string BasicAlg::Name()
{
    return "Basic Algorithm";
}