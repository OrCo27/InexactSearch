#ifndef INEXACTSEARCH_H
#define INEXACTSEARCH_H

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <math.h>

#define MAX_SEARCH_WORDS 150000

using namespace std;


class InexactSearch
{
protected:
	string input;
	string search_words;
	float min_similarity;
	int max_mismatch;
	int min_matches;
	int input_size;


	/* C'tor: 
	input - the input string for searching source
	min_similarity - minimum similarity search */
	InexactSearch(const string& input, int search_word_size, float min_similarity);

	/*
	check if there is a match between search word to the input 
	if there is a match - store it
	*/
	void DetermineMatch(int start_match_word_idx, int start_search_word_idx);
	virtual void SearchImplementation(int start_search_word_idx) = 0;
	vector<string> GetResults(unordered_map<int, int> matches);

public:
	double alg_time;
	int search_len;

	/*
	key -> start search word index
	value -> map that the key is start matching index and value is mismatch count 
	*/
	unordered_map<int, unordered_map<int, int>> search_words_results;

	/* Start find all similar matches */
	void Search();
	virtual string Name() = 0;

	/* Write to report file */
	void WriteResultsToFile(ofstream& ofile);
	int GetMaxMissMatches();
};

#endif