#include "MapBuilder.h"

MapBuilder::MapBuilder(const FormsLoader& forms, const string& source)
{
	this->forms = forms;
	this->source = source;
}

void MapBuilder::BuildMap()
{
    vector<string> forms = this->forms.GetFormData();
    string input = this->source;

    // iterate over each form in forms list
    for (string& form : forms)
    {
        unsigned int form_size = form.length();
        // pass over groups of form size with word overlapping
        for (unsigned int i = 0; i <= input.length() - form_size; i++)
        {
            string pattern;
            string sub_word = input.substr(i, form_size);

            // pass over each character for matching between form to sub-word
            for (unsigned int j = 0; j < form_size; j++)
            {
                if (form[j] == '1')  // need keep input character
                    pattern += sub_word[j];
                else
                    pattern += '-';
            }

            if (this->map_build.find(pattern) == this->map_build.end()) 
            {
                // not found, add this sub word to map with it's index
                vector<unsigned int> indexes_vect = { i };
                this->map_build.insert(pair<string, vector<unsigned int>>(pattern, indexes_vect));
            }
            else
            {
                // found this subword, so add the index to indexes vector
                this->map_build.at(pattern).push_back(i);
            }
        }
    }
}

void MapBuilder::SaveToFile(const string& fileName)
{
    ofstream outfile;
    outfile.open(fileName);
    
    string line;
    for (auto& x : this->map_build)
    {
        line = x.first + '\t';
        for (unsigned int index : x.second)
        {
            line += to_string(index) + " ";
        }
        
        outfile << line << endl;
    }
    outfile.close();
}

void MapBuilder::LoadFromFile(const string& fileName)
{
    this->map_build.clear(); // clean map first
    vector<string> map_lines = Utils::GetFileLines(fileName);

    string form, indexes;
    for (string& line : map_lines)
    {
        // extract form and it's indexes
        vector<string> line_tokens = Utils::SplitLineByDelimeter(line, '\t');
        form = line_tokens[0];
        indexes = line_tokens[1];

        // convert indexes string to vector
        vector<string> str_indexes_vect = Utils::SplitLineByDelimeter(indexes, ' ');
        vector<unsigned int> indexes_vect;

        for (string& str_idx : str_indexes_vect)
        {
            unsigned int idx = stoul(str_idx);
            indexes_vect.push_back(idx);
        }

        // add to map
        this->map_build.insert(pair<string, vector<unsigned int>>(form, indexes_vect));
    }
}

unordered_map<string, vector<unsigned int>> MapBuilder::GetMapData()
{
    return this->map_build;
}

FormsLoader MapBuilder::GetForms()
{
    return this->forms;
}