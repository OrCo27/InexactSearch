#include "InexactSearch.h"

InexactSearch::InexactSearch(const string& input, int search_word_size, float min_similarity)
{
	this->input = input;
    this->search_len = search_word_size;
	this->min_similarity = min_similarity;
    this->min_matches = ceil(search_word_size * min_similarity);
	this->max_mismatch = search_word_size - this->min_matches;
	this->input_size = input.length();
}

void InexactSearch::DetermineMatch(int start_match_word_idx, int start_search_word_idx)
{
    int missmatch_count = 0;
    int input_index = start_match_word_idx;
    int search_index = start_search_word_idx;
    bool matched = true;
    
    // in case of overflow, return false
    if (input_index + search_len > input_size)
        return;

    // in case of the same word between search and input
    if (input_index == search_index)
        return;

    // pass each letter in input and search word for checking of match
    for (int i = 0; i < search_len; i++, search_index++, input_index++)
    {
        // count mismatches, if it not reach to maximun - continue
        if (input[input_index] != input[search_index])
            missmatch_count++;

        // pass the maximum missmatches, stop searching
        if (missmatch_count > max_mismatch)
        {
            matched = false;
            break;
        }
    }

    // there is a match, add it to output map
    if (matched)
    {
        this->search_words_results[start_search_word_idx][start_match_word_idx] = missmatch_count;

        cout << "Found match in index: " << start_match_word_idx << " For search index: "<< start_search_word_idx << endl;
    }
}

void InexactSearch::Search()
{
    cout << Name() << " Starting Searching" << endl;

    // start measuring
    auto start_base = chrono::steady_clock::now();

    // perform algorithm for each search word in the text
    for (int start_search_word_idx = 0; start_search_word_idx < MAX_SEARCH_WORDS; start_search_word_idx++)
    {
        if (start_search_word_idx % 50000)
            cout << "Searching index: " << start_search_word_idx << endl;

        // start algorithom implementation
        SearchImplementation(start_search_word_idx);
    }

    // stop measuring
    auto end_base = chrono::steady_clock::now();

    // store ellapsed time
    this->alg_time = chrono::duration_cast<chrono::milliseconds>(end_base - start_base).count() / 1000.0;

    cout << Name() << " Searching Ended with: " << to_string(this->alg_time) << " seconds" << endl;
}

int InexactSearch::GetMaxMissMatches()
{
    return this->max_mismatch;
}


vector<string> InexactSearch::GetResults(unordered_map<int, int> matches)
{
    vector<string> results;
    for (auto& x : matches)
    {
        unsigned int match_index = x.first;
        int missmatch_count = x.second;
        string res_str;
        string match = input.substr(match_index, search_len);
        int matches_count = search_len - missmatch_count;
        double sim_rate = matches_count / double(search_len);
        
        res_str =  "-> Matched string: \" " + match + " \"\n";
        res_str += "-> Matched in index: " + to_string(match_index) + "\n";
        res_str += "-> Missed " + to_string(missmatch_count) + " matches!\n";
        res_str += "-> Similarity rate: " + to_string(sim_rate*100) + "%";

        results.push_back(res_str);
    }

    return results;
}

void InexactSearch::WriteResultsToFile(ofstream& ofile)
{
    //vector<string> results = GetResults();

    ofile << "\n###################################" << endl;
    ofile << "######### " << Name() << " Results #######" << endl;
    ofile << "###################################\n" << endl;
    ofile << "Elapsed time: " + to_string(alg_time) << " seconds\n" << endl;
    for (auto& search_result : search_words_results)
    {
        int search_word_idx = search_result.first;
        unordered_map<int, int> matches = search_result.second;

        string search_word = input.substr(search_word_idx, search_len);


        ofile << "## Search Word: " << search_word << " ##" << endl;
        ofile << "## Search Index : " << search_word_idx << "                                    ##" << endl;

        vector<string> results = GetResults(matches);

        for (size_t i = 0; i < results.size(); i++)
        {
            string str = results[i];
            int result_num = i + 1;

            ofile << "------->                 Result #" << to_string(result_num) << "               <-------" << endl;
            ofile << str << "\n" << endl;
        }
    }
}