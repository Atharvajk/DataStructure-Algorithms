//============================================================================
// Name        : DSA5_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
using namespace std;
#define SIZE 26

class Node{
	string value;
	Node *next;
public:
	Node(string val){
		value=val;
		next=NULL;
	}
	friend class HashTable;
};


class HashTable{
	Node *arr[SIZE];
public:
	HashTable(){
		for(int i=0;i<SIZE;i++){
			arr[i]=NULL;
		}
	}
	int hashfunc(char w){
		int ch=w;
		return ch%26;
	}

	void insert(string word){
		int hashcode=hashfunc(word[0]);
		if(arr[hashcode]==NULL){
			arr[hashcode]=new Node(word);
		}
		else{
			Node *temp=arr[hashcode];
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=new Node(word);
		}
	}
	void display(){
		for(int i=0;i<26;i++){
			cout<<i;
			if(arr[i]!=NULL){
			Node *temp=arr[i];
				while(temp!=NULL){
					cout<<"     "<<temp->value<<"-->";
					temp=temp->next;
				}
			}
			cout<<endl;
		}
	}
};


int main() {
	HashTable ht;
	string word;
	int ch;
	while(1){
		cout<<endl<<"----------------Menu-----------------"<<endl;
		cout<<"1.Insert\n2.Display\n3.Exit"<<endl;
		cout<<"Enter your choice:";
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter string:";
				cin>>word;
				ht.insert(word);
				break;
			case 2:
				cout<<"All entries...\n";
				ht.display();
				break;
			case 3:
				exit(0);
			default:
				cout<<"Incorrect choice entered!!!";

		}
	}
	return 0;
}
//Copyright Atharva