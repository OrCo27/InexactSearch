#include "BasicAlg.h"

BasicAlg::BasicAlg(MapBuilder map_text_builder, const string& input, const string& search_words, float min_similarity)
    : InexactSearch(input, search_words, min_similarity)
{
    map_text_input = map_text_builder.GetMapData();
    forms = map_text_builder.GetForms();
}

void BasicAlg::SearchImplementation()
{
    // build a map for the search words
    MapBuilder map_search_builder(forms, search_words);
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
                int start_index = map_idx - pattern_index;

                // check if there is a match, only when we didn't pass it yet
                if (this->results.find(start_index) == this->results.end())
                {
                    DetermineMatch(start_index);
                }
            }
        }
    }
}

string BasicAlg::Name()
{
    return "Basic Algorithm";
}