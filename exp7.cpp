//============================================================================
// Name        : exp7.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
// class node{
// int src,dest;
// int priority;
// node *next;
// public:
// node(){
// priority=0;
// next=NULL;
// }
// node(int s,int d,int prio){
// src=s;
// dest=d;
// priority=prio;
// next=NULL;
// }
// friend class priorityq;
// friend class pqn;
//
// };
// class pqn{
// node*head=NULL;
// public:
// void push(int data,int prio){
// node*n=new node(data,prio);
//
// if(head==NULL){
// head=n;
// }else{
// node*temp=head;
// node*par=head;
// while(temp!=NULL){
// if(temp->priority<prio){
// par=temp;
// temp=temp->next;
// }else{
// if(temp==head){
// n->next=temp;
// head=n;
// return;
// }
//// temp->priority<prio
// n->next=par->next;
// par->next=n;
// return;
// }
//
//
// }if(temp==NULL){
// par->next=n;
// }
// }
// }
// node* pop(){
// node* ret=head;
// head=head->next;
// return ret;
// }
// void display(){
// node*temp=head;
// while(temp!=NULL){
// cout<<temp->data<<" ";
// temp=temp->next;
// }
// cout<<endl;
// }
// };
//
// class priorityq{
// node * arr[20];
// int front,back;
// public:
////void sort(){
//// for(int i=0;i<20;i++){
//// for(int i=0;j<20;j++){
////
//// }
//// }
////}
// bool isempty(){
// if(front>back){
// return true;
// }
// }
// priorityq(){
// for(int i=0;i<20;i++){
// arr[i]=NULL;
// }
// front=0;back=-1;
// }
// void enqueue(node * temp){
// arr[++back]=temp;
// }
//
//
// };

class graph
{
public:
    int ne, nv;
    int **adjmat;
    string *namearr;
    graph()
    {

        nv = ne = 0;
        cout << "Enter Number of vertices in graph: ";
        cin >> nv;
        cout << "Enter Number of edges in graph: ";
        cin >> ne;
        adjmat = new int *[nv];
        for (int i = 0; i < nv; i++)
        {
            adjmat[i] = new int[nv];
        }
        for (int i = 0; i < nv; i++)
        {
            for (int j = 0; j < nv; j++)
            {
                adjmat[i][j] = -1;
            }
        }
        namearr = new string[nv];
        cout << "Graph created!" << endl;
    }
    graph(int v, int e)
    {
        nv = v;
        ne = e;
        adjmat = new int *[nv];
        for (int i = 0; i < nv; i++)
        {
            adjmat[i] = new int[nv];
        }
        for (int i = 0; i < nv; i++)
        {
            for (int j = 0; j < nv; j++)
            {
                adjmat[i][j] = -1;
            }
        }
        namearr = new string[nv];

        cout << "Graph created!" << endl;
    }
    string upper(string org)
    {
        string mod;
        char c;
        for (int x = 0; x < org.length(); x++)
        {
            c = toupper(x);
            mod = mod + c;
        }
        return mod;
    }
    int findvertex(string start)
    {

        for (int i = 0; i < nv; i++)
        {
            // check(adjlist[i]->landmark,start);
            // cout<<"currently at "<<adjlist[i]->landmark<<endl;
            if (namearr[i] == start)
            {
                return i;
            }
        }
        cout << "Vertex " << start << " not found inside findvertex returns 0"
             << endl;
        return 0;
    }
    void insertion()
    {
        string v1, v2;
        int a, b, w;
        v1 = v2 = " ";
        a = b = w = 0;

        for (int i = 0; i < nv; i++)
        {
            cout << "Enter name of " << i + 1 << "th vertex : ";
            cin >> namearr[i];
        }
        cout << "\nEnter 2 (space seperated) vertices in which edge is present."
             << endl;
        for (int i = 0; i < ne; i++)
        {
            cout << "Edge " << i + 1 << " is present between : ";
            cin >> v1 >> v2;
            a = findvertex(v1);
            b = findvertex(v2);
            cout << "Weight of edge is: ";
            cin >> w;
            adjmat[a][b] = w;
            adjmat[b][a] = w;
        }
    }
    void display()
    {
        for (int i = 0; i < nv; i++)
        {
            cout << namearr[i] << ". ";
            for (int j = 0; j < nv; j++)
            {
                cout << " " << adjmat[i][j];
            }
            cout << endl;
        }
    }

    int findbyweight(int s, int w)
    {
        for (int i = 0; i < nv; i++)
        {
            if (adjmat[s][i] == w)
            {
                return i;
            }
        }
        cout << "Error in find by weight for input" << s << w << endl;
        return 0;
    }

    void prims(string start_node)
    {
        cout << "Prims Algorithms \nMinimun Spanning Tree" << endl;
        int curr, min, min_indx, v_indx, total_weight, src, dest;
        v_indx = 0;
        int visited[nv];
        // start_node=upper(start_node);
        curr = findvertex(start_node);
        visited[v_indx] = curr;
        v_indx++;
        while (v_indx < nv)
        {
            min = 999;

            for (int k = 0; k < v_indx; k++)
            {
                curr = visited[k];
                for (int i = 0; i < nv; i++)
                { // finding minimum
                    if (adjmat[curr][i] != -1 && adjmat[curr][i] < min)
                    {
                        bool check = true;
                        // checking min with visited
                        for (int j = 0; j < v_indx; j++)
                        {
                            if (visited[j] == i)
                            {
                                check = false;
                            }
                        }
                        if (check)
                        {
                            min = adjmat[curr][i];
                            src = curr;
                            dest = i;
                            min_indx = i;
                        }
                    }
                }
            } // end for k
            // check if min is not 999
            if (min != 999)
            {
                string srcstr = namearr[src];
                string deststr = namearr[dest];
                cout << srcstr << " , " << deststr << " = " << min << endl;

                visited[v_indx] = dest;
                v_indx++;
                adjmat[src][dest] = -1;
                adjmat[dest][src] = -1;
            }
        } // end while

    } // endprims
};

int main()
{
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    // priority queue implementation
    // pqn pq;
    // pq.push(5, 5);
    // pq.push(3, 3);
    // pq.push(2,2);
    //
    // pq.display();
    // pq.push(6,6);
    // pq.push(0,0);
    // pq.push(1,1);
    // pq.pop();pq.pop();
    //
    //
    // pq.display();

    // manual data
    //  graph g;
    //  g.nv=4;
    //
    //  int adjmat[4][4]= {{-1,2,3,5},
    //  {2,-1,1,6},
    //  {3,1,-1,7},
    //  {5,6,7,-1}};
    //  for(int m=0;m<4;m++){
    //  for(int n=0;n<4;n++){
    //  g.adjmat[m][n]=adjmat[m][n];
    //  }
    //
    //  }
    //  string arr[]={"A","B","C","D"};
    //  g.namearr=arr;
    //
    //  g.display();
    //  g.prims("B");
    //

    // original
    graph g;
    g.insertion();
    g.display();
    g.prims("A");
    return 0;
}

//input demo

// !!!Hello World!!!
// Enter Number of vertices in graph: 4
// Enter Number of edges in graph: 6
// Graph created!
// Enter name of 1th vertex : A
// Enter name of 2th vertex : B
// Enter name of 3th vertex : C
// Enter name of 4th vertex : D

// Enter 2 (space seperated) vertices in which edge is present.
// Edge 1 is present between : A B
// Weight of edge is: 2
// Edge 2 is present between : B C
// Weight of edge is: 1
// Edge 3 is present between : C D
// Weight of edge is: 7
// Edge 4 is present between : D A
// Weight of edge is: 5
// Edge 5 is present between : A C
// Weight of edge is: 3
// Edge 6 is present between : B D
// Weight of edge is: 6
// A.  -1 2 3 5
// B.  2 -1 1 6
// C.  3 1 -1 7
// D.  5 6 7 -1
// Prims Algorithms 
// Minimun Spanning Tree
// A , B = 2
// B , C = 1
// A , D = 5