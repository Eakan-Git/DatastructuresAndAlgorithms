#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 
struct Tree
{
	string key;
	string mean;
	int color;
	Tree *left, *right, *parent;
};

Tree *Uncle(Tree *n, int &k);
void leftRotate(Tree *&T, Tree *&x);
void rightRotate(Tree *&T, Tree *&x);
Tree *uncle(Tree *n);
void add(Tree *&T, string key, string mean, Tree *parent);
bool insert(Tree *&T, Tree *p, Tree *parent);
void search(Tree *p, string word);
void edit(Tree *p, string eword, string emean);
void deleteWord(Tree *p, string dword);
Tree* readFile(string fileName);
void outputToFile(ofstream &file, Tree *p);
int main()
{
	string fileName;
	cout << "Enter file name: (must has .txt) ";
	getline(cin, fileName);
	Tree* dict;
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
				search(dict, key);
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
				edit(dict, tempW, tempM);
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
				add(dict, tempW, tempM, NULL);
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
				deleteWord(dict, tempW);
				stop = high_resolution_clock::now();
				duration = duration_cast<milliseconds>(stop - start);
				cout << "Running time: " << duration.count() << "ms.\n";
				cout << "Press any key to continue...";
				cin.get();
				break;
			}
			case 5:
			{
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
				file.close();
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


Tree *Uncle(Tree *n, int &k)
{
	if (n->parent == n->parent->parent->left)
	{
		k = 0;
		return n->parent->parent->right;
	}
	else
	{
		k = 1;
		return n->parent->parent->left;
	}
}

void leftRotate(Tree *&T, Tree *&x)
{
	Tree *y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	if (x->parent != NULL)
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else T = y;
	y->left = x;
	y->parent = x->parent;
	y->left->parent = y;
}

void rightRotate(Tree *&T, Tree *&x)
{
	Tree *y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	if (x->parent != NULL)
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else T = y;
	y->right = x;
	y->parent = x->parent;
	y->right->parent = y;
}

bool insert(Tree *&T, Tree *p, Tree *parent)
{
	if (T)
	{
		if (p->key == T->key) return false;
		else if (p->key < T->key)
		{
			return(insert(T->left, p, T));
		}
		else
		{
			return(insert(T->right, p, T));
		}
	}
	else
	{
		T = p;
		T->parent = parent;
		return true;
	}
}

void add(Tree *&T, string word, string mean, Tree *parent)
{
	Tree *p = new Tree;
	p->key = word;
	p->mean = mean;
	p->color = 1;
	p->left = p->right = NULL;
	bool k = insert(T, p, parent);
	if (k == true)
	{
		while (p != T && p->parent->color == 1)
		{
			int k;
			Tree *uncle = Uncle(p, k);
			if (uncle != NULL && uncle->color == 1)
			{
				p->parent->color == 0;
				uncle->color = 0;
				p->parent->parent->color = 1;
				p = p->parent->parent;
			}
			else
			{
				if (k == 0)
				{
					if (p == p->parent->right)
					{
						p = p->parent;
						leftRotate(T, p);
					}
					p->parent->color = 0;
					p->parent->parent->color = 1;
					rightRotate(T, p->parent->parent);
				}
				else
				{
					if (p == p->parent->left)
					{
						p = p->parent;
						rightRotate(T, p);
					}
					p->parent->color = 0;
					p->parent->parent->color = 1;
					leftRotate(T, p->parent->parent);
				}
			}
		}
		T->color = 0;
	}
}

void search(Tree *p, string word)
{
	if (p)
	{
		if (p->key == word) cout << p->mean << endl;
		else if (p->key < word) search(p->right, word);
		else search(p->left, word);
	}
	else cout << "Word not existed!\n";
}

void edit(Tree *p, string eword, string emean)
{
	if (p)
	{
		if (p->key == eword) p->mean = emean;
		else if (p->key < eword) edit(p->right, eword, emean);
		else edit(p->left, eword, emean);
	}
	else cout << "Word not existed!\n";
}

void deleteWord(Tree *p, string dword)
{
	if (p)
	{
		if (p->key == dword)
		{
			p->key = "";
			p->mean = "";
		}
		else if (p->key < dword) deleteWord(p->right, dword);
		else deleteWord(p->left, dword);
	}
	else cout << "Word not existed!\n";
}
Tree* readFile(string fileName)
{
	Tree* T = NULL;
	ifstream file;
	string str;
	file.open(fileName);
	while (!file.eof())
	{
		getline(file, str);
		int pos = str.find("  ");
		if (pos != -1)
			add(T, str.substr(0, pos), str.substr(pos + 2), NULL);
	}
	file.close();
	return T;
}
void outputToFile(ofstream &file, Tree *p)
{
	if (p->left) outputToFile(file, p->left);
	if (p->key != "") file << p->key << "  " << p->mean << endl;
	if (p->right) outputToFile(file, p->right);
}