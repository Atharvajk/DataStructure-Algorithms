//============================================================================
// Name        : DSA4_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
using namespace std;
#define SIZE 11

class Hash{
	string name;
	long telephone;
public:
	Hash(){
		name="";
		telephone=0;
	}
	Hash(string name,long tele){
		this->name=name;
		telephone=tele;
	}
	friend class HashTable;
};

class HashTable{
	Hash *arr[SIZE];
public:
	HashTable(){
		for(int i=0;i<SIZE;i++){
			arr[i]=NULL;
		}
	}
	int hashfunc(long tele){
		return tele%11;
	}

	int linearprobing(int hashcode){
		int start=hashcode;
		hashcode++;
		while(arr[hashcode]!=NULL){
			if(start==hashcode){
				break;
			}
			else{
				hashcode=(hashcode+1)%11;
			}
		}
		if(arr[hashcode]==NULL){
			return hashcode;
		}
		else{
			return -999;
		}
	}
	void insert(string name,long telephone){ //without replacement

		int hashcode=hashfunc(telephone);
		if(arr[hashcode]==NULL){
			arr[hashcode]=new Hash(name,telephone);
		}
		else{
			hashcode=linearprobing(hashcode);
			if(hashcode!=-999){
				arr[hashcode]=new Hash(name,telephone);
			}
			else{
				cout<<"Hashtable Overflow"<<endl;
				return;
			}
		}

	}
	void insertwr(string name,long telephone){ //with replacement

		int hashcode=hashfunc(telephone);
		if(arr[hashcode]==NULL){
			arr[hashcode]=new Hash(name,telephone);
		}
		else{
			int prev_ele_hashcode=hashfunc(arr[hashcode]->telephone);
			if(prev_ele_hashcode==hashcode){
				hashcode=linearprobing(hashcode);
				if(hashcode!=-999){
					arr[hashcode]=new Hash(name,telephone);;
				}
				else{
					cout<<"Hashtable Overflow"<<endl;
					return;
				}
			}
			else{
				prev_ele_hashcode=linearprobing(prev_ele_hashcode);
				if(prev_ele_hashcode!=-999){
					arr[prev_ele_hashcode]=new Hash(arr[hashcode]->name,arr[hashcode]->telephone);;
				}
				else{
					cout<<"Hashtable Overflow"<<endl;
					return;
				}
				arr[hashcode]->name=name;
				arr[hashcode]->telephone=telephone;
			}
		}
	}



	int search(long tele){
		int cnt=1;
		int hashcode=hashfunc(tele);
		if(arr[hashcode]->telephone==tele){
			cout<<"\n---------Record Found---------\nName="<<arr[hashcode]->name<<endl<<"Telephone="<<arr[hashcode]->telephone<<endl;
			return cnt;
		}
		else{
			int start=hashcode;
			hashcode++;
			cnt++;

			while(arr[hashcode]->telephone!=tele){
				if(start==hashcode){
					cout<<"Record Not Present"<<endl;
					return -99;
				}
				else{
					hashcode=(hashcode+1)%11;
					cnt++;
				}
			}
			cout<<"\n---------Record Found---------\nName="<<arr[hashcode]->name<<endl;
			return cnt;

		}
	}
	void displayall(){
		cout<<endl;
		cout<<"SR. \t"<<"NAME           \t"<<"TELEPHONE"<<endl;
		for(int i=0;i<SIZE;i++){
			if(arr[i]!=NULL){
				cout<<i<<". \t"<<arr[i]->name<<"           \t"<<arr[i]->telephone<<endl;
			}
			else{
				cout<<i<<". \t"<<endl;
			}
		}
		cout<<endl;
	}
};

void menu(){
	HashTable ht,ht2;
	int ch,cmp,cmp2;string name;long tele;
	while(1){
		cout<<endl<<"----------------Menu-----------------"<<endl;
		cout<<"1.Insert\n2.Search\n3.DisplayALL\n4.Exit"<<endl;
		cout<<"Enter your choice:";
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter Data\nName= ";
				cin>>name;
				cout<<"\nTelephone = ";
				cin>>tele;
				ht.insert(name, tele);
				ht2.insertwr(name,tele);
				//ht.displayall();
				break;

			case 2:
				cout<<"Enter telephone number to search = ";
				cin>>tele;
				cmp=ht.search(tele);
				cmp2=ht2.search(tele);
				cout<<"\nIn "<<cmp<<" Comparisons using linear probing without replacement."<<endl;
				cout<<"\nIn "<<cmp2<<" Comparisons using linear probing with replacement."<<endl;


			break;
			case 3:
				cout<<"\n-----------------Without replacement---------------------"<<endl;
				ht.displayall();

			break;
			case 4:
				exit(0);
			default:
				cout<<"Incorrect choice entered!!!";
		}
	}
}
int main() {
menu();
return 0;
}
//Copyright Atharva