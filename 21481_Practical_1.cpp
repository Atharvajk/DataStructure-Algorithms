//============================================================================
// Name        : DSA_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;
class Node
{
	string key, mean;
	Node *rchild;
	Node *lchild;

public:
	friend class Dictionary;
	Node()
	{
		rchild = NULL;
		lchild = NULL;
	}
	Node(string key, string mean)
	{
		this->key = key;
		this->mean = mean;
		rchild = NULL;
		lchild = NULL;
	}
};
class Dictionary
{
	Node *root;

public:
	Dictionary()
	{
		root = NULL;
	}
	void create();
	void deleteNode(string);
	void ascending(Node *r);
	void descending(Node *r);
	void inorder()
	{
		if (root == NULL)
		{
			cout << "\nDictionary is empty\n";
			return;
		}
		ascending(root);
	}
	void postorder()
	{
		if (root == NULL)
		{
			cout << "\nDictionary is empty\n";
			return;
		}
		descending(root);
	}
	bool insert(string key, string mean);
	int search(string key);
	void update(Node *r);
	void updatation()
	{
		update(root);
	}
};
void Dictionary::create()
{
	int n;
	string key1, mean1;
	cout << "Enter How many word to be inserted :";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter Key:";
		cin >> key1;
		cout << "Enter Meaning:";
		cin.ignore();
		getline(cin, mean1);
		insert(key1, mean1);
		cout << "KEY INSERTED SUCCESSFULLY\n";
	}
}
bool Dictionary::insert(string key, string mean)
{
	Node *r = new Node(key, mean);
	if (root == NULL)
	{
		root = r;
		return true;
	}
	Node *curr = root;
	Node *par = root;
	while (curr != NULL)
	{
		if (key > curr->key)
		{
			par = curr;
			curr = curr->rchild;
		}
		else if (key < curr->key)
		{
			par = curr;
			curr = curr->lchild;
		}
		else
		{
			cout << "\nKey is already exists in dictionary";
			return false;
		}
	}

	if (key > par->key)
	{
		par->rchild = r;
		return true;
	}
	else
	{
		par->lchild = r;
		return true;
	}
}

void Dictionary::ascending(Node *root)
{
	if (root)
	{
		ascending(root->lchild);
		cout << " " << root->key << " : " << root->mean << endl;
		ascending(root->rchild);
	}
}

void Dictionary::descending(Node *root)
{
	if (root)
	{
		descending(root->lchild);
		descending(root->rchild);
		cout << " " << root->key << " : " << root->mean << endl;
	}
}
int Dictionary::search(string key)
{
	Node *curr = root;
	int count = 0;
	if (curr == NULL)
	{
		return -1;
	}
	if (root->key == key)
	{
		return 1;
	}
	while (curr != NULL)
	{
		count++;
		if (curr->key < key)
		{
			curr = curr->rchild;
			count++;
		}
		else if (curr->key > key)
		{
			curr = curr->lchild;
			count++;
		}
		else if (curr->key == key)
		{
			return count;
		}
	}
	return -1;
}
void Dictionary::update(Node *root)
{
	Node *curr;
	string Ukey;
	cout << "Enter key to update:";
	cin >> Ukey;
	curr = root;
	while (curr)
	{
		if (curr->key == Ukey)
		{
			cout << "Enter new Meaning:";
			cin >> curr->mean;
			cout << "MEANNING UPDATED SUCCESSFULLY\n";
			return;
		}
		else
		{
			if (curr->key < Ukey)
			{
				curr = curr->lchild;
			}
			else
			{
				curr = curr->rchild;
			}
		}
		cout << "Key not found!\n";
	}
}
void Dictionary::deleteNode(string key)
{
	Node *par = NULL;
	Node *curr = NULL;
	Node *temp = NULL;
	int flag = 0, res = 0;
	if (root == NULL)
	{
		cout << "Dictionary is empty";
		return;
	}
	curr = root;
	while (1)
	{
		res = key.compare(curr->key);
		if (res == 0)
		{
			break;
		}
		flag = res;
		par = curr;
		curr = (res > 0) ? curr->lchild : curr->rchild;
		if (curr == NULL)
		{
			return;
		}
	}
	// deleting leaf node
	if (curr->rchild == NULL)
	{
		if (curr == root && curr->lchild == NULL)
		{
			delete (curr);
			root = NULL;
			return;
		}
		else if (curr == root)
		{
			root = curr->lchild;
			delete (curr);
			return;
		}
		flag > 0 ? (par->lchild = curr->lchild) : (par->rchild = curr->lchild);
	}
	else
	{
		// delete node with single child
		temp = curr->rchild;
		if (!temp->lchild)
		{
			temp->lchild = curr->lchild;
			if (curr == root)
			{
				root = temp;
				delete (curr);
				return;
			}
			flag > 0 ? (par->lchild = temp) : (par->rchild = temp);
		}
		else
		{
			// deleting with two child
			Node *successor = NULL;
			while (1)
			{
				successor = temp->lchild;
				if (!successor->lchild)
				{
					break;
				}
				temp = successor;
			}
			temp->lchild = successor->rchild;
			successor->lchild = curr->lchild;
			successor->rchild = curr->rchild;
			if (curr == root)
			{
				root = successor;
				delete (curr);
				return;
			}
			(flag > 0) ? (par->lchild = successor) : (par->rchild = successor);
		}
	}
	delete (curr);
	return;
}

int main()
{
	string key;
	Dictionary d1;
	int comparisons;
	int ch;
	do
	{
		cout << "*********MENU*********" << endl;
		cout << "\n1.Insertion in dictionary";
		cout << "\n2.Ascending Order";
		cout << "\n3.Descending Order";
		cout << "\n4.Search";
		cout << "\n5.Update Dictionary";
		cout << "\n6.Delete Dictionary";
		cout << "\n7.Exit";
		cout << "\nEnter your choice:";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "INSERTION\n";
			d1.create();
			cout << endl;
			break;
		case 2:
			cout << "\nAscending Order:\n";
			d1.inorder();
			cout << " ";
			break;
		case 3:
			cout << "\nDescending Order:\n";
			d1.postorder();
			cout << " ";
			break;
		case 4:
			cout << "\nSearching operation:";
			cout << "\nEnter key for search:";
			cin >> key;
			comparisons = d1.search(key);
			if (comparisons == -1)
			{
				cout << "Key not found\n";
			}
			else
			{
				cout << "\n"
					 << key << " found in " << comparisons << " comparison" << endl;
			}
			d1.search(key);
			break;
		case 5:
			cout << "Update Dictionary:\n";
			d1.updatation();
			break;
		case 6:
			cout << "Deleting Node\n";
			cout << "\nEnter key to delete:";
			cin >> key;
			d1.deleteNode(key);
			break;
		case 7:
			cout << "EXIT";
			exit(0);
			break;
		}
	} while (ch != 7);
	return 0;
}
