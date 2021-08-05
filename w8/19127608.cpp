#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 
struct AVLTree
{
	string word;
	string mean;
	int h;
	AVLTree* TreeLeft;
	AVLTree* TreeRight;
};
void TurnLeft(AVLTree *&p)
{
	AVLTree *q = p->TreeRight;
	AVLTree *tmp = q;
	if (q->h == 1)
	{
		tmp = q->TreeLeft;
		q->TreeLeft = tmp->TreeRight;
		tmp->TreeRight = q;
	}
	p->TreeRight = tmp->TreeLeft;
	tmp->TreeLeft = p;
	p = tmp;
	if (tmp == q)
	{
		if (p->TreeLeft) p->TreeLeft->h = 0;
		if (p->TreeRight) p->TreeRight->h = 0;
	}
	else
	{
		switch (p->h)
		{
		case 0:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		case 1:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = -1;
			break;
		case -1:
			if (p->TreeLeft) p->TreeLeft->h = 1;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		}
	}
	p->h = 0;
}

void TurnRight(AVLTree *&p)
{
	AVLTree *q = p->TreeLeft;
	AVLTree *tmp = q;
	if (q->h == -1)
	{
		tmp = q->TreeRight;
		q->TreeRight = tmp->TreeLeft;
		tmp->TreeLeft = q;
	}
	p->TreeLeft = tmp->TreeRight;
	tmp->TreeRight = p;
	p = tmp;
	if (tmp == q)
	{
		if (p->TreeLeft) p->TreeLeft->h = 0;
		if (p->TreeRight) p->TreeRight->h = 0;
	}
	else
	{
		switch (p->h)
		{
		case 0:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		case 1:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = -1;
			break;
		case -1:
			if (p->TreeLeft) p->TreeLeft->h = 1;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		}
	}
	p->h = 0;
}

int Add(AVLTree *&p, string word, string wmean)
{
	int k;
	if (p)
	{
		if (word == p->word) return -1;
		if (word < p->word)
		{
			k = Add(p->TreeLeft, word, wmean);
			if (k == 1)
			{
				switch (p->h)
				{
				case 0: p->h = 1; return 1;
				case -1: p->h = 0; return 0;
				case 1: TurnRight(p); return 0;
				}
			}
		}
		else
		{
			k = Add(p->TreeRight, word, wmean);
			if (k == 1)
			{
				switch (p->h)
				{
				case 0: p->h = -1; return 1;
				case 1: p->h = 0; return 0;
				case -1: TurnLeft(p); return 0;
				}
			}
		}
	}
	else
	{
		p = new AVLTree;
		if (p == NULL)
			return -1;
		p->word = word;
		p->mean = wmean;
		p->h = 0;
		p->TreeLeft = p->TreeRight = NULL;
		return 1;
	}
	return 0;
}

void Search(AVLTree *p, string word)
{
	if (p)
	{
		if (p->word == word) cout << p->mean << endl;
		else if (p->word < word) Search(p->TreeRight, word);
		else Search(p->TreeLeft, word);
	}
	else
	{
		cout << "This word is not exists.\n";
	}
}
void Edit(AVLTree *p, string word, string mean)
{
	if (p)
	{
		if (p->word == word) p->mean = mean;
		else if (p->word < word) Edit(p->TreeRight, word, mean);
		else Edit(p->TreeLeft, word, mean);
	}
	else
	{
		cout << "This word does not exists.\n";
	}
}
void Delete(AVLTree *p, string word)
{
	if (p)
	{
		if (p->word == word)
		{
			p->word = "";
			p->mean = "";
		}
		else if (p->word < word) Delete(p->TreeRight, word);
		else Delete(p->TreeLeft, word);
	}
	else
	{
		cout << "This word does not exists.\n";
	}
}
AVLTree* readFile(string fileName)
{
	AVLTree* AVL = NULL;
	ifstream file;
	string str;
	file.open(fileName);
	while(!file.eof())
	{
		getline(file, str);
		int pos = str.find("  ");
		if(pos!=-1)
			Add(AVL, str.substr(0, pos), str.substr(pos+2));
	}
	return AVL;
}
bool isEmpty(AVLTree *p)
{
	if(p == NULL)
		return true;
	return false;
}
void outputToFile(ofstream &file, AVLTree *p)
{
	if(p->TreeLeft) outputToFile(file, p->TreeLeft);
	if(p->word != "") file << p->word << "  " << p->mean << endl;
	if(p->TreeRight) outputToFile(file, p->TreeRight);
}
int main()
{
	string fileName;
	cout << "Enter file name: (must has .txt) ";
	getline(cin, fileName);
	AVLTree* dict;
	auto start = high_resolution_clock::now();
	dict = readFile(fileName);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "File loaded in " << duration.count() << "ms.\n\n";
	int choice;
	string tempW, tempM;
	do
	{
		cout << "NOTE: CASE SENSITIVE.\n";
		cout << "[1] Look up\n";
		cout << "[2] Edit\n";
		cout << "[3] Add\n";
		cout << "[4] Delete\n";
		cout << "[5] Save\n";
		cout << "[0] Exit\n";
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
				Search(dict, key);
				//cin.get(); //test stop
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 2:
			{
				cout << "Enter a word to edit: ";
				getline(cin, tempW);
				cout << "Enter mean:";
				getline(cin, tempM);
				start = high_resolution_clock::now();
				Edit(dict, tempW, tempM);
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 3:
			{
				cout << "Enter a word: ";
				getline(cin, tempW);
				cout << "Enter mean:";
				getline(cin, tempM);
				start = high_resolution_clock::now();
				Add(dict, tempW, tempM);
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 4:
			{
				cout << "Enter a word to delete: ";
				getline(cin, tempW);
				start = high_resolution_clock::now();
				Delete(dict, tempW);
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 5:
			{
				if(isEmpty(dict))
					cout << "This dictionary has nothing init.\n";
				string fileNameOut;
				cout << "Enter file name to save (must has .txt): ";
				getline(cin, fileNameOut);
				ofstream file;
				file.open(fileNameOut);
				if(!file.is_open())
				{
					cout << "Error opening file.\n";
					break;
				}
				start = high_resolution_clock::now();
				outputToFile(file, dict);
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
				return 0;
			}
		}
		system("cls");
	} while(true);
	return 0;
}