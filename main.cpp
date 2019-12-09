#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cctype>

using namespace std;

struct NewWord
{
	string word;
	vector<int> lines;
	vector<int> chapters;
};

void addword(string wordbuilt, int linecurr, int chaptercurr, vector<NewWord>& index)
{
	bool wordfound = false;
	for (int i0 = 0; i0 < index.size(); i0++)
	{
		if (index[i0].word == wordbuilt)
		{
			wordfound = true;
			bool linefound = false;
			for (int i1 = 0; i1 < index[i0].lines.size(); i1++)
			{
				if (index[i0].lines[i1] == linecurr)
				{
					linefound = true;
					break;
				}
			}
			if (not linefound)
			{
				index[i0].lines.push_back(linecurr);
			}
			bool chapfound = false;
			for (int i2 = 0; i2 < index[i0].chapters.size(); i2++)
			{
				if (index[i0].chapters[i2] == chaptercurr)
				{
					chapfound = true;
					break;
				}
			}
			if (not chapfound)
			{
				index[i0].chapters.push_back(chaptercurr);
			}
			break;
		}
	}
	if (not wordfound)
	{
		NewWord w;
		w.word = wordbuilt;
		w.lines.push_back(linecurr);
		w.chapters.push_back(chaptercurr);
		index.push_back(w);
	}
}

void scan(vector<NewWord>& index, ifstream& file, vector<string>& linec)
{
	char character;
	string wordbuilt = "";
	string linebuilt = "";
	int linecurr = 1;
	int chaptercurr = 0;

	while (file.get(character))
	{
		if (character != '\n')
		{
			linebuilt += character;
			if (isalnum(character))
			{
				wordbuilt += tolower(character);
			}
		}
		if (isspace(character))
		{
			if (wordbuilt != "")
			{
				addword(wordbuilt, linecurr, chaptercurr, index);
				if (wordbuilt == "chapter")
				{
					chaptercurr++;
				}
				wordbuilt = "";
			}
			if (character == '\n')
			{
				linec.push_back(linebuilt);
				linebuilt = "";
				linecurr++;
			}
		}
	}
}

string actions_menu()
{
	string action;
	cout << "Print Index (I + Enter)" << endl;
	cout << "Search for Word (S + Enter)" << endl;
	cout << "Stop (Q + Enter)" << endl;
	cout << ">> ";
	cin >> action;
	return action;
}

void search_word(vector<NewWord>& index, vector<string>& linec)
{
	string searchfor;
	cout << "Enter the Word: ";
	cin >> searchfor;

	for (int w = 0; w < index.size(); w++)
	{
		if (index[w].word == searchfor)
		{
			cout << endl << "Word: " << index[w].word << endl << "Chapters: ";
			for (int i0 = 0; i0 < index[w].chapters.size(); i0++)
			{
				cout << index[w].chapters[i0] << ",";
			}
			cout << endl << "Lines: ";
			for (int i1 = 0; i1 < index[w].lines.size(); i1++)
			{
				cout << index[w].lines[i1] << ",";
			}
			cout << endl << endl;
			for (int i2 = 0; i2 < index[w].lines.size(); i2++)
			{
				cout << index[w].lines[i2] - 1 << " " << linec[index[w].lines[i2] - 2] << endl;
				cout << index[w].lines[i2] << " " << linec[index[w].lines[i2] - 1] << endl;
				cout << index[w].lines[i2] + 1 << " " << linec[index[w].lines[i2]] << endl;
				if (i2 != index[w].lines.size() - 1)
				{
					cout << "********************" << endl;
				}
			}
			break;
		}	
	}
	cout << endl;
}

void print_index(vector<NewWord>& index)
{
	cout << endl;
	for (int i0 = 0; i0 < index.size(); i0++)
	{
		cout << index[i0].word << ",[";
		for (int i1 = 0; i1 < index[i0].chapters.size(); i1++)
		{
			cout << index[i0].chapters[i1] << ",";
		}
		cout << "],(";
		for (int i2 = 0; i2 < index[i0].lines.size(); i2++)
		{
			cout << index[i0].lines[i2] << ",";
		}
		cout << ")" << endl;
	}
	cout << endl;
}

int main()
{
	ifstream file("alice.txt");	
	vector<NewWord> index;
	vector<string> linec;
	scan(index, file, linec);
	bool continue_program = true;
	while (continue_program)
	{
		string decision = actions_menu();
		if (decision == "i")
		{
			print_index(index);
		}
		else if (decision == "s")
		{
			search_word(index, linec);
		}
		else if (decision == "q")
		{
			continue_program = false;
		}
		else
		{
			cout << endl << "Not a valid input." << endl << endl;
		}
	}
	return 0;
}
