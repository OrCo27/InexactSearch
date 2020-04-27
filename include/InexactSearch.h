#ifndef INEXACTSEARCH_H
#define INEXACTSEARCH_H

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;

struct MatchResult
{
	int missmatch_count = 0;
	string match;
};

class InexactSearch
{
protected:
	string input;
	string search_words;
	float min_similarity;
	int max_mismatch;
	int min_matches;
	int search_len;
	int input_size;


	/* C'tor: 
	input - the input string for searching source
	search_words - the text for search in the whole text
	min_similarity - minimum similarity search */
	InexactSearch(const string& input, const string& search_words, float min_similarity);

	/*
	check if there is a match between search word to the input 
	if there is a match - store it
	*/
	void DetermineMatch(int start_index);
	virtual void SearchImplementation() = 0;
	vector<string> GetResults();

public:
	double alg_time;
	/* save starting index as key and details about the match as value */
	unordered_map<int, MatchResult> results;


	void Search();
	virtual string Name() = 0;
	void WriteResultsToFile(ofstream& ofile);
	unsigned int GetMaxMissMatches();
};

#endif