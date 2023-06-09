#include <iostream>
#include <math.h>
using namespace std;
class heap
{
	int *arr;
	int *sortedarr;
	int totalsize;
	int pos = -1;

public:
	heap()
	{
		cout << "Size ";
		cin >> totalsize;
		arr = new int[totalsize];
		sortedarr = new int[totalsize];
	}
	heap(int n)
	{
		totalsize = n;
		arr = new int[totalsize];
		sortedarr = new int[totalsize];
	}
	void heapify(int i)
	{
		while (1)
		{
			int par = floor((i - 1) / 2);
			// cout<<arr[i]<<"ka parent "<<arr[par]<<endl;
			if (arr[par] < arr[i])
			{
				swap(arr[i], arr[par]);
				i = par;
			}
			else
			{
				break;
			}
		}
	}
	void saveorignal()
	{
		for (int i = 0; i < totalsize; i++)
		{
			sortedarr[i] = arr[i];
		}
	}
	void insert(int val)
	{
		if (pos < totalsize - 1)
		{
			arr[++pos] = val;
		}
		heapify(pos);
		// sortedarr=arr;
	}

	void heapsort(int m = 0)
	{
		if (m == 0)
		{

			for (int i = 0; i < totalsize; i++)
			{
				cout << delete1() << " ";
			}
			cout << endl;
		}
		else
		{
			int arrmin[totalsize];
			for (int i = totalsize - 1; i >= 0; i--)
			{
				arrmin[i] = delete1();
				// cout<<delete1()<<" ";
			}
			cout << "done" << endl;
			for (int i = 0; i < totalsize; i++)
			{
				cout << arrmin[i] << " ";
			}
			cout << endl;
		}
	}
	int delete1()
	{

		int todel = arr[0];
		arr[0] = 0;
		for (int i = 1; i < totalsize; i++)
		{
			heapify(i);
		}
		return todel;
	}
	void display()
	{
		cout << "\nDisplay: " << endl;
		for (int i = 0; i < totalsize; i++)
		{
			cout << sortedarr[i] << " ";
		}
		cout << endl;
	}
};
int main()
{
	heap h(9);
	h.insert(50);
	h.insert(10);
	h.insert(60);
	h.insert(80);
	h.insert(40);
	h.insert(5);
	h.insert(20);
	h.insert(12);
	h.insert(15);
	h.saveorignal();
	h.display();
	cout << "Aplyingheap sort" << endl;

	// 0 for max, 1 for min
	h.heapsort(0);
	h.display();
	return 0;
}