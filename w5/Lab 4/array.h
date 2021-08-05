#pragma once
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 
struct dict
{
	string word;
	string mean;
};
dict* addNew(dict myDict[], int &size, string word, string mean);
//int readFile(string fileName, dict myDict[]);
dict* readFile(string fileName, int &size);
void sortDict(dict myDict[], int left, int right);
int searchDict(dict myDict[], int size, string key);
void outputToFile(string fileName, dict myDict[], int size);
dict* addNew(dict myDict[], int &size);
void editWord(dict myDict[], int size);
dict* deleteWord(dict myDict[], int &size);
void doArr()
{
	string fileName;// = "Oxford English Dictionary.txt";
	int size = 0;
	dict * myDict;
	begin:
	cout << "Input filename to import data: ";
	getline(cin, fileName);
	auto start = high_resolution_clock::now();
	myDict = readFile(fileName, size);
	//unable to read
	if(size == -1)
	{
		cout << endl;
		goto begin;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Loaded " << fileName << " in: " << duration.count() << "ms.\n";
	////for debugging
	//outputToFile("readFile.txt", myDict, size);
	start = high_resolution_clock::now();
	sortDict(myDict, 0, size - 1);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	////for debugging
	//outputToFile("sortedFile.txt", myDict, size);
	cout << "Dictionary is sorted in: " << duration.count() << "ms.\n\n";
	int choice;

	do
	{
		cout << "NOTE: CASE SENSITIVE.\n";
		cout << "[1] Look up\n";
		cout << "[2] Edit\n";
		cout << "[3] Add\n";
		cout << "[4] Delete\n";
		cout << "[5] Save\n";
		cout << "[0] Go back\n";
		do
		{
			cout << "Your choice: ";
			cin >> choice;
			cin.ignore();
		} while (choice < 0 || choice > 5);
		switch(choice)
		{
			case 1:
			{
				string key;
				int pos;

				cout << "Enter a word to lookup: ", getline(cin, key);
				start = high_resolution_clock::now();
				pos = searchDict(myDict, size, key);
				//cin.get(); //test stop
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				if(pos != -1)
				{
					cout << myDict[pos].word << ": " << myDict[pos].mean << endl;
				}
				else
					cout << "This word is not in dictionary.\n";
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 2:
			{
				editWord(myDict, size);
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 3:
			{
				myDict = addNew(myDict, size);
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 4:
			{
				myDict = deleteWord(myDict, size);
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 5:
			{
				string fileNameOut;
				cout << "Enter file name to save (must has .txt): ";
				getline(cin, fileNameOut);
				start = high_resolution_clock::now();
				outputToFile(fileNameOut, myDict, size);
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				cout << fileNameOut << " is saved.\n";
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 0:
			{
				return;
			}
		}
		system("cls");
	} while(true);
	
	delete []myDict;
	return;
}
void outputToFile(string fileName, dict myDict[], int size)
{
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < size; ++i)
		file << myDict[i].word << "  " << myDict[i].mean << endl;
	file.close();
}
void swap(dict &a, dict &b)
{
	dict temp = a;
	a = b;
	b = temp;
}

void sortDict(dict myDict[], int left, int right)
{
	if(left <= right)
	{
		string key = myDict[(left+right)/2].word;

		int i = left;
		int j = right;

		while(i <= j)
		{
			while(myDict[i].word < key) i++;
			while(myDict[j].word > key) j--;

			if(i <= j)
			{
				swap(myDict[i], myDict[j]);
				i++;
				j--;
			}
		}
		if(left < j)
			sortDict(myDict, left, j);
		if(right > i)
			sortDict(myDict, i, right);
	}
}

int searchDict(dict myDict[], int size, string key)
{
	int left, right, mid;
	bool flag;

	left = 0;
	right = size - 1;
	while(left <= right)
	{
		mid = left + ((right - left) / 2);
		if(myDict[mid].word == key)
		{
			return mid;
		}
		else if(myDict[mid].word < key)
			{
				left = mid + 1;
			}
		else
			{
				right = mid - 1;
			}
	}
	return - 1; //key not found
}
bool hasOnlySpaces(string str)
{
	return str.find_first_not_of (' ') == str.npos;
}
dict* readFile(string fileName, int &size)
{
	fstream file;
	file.open(fileName, ios::in);

	vector<dict> v;
	dict* myDict;
	string str; //line by line reading
	dict tempW;

	if(!file.is_open())
	{
		cout << "Unable to open file.\n";
		size = - 1;
		return myDict;
	}
	int flag = 0;
	int found; //index of "  "

	string temp; //for splitting words
	string delim = "  ";

	while(getline(file, str))
	{
		//Line is not empty
		if(str.size() != 0)
		{
			found = str.find(delim);

			//check if "Usage":
			temp = str.substr(0, found);

			if(temp == "Usage")
			{
				//add more detail for the previous:
				v[flag-1].mean = str.substr(found + 2, str.size());
			}
			else
			{
				tempW.word = temp;
				if(!hasOnlySpaces(tempW.word)) //mistakes in file: a word characters are all spaces
				{
					found += 2;
					tempW.mean = str.substr(found, str.size());

					v.push_back(tempW);
					++flag; //one more word
				}
			}
		}
	}
	file.close();

	myDict = new dict[flag];
	for (int i = 0; i < flag; ++i)
	{
		myDict[i].word = v[i].word;
		myDict[i].mean = v[i].mean;
		////for debugging
		//cout << myDict[i].word << "  " << myDict[i].mean << endl;
	}
	size = flag;
	return myDict;
}
// dict* readFile(string fileName, int &size)
// {
// 	fstream file;
// 	file.open(fileName, ios::in);


// 	string str; //line by line reading
// 	dict tempW;

// 	int flag = 0;
// 	int found; //index of "  "

// 	dict* myDict = new dict[flag];
// 	string temp; //for splitting words
// 	string delim = "  ";

// 	while(getline(file, str))
// 	{
// 		//Line is not empty
// 		if(str.size() != 0)
// 		{
// 			found = str.find(delim);

// 			//check if "Usage":
// 			temp = str.substr(0, found);

// 			if(temp == "Usage" && flag > 1)
// 			{
// 				//add more detail for the previous:
// 				myDict[flag-1].mean = str.substr(found + 2, str.size());
// 			}
// 			else
// 			{
// 				tempW.word = temp;
// 				if(!hasOnlySpaces(tempW.word)) //mistakes in file: a word characters are all spaces
// 				{
// 					found += 2;
// 					tempW.mean = str.substr(found, str.size());

// 					myDict = addNew(myDict, flag, tempW.word, tempW.mean);
// 					++flag; //one more word
// 				}
// 			}
// 		}
// 	}
// 	file.close();
// 	size = flag;
// 	return myDict;
// }
dict* addNew(dict myDict[], int &size, string word, string mean)
{
	int checkSearch = searchDict(myDict, size, word);
	if(checkSearch != -1)
	{
		return myDict;
	}
	else
	{
		int newSize = size + 1;
		dict* temp = new dict[newSize];
		bool flag = false;
		for(int i = 0; i < size; ++i)
		{
			if((myDict[i].word < word) || flag == true)
			{
				//copy to new array
				temp[i].word = myDict[i].word;
				temp[i].mean = myDict[i].mean;
			}
			else
			{
				//add new word to new array
				temp[i].word = word;
				temp[i].mean = mean;
				//set the flag to continue copying
				flag = true;
			}
		}
		size = newSize;
		delete []myDict;
		return temp;
	}
	return myDict;
}
dict* addNew(dict myDict[], int &size)
{
	string word, mean;
	cout << "Enter a word to add: ";
	getline(cin, word);
	int checkSearch = searchDict(myDict, size, word);
	//already in dict
	if(checkSearch != -1)
	{
		cout << "This word is already in your dictionary.\n";
		cout << myDict[checkSearch].word << ": " << myDict[checkSearch].mean << endl;
		cout << "You may want to edit this word.\n";
	}
	else
	{
		cout << "Enter the meaning of " << word << ": ";
		getline(cin, mean);
		int newSize = size + 1;
		dict* temp = new dict[newSize];
		int checkSearch;
		bool flag = false;
		//copy to new array with size += 1
		auto start = high_resolution_clock::now(); //start timing
		for(int i = 0; i < size; i++)
		{
			if((myDict[i].word < word) || flag == true)
			{
				//copy to new array
				temp[i].word = myDict[i].word;
				temp[i].mean = myDict[i].mean;
			}
			else
			{
				//add new word to new array
				temp[i].word = word;
				temp[i].mean = mean;
				//set the flag to continue copying
				flag = true;
			}
		}
		auto stop = high_resolution_clock::now(); //stop timing
		auto duration = duration_cast<milliseconds>(stop - start);
		//check new word added
		checkSearch = searchDict(temp, newSize, word);
		if(checkSearch == -1) //not found
		{
			cout << "Error while adding.\n";
			return myDict;
		}
		//found
		//increase size
		size = newSize;
		//delete old dict
		delete[] myDict;
		cout << "New word added!\n";
		cout << "Running time: " << duration.count() << "ms.\n";
		return temp;
	}
	//if not create new dict, return the old dict
	return myDict;
}
void editWord(dict myDict[], int size)
{
	string word, mean;
	cout << "Enter the word you want to edit: ";
	getline(cin, word);
	int pos = searchDict(myDict, size, word);
	//If not in dict
	if(pos == -1)
	{
		cout << word << " is not in your dictionary. You may want to add this new word.\n";
	}
	else
	{
		cout << myDict[pos].word << ": " << myDict[pos].mean << endl;
		cout << "Enter new mean of " << word << " to edit: ";
		getline(cin, mean);
		myDict[pos].mean = mean;
		cout << "Word edited.\n";
		cout << myDict[pos].word << ": " << myDict[pos].mean << endl;
	}
}
dict* deleteWord(dict myDict[], int &size)
{
	string word, mean;
	cout << "Enter a word to delete: ";
	getline(cin, word);
	int pos = searchDict(myDict, size, word);
	if(pos == -1)
	{
		cout << "This word is not exist.\n";
	}
	else
	{
		cout << myDict[pos].word << ": " << myDict[pos].mean << endl;
		cout << "Are you sure to delete this word? [Y/N]: ";
		char choice;
		cin >> choice;
		cin.ignore();
		if(choice == 'y' || choice == 'Y')
		{
			bool flag = false;
			int newSize = size - 1;
			dict* temp = new dict[newSize];
			int j = 0;
			auto start = high_resolution_clock::now();
			for(int i = 0; i < size;)
			{
				if(myDict[i].word < word || flag == true) //copy to new dict
				{
					//copy to new array
					temp[j].word = myDict[i].word;
					temp[j].mean = myDict[i].mean;
					++i;
					++j;
				}
				else if(myDict[j].word == word)
				{
					//index of old dict keep increase
					//to ignore the deleted word
					++i;
					//j does not increase this turn because no word added
					//set the flag
					flag = true;
				}
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);
			//confirm that the word is deleted (aka not copied to new dict)
			int confirm = searchDict(temp, newSize, word);
			//found a valid position in dict
			if(confirm != -1)
			{
				cout << "Error while deleting.\n";
			}
			//confirm == -1
			//not found
			else
			{
				cout << "Word deleted.\n";
				cout << "Running time: " << duration.count() << "ms.\n";
				//update the size
				size = newSize;
				delete []myDict;
				return temp;
			}
		}
		else
		{
			cout << "Okay, your word still here, see you later.\n";
		}
	}
	//in case of error
	//in case of not found word to delete
	return myDict;
}