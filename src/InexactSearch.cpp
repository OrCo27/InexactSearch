#include "InexactSearch.h"

InexactSearch::InexactSearch(const string& input, const string& search_words, float min_similarity)
{
	this->input = input;
	this->search_words = search_words;
	this->min_similarity = min_similarity;
    this->min_matches = ceil(search_words.length() * min_similarity);
	this->max_mismatch = search_words.length() - this->min_matches;
	this->search_len = search_words.length();
	this->input_size = input.length();
}

void InexactSearch::DetermineMatch(int start_index)
{
    int missmatch_count = 0;
    int input_index = start_index;
    bool matched = true;
    
    // in case of overflow, return false
    if ((start_index < 0) || (start_index + search_len > input_size))
    {
        return;
    }

    for (int i = 0; i < search_len; i++)
    {
        // count mismatches, if it not reach to maximun - continue
        if (input[input_index] != search_words[i])
            missmatch_count++;

        // pass the maximum missmatches, stop searching
        if (missmatch_count > max_mismatch)
        {
            matched = false;
            break;
        }

        input_index++;
    }

    // there is a match, add it to output map
    if (matched)
    {
        this->results.insert(pair<int, int>(start_index, missmatch_count));
    }
}

void InexactSearch::Search()
{
    // start measuring
    auto start_base = chrono::steady_clock::now();

    // start algorithom implementation
    SearchImplementation();

    // stop measuring
    auto end_base = chrono::steady_clock::now();

    // store ellapsed time
    this->alg_time = chrono::duration_cast<chrono::milliseconds>(end_base - start_base).count() / 1000.0;
}

unsigned int InexactSearch::GetMaxMissMatches()
{
    return this->max_mismatch;
}

vector<string> InexactSearch::GetResults()
{
    vector<string> results;
    for (auto& x : this->results)
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
    vector<string> results = GetResults();

    ofile << "\n###################################" << endl;
    ofile << "######### " << Name() << " Results #######" << endl;
    ofile << "###################################" << endl;
    ofile << "Found: " + to_string(results.size()) + " matches!" << endl;
    ofile << "Elapsed time: " + to_string(alg_time) << " seconds\n" << endl;

    for (size_t i = 0; i < results.size(); i++)
    {
        string str = results[i];
        int result_num = i + 1;

        ofile << "------->                 Result #" << to_string(result_num) << "               <-------" << endl;
        ofile << str << "\n" << endl;
    }
}