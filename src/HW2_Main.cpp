#include <iostream>
#include "FormsLoader.h"
#include "MapBuilder.h"
#include "NaiveAlg.h"
#include "BasicAlg.h"
#include <string>

using namespace std;


int main()
{
    const string forms_file_name = "input/forms_an2";
    const string map_file_name = "input/map_input1";  // IMPORTANT: change map file name in case of another input
    const string input_file_name = "input/rand_text.txt";
    const string output_file_name = "output/results.txt";
    const unsigned int input_size = 1000000;
    const float similar_match = 0.75;

    // ##### Generate a text file with a random text, and load it when exists #####
    if (!Utils::FileIsExists(input_file_name))
    {
        Utils::CreateFileWithRandomLetters(input_file_name, input_size);
    }

    const string input_text = Utils::GetFileString(input_file_name);
    
    // ######## Select a search word in size of S ######
    // X=4 (Average last id) => |S|=25-4=21 
    // Select a random word for search in size of |S|

    string search_word = "uhafobaoanfaseqffwfmr";
    //                    ^^-^^^-^-^^-^^-^^^^^^
    // full match:        uhtfobtornfuseaffwfmr

    // ############ Loading forms ##############
    
    FormsLoader forms_builder;
    forms_builder.LoadFromFile(forms_file_name);

    // Can Also Add Them Manually:
    // forms_builder.AddFormManually("1111");
    // forms_builder.AddFormManually("11101");
    

    // ##### Pre-Processing: Building Map ######

    cout << "Building Map as Pre-Processing Step.." << endl;
    MapBuilder map_builder(forms_builder, input_text);
    map_builder.BuildMap();

    //map_builder.SaveToFile(map_file_name);
    //map_builder.LoadFromFile(map_file_name);

   
    // ############# Running Algs ##############

    BasicAlg basic_alg(map_builder, input_text, search_word, similar_match);
    NaiveAlg naive_alg(input_text, search_word, similar_match);

    InexactSearch* algs[2] = { &basic_alg, &naive_alg };
    
    
    for (int i = 0; i < 2; i++)
    {
        string alg_name = algs[i]->Name();
        cout << "-- Start Searching by " + alg_name + "--"<< endl;

        algs[i]->Search();
        
        cout << "Found: " + to_string(algs[i]->results.size()) + " Matches!" << endl;
        cout << "Elapsed time for " + alg_name + " : " + to_string(algs[i]->alg_time) << endl;
    }
   
    // ##### Final Step: Writing Results to file ######
    ofstream ofile;
    ofile.open(output_file_name);
    
    // write header
    float min_sim_rate = similar_match * 100;
    double speed_rate = naive_alg.alg_time / basic_alg.alg_time;

    ofile << "Searching for word: \" " + search_word + " \"" << endl;
    ofile << "Minimum similarity rate required: " << to_string(min_sim_rate) << "%" << endl;
    ofile << "Maximum miss matches allowed: " << to_string(basic_alg.GetMaxMissMatches()) << endl;
    ofile << "Basic Alg is x" << speed_rate << " faster than Naive Alg" << endl;

    for (int i = 0; i < 2; i++)
    {
        // write current alg result to file
        algs[i]->WriteResultsToFile(ofile);
    }

    ofile.close();

    return 0;
}
