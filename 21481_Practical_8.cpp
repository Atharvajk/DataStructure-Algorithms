//============================================================================
// Name        : DSA8_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <climits>
using namespace std;

template <class T>
class node
{
	T data;
	node<T> *left;
	node<T> *right;

public:
	node()
	{
		left = right = NULL;
	}

	node(T data)
	{
		this->data = data;
		left = right = NULL;
	}

	template <class B>
	friend class OBST;
};

// Optimal Binary Search Tree ------------------------------------------------------

template <class T>
class OBST
{
	node<T> *root;

public:
	OBST()
	{
		root = NULL;
	}

	node<T> *get_root()
	{
		return this->root;
	}

	void calculate_weight(double *, double *, int, T *);
	node<T> *create_tree(int, int, double **, T *);

	void inorder_traversal(node<T> *curr);
	void preorder_traversal(node<T> *curr);
	void postorder_traversal(node<T> *curr);
};


int main()
{
	OBST<string> ST;
	int choice = -1;
	int temp = 0;

	cout << "# Implementation of OBST\n";

	while (choice)
	{
		cout << "\n---------- MENU ----------\n"
			 << "1. Input identifiers\n"
			 << "2. Inorder Traversal\n"
			 << "3. Preorder Traversal\n"
			 << "4. Postorder Traversal\n"
			 << "5. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch (choice)
		{
		case 1: // Input identifiers
		{
			cout << "Enter no. of identifiers = ";
			cin >> temp;
			string *input = new string[temp + 1];
			double *p = new double[temp];
			double *q = new double[temp + 1];
			cout << "Enter identifiers = " << endl;

			input[0] = "NULL"; // dummy node
			for (int i = 0; i < temp; ++i)
			{
				cout << "Enter identifier " << i + 1 << " = ";
				cin >> input[i + 1];
			}
			cout << "Enter probabilities of successful search = " << endl;
			for (int i = 0; i < temp; ++i)
			{
				cout << "Enter probability " << i + 1 << " = ";
				cin >> p[i];
			}
			cout << "Enter probabilities of unsuccessful search = " << endl;
			for (int i = 0; i < temp + 1; ++i)
			{
				cout << "Enter probability " << i + 1 << " = ";
				cin >> q[i];
			}
			ST.calculate_weight(p, q, temp, input);
			break;
		}

		case 2: // Inorder Traversal
		{
			cout << "Inorder Traversal = " << endl;
			ST.inorder_traversal(ST.get_root());
			break;
		}

		case 3: // Preorder Traversal
		{
			cout << "Preorder Traversal = " << endl;
			ST.preorder_traversal(ST.get_root());
			break;
		}

		case 4: // Postorder Traversal
		{
			cout << "Postorder Traversal = " << endl;
			ST.postorder_traversal(ST.get_root());
			break;
		}

		case 5: 
		{
			cout << "Thank you :)" << endl;
			break;
		}

		default: // Forced exit
		{
			cout << "# Forced exit due to error" << endl;
			exit(0);
		}
		}
	}

	return 0;
}
//Copyright Atharva

template <class T>
void OBST<T>::calculate_weight(double *p, double *q, int n, T *input)
{
	
	double w[n+1][n+1];

	double c[n+1][n+1];

	double **r = new double *[n + 1]; 
	for (int i = 0; i < n + 1; ++i)
	{
		r[i] = new double[n + 1];
	}

	for (int i = 0; i < n; ++i)
	{
		w[i][i] = q[i];
		r[i][i] = c[i][i] = 0;

		w[i][i + 1] = q[i] + q[i + 1] + p[i];
		r[i][i + 1] = i + 1;
		c[i][i + 1] = w[i][i + 1];
	}

	w[n][n] = q[n];
	r[n][n] = c[n][n] = 0;
	for (int m = 2; m <= n; ++m)
	{
		for (int i = 0; i <= n - m; ++i)
		{
			double Min = 999;

			int j = i + m;
			int k = 0;
			w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

			for (int x = i + 1; x <= j; ++x)
			{
				// find minimum sum
				double sum = c[i][x - 1] + c[x][j];
				if (sum < Min)
				{
					Min = sum;
					k = x;
				}
			}
			c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
			r[i][j] = k;
		}
	}


	this->root = this->create_tree(0, n, r, input);
}

template <class T>
node<T> *OBST<T>::create_tree(int i, int j, double **r, T *input)
{
	if (i != j)
	{
		int k = r[i][j];
		node<T> *t = new node<T>(input[k]);

		t->left = this->create_tree(i, k - 1, r, input);
		t->right = this->create_tree(k, j, r, input);

		return t;
	}
	else
	{
		return NULL;
	}
}

template <class T>
void OBST<T>::inorder_traversal(node<T> *curr)
{
	if (curr != NULL)
	{
		this->inorder_traversal(curr->left);
		cout << curr->data << " ";
		this->inorder_traversal(curr->right);
	}
}

template <class T>
void OBST<T>::preorder_traversal(node<T> *curr)
{
	if (curr != NULL)
	{
		cout << curr->data << " ";
		this->preorder_traversal(curr->left);
		this->preorder_traversal(curr->right);
	}
}

template <class T>
void OBST<T>::postorder_traversal(node<T> *curr)
{
	if (curr != NULL)
	{
		this->postorder_traversal(curr->left);
		this->postorder_traversal(curr->right);
		cout << curr->data << " ";
	}
}

