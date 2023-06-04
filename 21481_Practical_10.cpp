
//============================================================================
// Name        : DSA10_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <climits>
using namespace std;


template <class T>
class MinHeap
{
	T *arr;		 
	int capacity; 
	int size;	  
public:

	MinHeap()
	{
		capacity = 0;
		size = 0;
		arr = NULL;
	}

	MinHeap(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		arr = new T[capacity];
	}


	void setCapacity(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		arr = new T[capacity];
	}

	// methods
	void insert(T data); 
	T getMin();			 

	void heapify(int i); 
	void heapify_itr();	 
	void display();		 

	void remove(int i);			  
	T extract_min_key();		 
	void bubble_key_to_top(int i); 


	int parent(int i) 	{
		return (i - 1) / 2;
	}

	int Lchild(int i) 	{
		return (2 * 1 + 1);
	}

	int Rchild(int i) 	{
		return (2 * 1 + 2);
	}

	void swap(int a, int b)
	{
		
		T temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}
};

template <class T>
T *heap_sort(T *arr, int n) 
{
	MinHeap<T> heap(n);
	for (int i = 0; i < n; ++i)
	{ 
		heap.insert(arr[i]);
	}
	for (int i = 0; i < n; ++i)
	{ 
		arr[i] = heap.extract_min_key();
	}

	return arr;
}

int main()
{
	MinHeap<int> heap;
	int choice = -1;
	int temp = 0;
	int marksLength;
	int *marks = NULL;

	cout << "# Implementation of Heap DS and Heap Sort\n";

	while (choice)
	{
		cout << "\n---------- MENU ----------\n"
			 << "1. Input Marks of students\n"
			 << "2. Get minimum marks obtained\n"
			 << "3. Heap sort on marks\n"
			 << "4. Display heap\n"
			 << "5. Exit" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch (choice)
		{
		case 1: // Input Marks
		{
			cout << "Enter no. of entries = ";
			cin >> marksLength;
			heap.setCapacity(marksLength);
			marks = new int[marksLength];
			cout << "Enter Marks of students =" << endl;
			for (int i = 0; i < marksLength; ++i)
			{
				cout << "Enter marks of student " << i + 1 << " = ";
				cin >> marks[i];
				heap.insert(marks[i]);
			}
			break;
		}

		case 2: // Get minimum marks
		{
			temp = heap.getMin();
			if (temp != -1)
			{
				cout << "Minimum marks obtained = " << temp << endl;
			}
			else
			{
				for (int i = 0; i < marksLength; ++i)
				{
					heap.insert(marks[i]);
				}
				cout << "Minimum marks obtained = " << heap.getMin() << endl;
			}
			break;
		}

		case 3: // Heap Sort
		{
			cout << "Heap Sort = " << endl;
			int *sortedMarks = heap_sort(marks, marksLength);
			for (int i = 0; i < marksLength; ++i)
			{
				cout << sortedMarks[i] << " ";
			}
			cout << endl;
			break;
		}

		case 4: // Display heap
		{
			temp = heap.getMin();
			if (temp != -1)
			{
				heap.display();
			}
			else
			{
				for (int i = 0; i < marksLength; ++i)
				{
					heap.insert(marks[i]);
				}
				heap.display();
			}
			break;
		}

		case 5: // Exit
		{
			cout << "Thank you :)" << endl;
			break;
		}

		default: // Forced exit
		{
			cout << "Exit due to wrong input!!!!!" << endl;
			exit(0);
		}
		}
	}

	return 0;
}

template <class T>
void MinHeap<T>::insert(T data)
{
	if (size == capacity)
	{
		cout << "Overflow: could not insert key" << endl;
	}
	else
	{

		size++;
		int i = size - 1;
		arr[i] = data;

	
		while (i >= 0 && arr[this->parent(i)] > arr[i])
		{
		
			swap(parent(i), i);
		
			i = this->parent(i);
		}
	}
}

template <class T>
T MinHeap<T>::getMin()
{
	if (size <= 1) 
	{
		cout << "Underflow: no element in heap" << endl;
		return -1;
	}
	else
	{ 
		return arr[0];
	}
}

template <class T>
void MinHeap<T>::heapify(int i)
{
	int l = Lchild(i);
	int r = Rchild(i);

	int smallest = i;

	if (l < size && arr[l] < arr[smallest])
	{
		smallest = l;
	}
	if (r < size && arr[r] < arr[smallest])
	{
		smallest = r;
	}

	if (smallest != i)
	{
		swap(i, smallest);
		heapify(smallest);
	}
}

template <class T>
void MinHeap<T>::heapify_itr()
{ 
	MinHeap<T> tempHeap(this->capacity);

	for (int i = 0; i < size; ++i)
	{ 
		tempHeap.insert(this->arr[i]);
	}

	for (int i = 0; i < size; ++i)
	{
		this->arr[i] = tempHeap.arr[i];
	}
}

template <class T>
void MinHeap<T>::display()
{
	cout << "Level Order Traversal: ";
	for (int i = 0; i < size; ++i)
	{ 
		cout << arr[i] << " ";
	}
	cout << endl;
}

template <class T>
void MinHeap<T>::remove(int i)
{
	this->bubble_key_to_top(i); 
	this->extract_min_key();
}

template <class T>
T MinHeap<T>::extract_min_key()
{
	T minKey = arr[0];
	arr[0] = arr[size - 1];
	size--;
	heapify_itr();

	return minKey;
}

template <class T>
void MinHeap<T>::bubble_key_to_top(int i)
{
	arr[i] = INT_MIN;
	while (i != 0 && arr[parent(i)] > arr[i])
	{
		swap(parent(i), i);
		i = parent(i);
	}
}


