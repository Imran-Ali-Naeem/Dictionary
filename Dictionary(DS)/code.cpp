#include<iostream>
#include<conio.h>
#include<vector>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<cstdlib>

using namespace std;

class Dictionary
{
public:
	Dictionary* children[93];
	bool isWordEnd;
	string meaning;

	Dictionary()
	{
		isWordEnd = false;

		for (int i = 0; i < 93; i++)
		{
			children[i] = 0;
		}
		meaning = "";
	}
};


class Dic
{
public:
	Dictionary* root;
	Dic()
	{
		root = new Dictionary;
	}

	bool insert(string word, string meaning)
	{
		Dictionary* temp = root;
		int key;
		for (int i = 0; i < word.length(); i++)
		{
			key = word[i] - 33;
			if (temp->children[key] == 0)
			{
				temp->children[key] = new Dictionary;
			}
			temp = temp->children[key];

		}
		if (temp->isWordEnd == true)
		{
			//	cout << "\nWord Already Exist\n\n";
			return false;
		}

		temp->isWordEnd = true;
		temp->meaning = meaning;
		return true;
	}

	bool search(string word)
	{
		Dictionary* temp = root;

		for (int i = 0; i < word.length(); i++)
		{
			int key = word[i] - 33;
			if (!temp->children[key])
			{
				return false;
			}
			temp = temp->children[key];
		}

		if (temp->isWordEnd == true)
		{
			cout << setfill(' ');
			cout << setfill('-') << setw(62) << "-" << endl;
			cout << left << setw(30) << "| Word                        " << left << setw(30) << " | Meaning                    " << " |" << endl;
			cout << setfill('-') << setw(62) << "-" << endl;
			cout << setfill(' ');
			cout << "| " << setw(29) << left << word << "| " << setw(27) << left << temp->meaning << " |\n";
			cout << setfill('-') << setw(62) << "-" << endl;
		}
		return temp->isWordEnd;
	}


	void update(string word)
	{
		Dictionary* temp = root;

		for (int i = 0; i < word.length(); ++i)
		{
			int key = word[i] - 33;
			if (!temp->children[key])
			{
				cout << "\nWord not found!\n\n";
				return;
			}
			temp = temp->children[key];
		}

		if (temp->isWordEnd == false)
		{
			cout << "\nWord not found!\n\n";
			return;
		}
		else
		{
			cout << setfill(' ');
			cout << setfill('-') << setw(62) << "-" << endl;
			cout << left << setw(30) << "| Word                        " << left << setw(30) << " | Meaning                    " << " |" << endl;
			cout << setfill('-') << setw(62) << "-" << endl;
			cout << setfill(' ');
			cout << "| " << setw(29) << left << word << "| " << setw(27) << left << temp->meaning << " |\n";
			cout << setfill('-') << setw(62) << "-" << endl;

			cout << "Do you Wand to Update?\nPress '1' to Update\nPress '2' to Quit\nPlease Input == ";
			string choice;
			cin >> choice;

			if (choice == "1")
			{
				string newMeaning;

				cout << "Please Enter New Meaing == ";
				cin >> newMeaning;

				temp->meaning = newMeaning;

				ifstream read("Dictionary.txt");
				ofstream open("temp.txt");
				string w, m;
				cout << "Updating >>>\n";

				while (!read.eof())
				{
					read >> w;
					read >> m;
					if (!read.eof())
					{
						if (w == word)
						{
							open << left << setw(50) << w << left << setw(50) << temp->meaning << endl;
						}
						else
						{
							open << left << setw(50) << w << left << setw(50) << m << endl;

						}
					}
				}
				read.close();
				open.close();
				remove("Dictionary.txt");
				int num = rename("temp.txt", "Dictionary.txt");


				cout << "Meaning Updated SuccessFully.\n";
			}
			else if (choice == "2")
			{
				return;
			}
		}
	}

	void deleteWord(string word)
	{
		Dictionary* temp = root;
		for (int i = 0; i < word.length(); i++)
		{
			int key = word[i] - 33;
			if (!temp->children[key])
			{
				cout << "\nWord not found!\n\n";
				return;
			}
			temp = temp->children[key];
		}

		if (temp->isWordEnd == false)
		{
			cout << "\nWord not found!\n\n";
			return;
		}
		else
		{
			cout << setfill(' ');
			cout << setfill('-') << setw(62) << "-" << endl;
			cout << left << setw(30) << "| Word                        " << left << setw(30) << " | Meaning                    " << " |" << endl;
			cout << setfill('-') << setw(62) << "-" << endl;
			cout << setfill(' ');
			cout << "| " << setw(29) << left << word << "| " << setw(27) << left << temp->meaning << " |\n";
			cout << setfill('-') << setw(62) << "-" << endl;


			cout << "\nDo you Want to Delete?\nPress '1' to Delete\nPress '2' to Quit\nPlease Input == ";
			string choice;
			cin >> choice;

			if (choice == "1")
			{
				temp->isWordEnd = false;

				ifstream read("Dictionary.txt");
				ofstream open("temp.txt");
				string w, m;
				cout << "Deleing >>> \n";

				while (!read.eof())
				{
					read >> w;
					read >> m;
					if (w != word)
					{
						open << endl << left << setw(50) << w << left << setw(50) << m << endl;

					}
				}
				read.close();
				open.close();
				remove("Dictionary.txt");
				int num = rename("temp.txt", "Dictionary.txt");
				cout << "Word Deleted SuccessFully\n";
			}
			else if (choice == "2")
			{
				return;
			}
		}
	}

	void load()
	{
		string word, meaning;
		system("cls");
		cout << endl;
		cout << setw(40) << " " << "->|----------------------------------|<-\n";
		cout << setw(40) << " " << "->|             DICTIONARY           |<-\n";
		cout << setw(40) << " " << "->|----------------------------------|<-\n\n";
		system("cls");
		ifstream read("Dictionary.txt");

		while (!read.eof())
		{
			read >> word;
			read >> meaning;


			if (word.length() != 0 && meaning.length() != 0)
			{
				insert(word, meaning);
			}

		}
		system("cls");

		read.close();

		cout << endl;
		cout << setfill(' ');
		cout << setw(40) << " " << "->|----------------------------------|<-\n";
		cout << setw(40) << " " << "->|             DICTIONARY           |<-\n";
		cout << setw(40) << " " << "->|----------------------------------|<-\n\n";
	}

	vector<string> wordSuggestions(string prefix)
	{
		vector<string> suggestions;
		Dictionary* t = root;

		for (int i = 0; i < prefix.length(); i++)
		{

			int key = prefix[i] - 33;
			if (!t->children[key])
			{
				return suggestions;
			}
			t = t->children[key];
		}

		collectSuggestions(t, prefix, suggestions);
		return suggestions;
	}

	void collectSuggestions(Dictionary* node, string currentPrefix, vector<string>& suggestions)
	{
		if (node == NULL)
		{
			return;
		}

		if (node->isWordEnd)
		{
			suggestions.push_back(currentPrefix);
		}

		for (int i = 0; i < 93; i++)
		{
			if (node->children[i] != NULL)
			{
				char ch = i + 33;
				collectSuggestions(node->children[i], currentPrefix + ch, suggestions);
			}
		}
	}

};

int main()
{
	Dic SFE;
	SFE.load();

	do
	{
		system("cls");
		cout << setfill('-') << setw(64) << "-" << endl;
		cout << setfill(' ');
		cout << setw(30) << "|          MENU          |" << endl;
		cout << setfill('-') << setw(64) << "-" << endl;
		cout << left << setw(30) << "| Option |        Action         |" << endl;
		cout << setfill('-') << setw(64) << "-" << endl;
		cout << setfill(' ');
		cout << left << setw(30) << "|   1    |        Search         |" << endl;
		cout << left << setw(30) << "|   2    |        Update         |" << endl;
		cout << left << setw(30) << "|   3    |        Delete         |" << endl;
		cout << left << setw(30) << "|   4    |        Add Word       |" << endl;
		cout << left << setw(30) << "|   5    |        Suggestions    |" << endl;
		cout << left << setw(30) << "|   6    |        Exit           |" << endl;
		cout << setfill('-') << setw(64) << "-" << endl;

		string x;
		cout << "\nPlease Input == ";
		cin >> x;

		if (x == "1")
		{
			system("cls");
			cout << "|     Search word     |" << endl;
			cout << "|_____________________|" << endl << endl << endl;
			string w;
			cout << "\nPlease Enter Word == ";
			cin >> w;
			if (!SFE.search(w))
			{
				cout << "Word not found\n"; 
			}
			cout << "\n\n press any key to continue";
			_getch();
		}
		else if (x == "2")
		{
			system("cls");
			cout << "|     update word     |" << endl;
			cout << "|_____________________|" << endl << endl << endl;
			string w;
			cout << "\nPlease Enter Word == ";
			cin >> w;
			SFE.update(w);
			cout << "\n\n press any key to continue";
			_getch();
		}
		else if (x == "3")
		{
			system("cls");
			cout << "|     delete word     |" << endl;
			cout << "|_____________________|" << endl << endl << endl;
			string w;
			cout << "\nPlease Enter Word == ";
			cin >> w;
			SFE.deleteWord(w);
			cout << "\n\n press any key to continue";
			_getch();
		}
		else if (x == "4")
		{
			system("cls");
			cout << "|     insert word     |" << endl;
			cout << "|_____________________|" << endl << endl << endl;
			string w, m;
			cout << "\nPlease Enter Word == ";
			cin >> w;
			cout << "Please Enter Meaning == ";
			cin >> m;

			if (SFE.insert(w, m))
			{
				ofstream open("Dictionary.txt", ios::app);
				open << w << "\t" << m << endl;
				open.close();
				cout << "\nWord Inserted Successfully\n";
			}
			cout << "\n\n press any key to continue";
			_getch();
		}
		else if (x == "5")
		{
			system("cls");
			cout << "|     suggestion word     |" << endl;
			cout << "|_________________________|" << endl << endl << endl;
			string prefix;
			cout << "\nEnter Short Word == ";
			cin >> prefix;

			vector<string> suggestions = SFE.wordSuggestions(prefix);

			cout << "Word Suggestions == \n";
			if (suggestions.empty())
			{
				cout << "No suggestions found.\n";
				cout << "\n\n press any key to continue";
				_getch();
				continue;
			}
			else
			{
				int size = (suggestions.size());
				int numSuggestions = min(10, size);

				cout << endl;
				cout << setfill('-') << setw(25) << "-" << endl;
				cout << left << setw(21) << "|    Suggestions     " << "   |\n";
				cout << setfill('-') << setw(25) << "-" << endl;

				for (int i = 0; i < numSuggestions; i++)
				{
					cout << setfill(' ');
					cout << "|-> " << left << setw(19) << suggestions[i] << " |" << endl;
					cout << setfill('-') << setw(25) << "-" << endl;
				}
			}
			cout << "\n\n press any key to continue";
			_getch();
		}
		else if (x == "6")
		{
			break;
		}
	} while (1);

	system("pause");
}