//============================================================================
// Name        : Hashexp5.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define SIZE 26

class Hash
{
	string value;
	char key;
	Hash *next;

public:
	Hash()
	{
		value = "";
		key = ' ';
		next = NULL;
	}
	Hash(string value, char key)
	{
		this->value = value;
		this->key = key;
		next = NULL;
	}
	friend class HashTable;
};

class HashTable
{
	Hash *arr[SIZE];

public:
	HashTable()
	{
		for (int i = 0; i < SIZE; i++)
		{
			arr[i] = NULL;
		}
	}
	int hashfunc(char key)
	{
		int k = key;
		return k % SIZE;
	}

	void insert(string value, char key)
	{ // without replacement

		int hashcode = hashfunc(key);
		if (arr[hashcode] == NULL)
		{
			arr[hashcode] = new Hash(value, key);
		}
		else
		{
			Hash *n = new Hash(value, key);
			Hash *temp = arr[hashcode];
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = n;
		}
	}

	int search(char keyc)
	{
		int key = keyc;
		int cnt = 1;

		int hashcode = hashfunc(keyc);
		if (arr[hashcode]->key == keyc)
		{
			cout << "\n---------Record Found---------\nValue=" << arr[hashcode]->value << endl
				 << "Key=" << arr[hashcode]->key << endl;
			return cnt;
		}
		else
		{
			Hash *temp = arr[hashcode];
			while (temp != NULL && temp->key != keyc)
			{
				cnt++;
				temp = temp->next;
			}
			cout << "\n---------Record Found---------\nValue=" << arr[hashcode]->value << endl
				 << "Key=" << arr[hashcode]->key << endl;
			return cnt;
		}
	}
	void displayall()
	{
		cout << endl;
		cout << "SR. \t"
			 << "Value           \t"
			 << "Key" << endl;
		bool flag = true;
		char bb = 65;
		for (int i = 0; i < SIZE; i++)
		{
			if (flag && (i + 72) <= 90)
			{
				bb = i + 72;
			}
			else
			{
				flag = false;
				bb = i + 46;
			}

			if (arr[i] != NULL)
			{
				Hash *temp = arr[i];

				cout << bb << ". \t";
				while (temp != NULL)
				{
					cout << temp->value << "-key: " << temp->key << "  -->  ";
					temp = temp->next;
				}
				cout << endl;
			}
			else
			{
				cout << bb << ". \t" << endl;
			}
		}
		cout << endl;
	}
};

void menu()
{
	HashTable ht;
	int ch, cmp, cmp2;
	string value;
	char key;
	while (1)
	{
		cout << endl
			 << "----------------Menu-----------------" << endl;
		cout << "1.Insert\n2.Search\n3.DisplayALL" << endl;
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "\nKey = ";
			cin >> key;
			key = tolower(key);
			cout << "Enter Data\nValue= ";
			cin >> value;
			ht.insert(value, key);
			// ht.displayall();
			break;
		case 2:
			cout << "Enter Key number to search = ";
			cin >> key;
			key = tolower(key);
			cmp = ht.search(key);
			cout << "\nIn " << cmp << " Comparisons." << endl;

			break;
		case 3:
			cout << "\n-----------------Open Hashing---------------------" << endl;
			ht.displayall();

			break;
		case 10:
			exit(0);
		}
	}
}
int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	menu();
	return 0;
}