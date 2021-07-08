#include <bits/stdc++.h>
using namespace std;


struct dict
{
	string word;
	string mean;
};

int countWords(string fileName);
int readFile(string fileName, dict myDict[]);
dict* readFile(string fileName, int &size);
void sortDict(dict myDict[], int left, int right);
int searchDict(dict myDict[], int size, string key);
void outputToFile(string fileName, dict myDict[], int size);
int main()
{
	string fileName = "Oxford English Dictionary.txt";

	int size = 0;
	dict * myDict;
	//cout << "Please wait because it is really really slow, it may take up to 10m to read the file. I'm trying to improve my algorithm.\n\n";
	myDict = readFile(fileName, size);
	cout << "Loaded " << fileName << endl;
	outputToFile("readFile.txt", myDict, size);
	sortDict(myDict, 0, size - 1);
	outputToFile("sortedFile.txt", myDict, size);
	cout << "Dictionary is sorted\n";

	string key;
	int pos;
	char choice;
	go:
	cout << "\nNoted: Case sensitive.\n";
	cout << "Enter a word to lookup: ", getline(cin, key);
	pos = searchDict(myDict, size, key);
	if(pos != -1)
	{
		cout << myDict[pos].word << ": " << myDict[pos].mean << endl << endl;
	}
	else
		cout << "This word is not in dictionary.\n";
	cout << "Continue? y/n: ";
	cin >> choice;
	if(choice == 'y' || choice == 'Y')
		{
			cin.ignore();
			goto go;
		}

	delete []myDict;
	return 0;
}
void outputToFile(string fileName, dict myDict[], int size)
{
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < size; ++i)
		file << i << ": " << myDict[i].word << ": " << myDict[i].mean << endl;

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
void copyArr(dict oldArr[], dict newArr[], int size)
{
	for(int i = 0; i < size; ++i)
	{
		newArr[i].word = oldArr[i].word;
		newArr[i].mean = oldArr[i].mean;
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
	string str; //line by line reading
	dict tempW;

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

	dict* myDict = new dict[flag];
	for (int i = 0; i < flag; ++i)
	{
		myDict[i].word = v[i].word;
		myDict[i].mean = v[i].mean;
	}
	size = flag;
	return myDict;
}