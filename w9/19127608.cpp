#include <bits/stdc++.h>
using namespace std;

struct node
{
	string data;
	//question = false
	//answer = true
	//bool type = false;
	node *yes_ans, *no_ans;
};
typedef node* nodePtr;

//File processing
void openFile(ifstream &inFile);
void openFile(ofstream &outFile);
void readFile(nodePtr& start, ifstream& inFile);
void writeFile(nodePtr start, ofstream& outFile);

//Testing
void print(nodePtr root);

//Deallocating memory
void free_memory(nodePtr root);

int main()
{
	ifstream inFile;
	ofstream outFile;
	nodePtr root;

	openFile(inFile);
	readFile(root, inFile);
	inFile.close();
	print(root);
	string lastInput;
	nodePtr p = root;
	do
	{
		cout << root->data << endl;
		getline(cin, lastInput);
		p = (tolower(lastInput[0]) == 'y') ? p->yes_ans : p->no_ans;
	//loop until reach the leaf node
	} while(p->yes_ans != NULL);

	cout << p->data << endl;
	cout << "Am I right?\n";
	getline(cin, lastInput);
	if(tolower(lastInput[0]) == 'y')
		cout << "That was easy!\n";
	else
	{
		cout << "Well, I don't know this animal.\n";
		cout << "What is it?\n";
		getline(cin, lastInput);
		string correctAnimal = lastInput;


	}
	openFile(outFile);
	writeFile(root, outFile);
	outFile.close();

	free_memory(root);
	return 0;
}


void openFile(ifstream &inFile)
{
	string fileName;
	cout << "Input file name: ";
	getline(cin, fileName);
	inFile.open(fileName);
	if(!inFile.is_open())
	{
		cout << "Unable to open file.\n";
		openFile(inFile);
	}
	else
	{
		return;
	}
}
void openFile(ofstream &outFile)
{
	string fileName;
	cout << "Input file name: ";
	getline(cin, fileName);
	outFile.open(fileName);
	if(!outFile.is_open())
	{
		cout << "Unable to open file.\n";
		openFile(outFile);
	}
	else
	{
		return;
	}
}
void readFile(nodePtr& start, ifstream& inFile)
{
	string str;
	getline(inFile, str);
	if(str != "")
	{
		start = new node;
		start->data = str;
		// if(str.substr(0, 2) == "#A")
		// 	start->type = true;
		readFile(start->yes_ans, inFile);
		readFile(start->no_ans, inFile);
	}
	else
		start = NULL;
}

void writeFile(nodePtr start, ofstream& outFile)
{
	if(start != NULL)
	{
		outFile << start->data << endl;
		writeFile(start->yes_ans, outFile);
		writeFile(start->no_ans, outFile);
	}
	// else
	// 	outFile << "" << endl;
}

void print(nodePtr root)
{
	if(root != NULL)
	{
		cout << root->data << endl;
		print(root->yes_ans);
		print(root->no_ans);
	}
	else
		return;
}
void free_memory(nodePtr root)
{
	if(root != NULL)
	{
		free_memory(root->yes_ans);
		free_memory(root->no_ans);
	}
	delete root;
}