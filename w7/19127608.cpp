#include<iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
};
class BST
{
	node* root;
	node* find(int x, node* t);
	node* insert(int x, node* t);
	node* remove(int x, node* t);
	node* make_empty(node* t); //for destructor
public:
	BST(){root = NULL;}
	~BST(){root = make_empty(root);}
	void insert(int x){root = insert(x, root);}
	void search(int x);
	void remove(int x){root = remove(x, root);}
	void in_order(node* t);
	void display();
	bool is_empty(){return root == NULL;}
};


int main()
{
	srand(time(NULL));
	BST tree;
	int n = 10; //number of nodes to be added
	//int m = 3; //number of nodes to be deleted
	int num;
	for(int i = 0; i < n; ++i)
	{
		num = rand() % 100; //in range [1-99]
		tree.insert(num);
		cout << "Insert " << num << ": ";
		tree.display();
	}
	char choice;
	cout << "\nEnter a number to search: ";
	cin >> num;
	tree.search(num);
	here:
	cout << "\nSelect a number to delete: ";
	cin >> num;
	tree.remove(num);
	cout << "After remove: ";
	tree.display();
	if(tree.is_empty() == false)
		cout << "The tree is not empty yet!\n";
	else
		cout << "The tree is now empty!\n";
	//cin.ignore();
	cout << "\nEnter 'y' or 'Y' to continue deleting, else exit: ";
	cin >> choice;
	if(choice == 'y' || choice == 'Y')
		goto here;
	return 0;
}
void BST::search(int x)
{
	node* t = find(x, root);
	if(t != NULL)
		cout << t->data << " is found." << endl;
	else
		cout << "Not found.\n";
}
void BST::in_order(node* t)
{
	if(t == NULL)
		return;
	in_order(t->left);
	cout << t->data << " ";
	in_order(t->right);	
}
void BST::display()
{
	in_order(root);
	cout << endl;
}
node* BST::find(int x, node* t)
{
	if(t == NULL)
		return NULL;
	else if(x < t->data)
		return find(x, t->left);
	else if(x > t->data)
		return find(x, t->right);
	else
		return t;
}
node* BST::insert(int x, node* t)
{
	if(t == NULL)
	{
		t = new node;
		t->data = x;
		t->left = t->right = NULL;
	}
	else if(x < t->data)
	{
		t->left = insert(x, t->left);
	}
	else if(x > t->data)
	{
		t->right = insert(x, t->right);
	}
	return t;
}

node* findMin(node* t)
{
	if(t == NULL)
		return NULL;
	else if(t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

node* findMax(node* t)
{
	if(t == NULL)
		return NULL;
	else if(t->right == NULL)
		return t;
	else
		return findMax(t->right);
}

node* BST::remove(int x, node* t)
{
	node* temp;
	if(t == NULL)
		return NULL;
	else if(x < t->data)
		t->left = remove(x, t->left);
	else if(x > t->data)
		t->right = remove(x, t->right);
	else if(t->left && t->right)
	{
		temp = findMin(t->right);
		t->data = temp->data;
		t->right = remove(t->data, t->right);
	}
	else
	{
		temp = t;
		if(t->left == NULL)
			t = t->right;
		else if(t->right == NULL)
			t = t->left;
		delete temp;
	}

	return t;
}

node* BST::make_empty(node* t)
{
	if(t == NULL)
		return NULL;
	else
	{
		make_empty(t->left);
		make_empty(t->right);
		delete t;
	}
	return NULL;
}