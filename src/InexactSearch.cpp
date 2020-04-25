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

bool InexactSearch::DetermineMatch(unsigned int start_index)
{
    int missmatch_count = 0;
    string possible_match;

    // in case of overflow, return false
    if ((start_index < 0) || (start_index + search_len > input_size))
    {
        return false;
    }

    // take the part of possible match from original text
    possible_match = input.substr(start_index, search_len);
    
    bool matched = true;
    for (int j = 0; j < search_len; j++)
    {
        // count mismatches, if it not reach to maximun - continue
        if (possible_match[j] != search_words[j])
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
        MatchResult res_data;
        res_data.match = possible_match;
        res_data.missmatch_count = missmatch_count;

        this->results.insert(pair<unsigned int, MatchResult>(start_index, res_data));
    }

    return matched;
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
        MatchResult res = x.second;
        string res_str;
        int matches_count = search_len - res.missmatch_count;
        double sim_rate = matches_count / double(search_len);
        
        res_str =  "-> Matched string: \" " + res.match + " \"\n";
        res_str += "-> Matched in index: " + to_string(match_index) + "\n";
        res_str += "-> Missed " + to_string(res.missmatch_count) + " matches!\n";
        res_str += "-> Similarity rate: " + to_string(sim_rate*100) + "%\n";

        vector<string> forms = res.forms_matched;
        
        if (forms.size() > 0)
        {
            string forms_matches = "-> Forms matched: ";

            for (unsigned int i = 0; i < forms.size(); i++)
            {
                forms_matches += forms[i];
                if (i != forms.size() - 1)
                    forms_matches += ", ";
            }

            res_str += forms_matches;
        }

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