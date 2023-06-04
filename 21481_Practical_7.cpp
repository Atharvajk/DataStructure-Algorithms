//============================================================================
// Name        : DSA7_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;
class Office
{
	int n;
	int a[10][10];
	string office[10];
public:
	void input();
	void display();
	void Prims();
};

void Office::input()
{
	cout<<"Enter number of offices:";
	cin>>n;
	cout<<"Enter names of offices:"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>office[i];
	}
	cout<<"Enter the cost to connect the offices:"<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			if(i==j)
			{
				a[i][j]=0;
				continue;
			}
			cout<<"Enter cost to connect "<<office[i]<<" and "<<office[j]<<" : ";
			cin>>a[i][j];
			a[j][i]=a[i][j];
		}
	}
}

void Office::display()
{
	for(int i=0;i<n;i++)
	{
		cout<<endl;
		for(int j=0;j<n;j++)
		{
			cout<<a[i][j]<<"\t";
		}
	}
}

void Office::Prims()
{
int minCost = 0, minIndex, cost = 0, count = 1;
int visit[n] = {0};
visit[0] = 1;
while (count != n) {
    minCost = 100000;

    for (int i = 0; i < n; i++) {
        if (visit[i] == 1) {
            for (int j = 0; j < n; j++) {
                if (visit[j] == 0 && a[i][j] != 0 && a[i][j] < minCost) {
                    minCost = a[i][j];
                    minIndex = j;
                }
            }
        }
    }

    visit[minIndex] = 1;
    cost += minCost;
    count++;
}
cout << "Minimum Cost is: " << cost << endl;

}

int main()
{
    Office o1;
    int choice;
    cout<<"Prim's Algorithm"<<endl;
    while(true){
    	cout<<"\nMINIMUM SPANNING TREE";
    	cout<<"\n1. Input data";
    	cout<<"\n2. Display data";
    	cout<<"\n3. Calculate minimum cost";
    	cout<<"\n4. Exit";
    	cout<<"\nEnter your choice: ";
    	cin >> choice;
    	switch(choice)
    	{
    		case 1:
    			o1.input();
    			break;
    		case 2:
    			o1.display();
    			break;
    		case 3:
    			o1.Prims();
    			break;
    		case 4:
    			cout<<"EXIT!";
    			return 0;
    		default:
    			cout<<"\nInvalid choice!";
    	}
    }
    return 0;
}
//Copyright Atharva
