#pragma once
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 


class HashNode
{
private:
	string word;
	string mean;
	HashNode* next;
public:
	HashNode()
	{
		word = "";
		mean = "";
	}
	HashNode(string word, string mean)
	{
		this->word = word;
		this->mean = mean;
		next = NULL;
	}
}

class HashTable
{
private:
	HashNode **data;
protected:
	int maxSize;
	HashNode *arr = nullptr;
	HashNode *resize();
public:
	int size;
	HashTable(int M);
	~HashTable();
	HashTable(): data(nullptr), maxSize(0), size(0){}
	unsigned int hash(string word, string mean);
	virtual void insert(string word, string mean);
	virtual string lookUp(string word);
}

HashNode* HashTable::resize()
{
	const int oldSize = maxSize;
	maxSize = maxSize * 12 + 1;

	HashNode *temp = new HashNode[oldSize]();
	for(int i = 0; i < oldSize; ++i)
	{
		temp[i] = arr[i];
	}

	HashNode x;
	arr = new HashNode[maxSize]();
	for(int i = 0; i < oldSize; ++i)
	{
		if(temp[i].word != "" && temp[i].mean != "")
		{
			insert(temp[i].word, temp[i].mean);
		}
		else arr[i] = x;
	}
	return arr;
}

HashTable::HashTable(int M)
{
	maxSize = M;
	size = 0;
	data = new HashNode*[maxSize];
	for(int i = 0; i < maxSize; ++i)
		data[i] = NULL;
}

HashTable::~HashTable()
{
	for(int i = 0; i < maxSize; ++i)
	{
		if(data[i] != NULL)
		{
			for(HashNode* x = data[i]; x!= NULL;)
			{
				HashNode* y = x;
				x = x->next;
				delete y;
			}
		}
	}
	delete []data;
	delete []arr;
}

unsigned int HashTable::hash(string key, int M)
{
	unsigned int res = 0;
	unsigned int len = key.length();
	for(int i = 0; i < len; ++i)
	{
		int c = (int)((char)key[i]);
		int temp = (int)(c*pow((float)128, (float)(len - i - 1))) % M;
		res += temp;
	}
	res %= M;
	return res;
}

void HashTable::insert(string word, string mean)
{
	int pos = hash(key, maxSize);
	HashNode *temp = new HashNode(word, mean);
	if(data[pos] == NULL)
	{
		data[pos] = temp;
	}
	else
	{
		temp->next = data[pos];
		data[pos] = temp;
	}
}

string HashTable::lookUp(string word)
{
	int pos = hash(word, maxSize);
	for(auto val = data[pos]; val != NULL; val = val->next)
	{
		if(val->word == word)
			return val->mean;
	}
	return "";
}

void HashTable::edit(string word)
{
	int pos = hash(word, maxSize);
	for(auto val = data[pos]; val != NULL; val = val->next)
	{
		if(val->word == word)
			{
				cout << "Input new mean: ";
				string newMeaning;
				getline(cin, newMeaning);
				val->mean = newMeaning;
			}
	}
}
void build(HashTable *&hashTable, string fileName)
{
	fstream file;
	file.open(fileName, ios::in);

	string str;

}