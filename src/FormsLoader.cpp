#include "FormsLoader.h"

void FormsLoader::AddFormManually(const string& form)
{
	this->form_data.push_back(form);
}

void FormsLoader::LoadFromFile(const string& file)
{
	vector<string> file_lines = Utils::GetFileLines(file);
	
	string final_form, form_extracted;
	unsigned int i = 0;
	for (string& line : file_lines)
	{
		// check if it fits to template of form file
		if (line[0] == '>') 
		{
			vector<string> line_tokens = Utils::SplitLineByDelimeter(line, '\t');
			
			// extract the form with spaces
			form_extracted = line_tokens[1];
			
			// remove all spaces in form
			form_extracted.erase(remove(form_extracted.begin(), form_extracted.end(), ' '), form_extracted.end());
			
			// get the form size
			unsigned int form_size = form_extracted[ARRAY_FORM_SIZE] - '0';
			
			// cut only relevant part of form
			final_form = form_extracted.substr(0, form_size);
			
			this->AddFormManually(final_form);
			
			i++;
		}
	}
}

vector<string>& FormsLoader::GetFormData()
{
	return this->form_data;
}