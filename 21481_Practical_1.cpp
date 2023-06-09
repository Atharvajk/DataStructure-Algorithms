#include<iostream>
using namespace std;

class node{
    node *left,*right;
    string key,value;
    public:
    node(){
        left=right=NULL;
        value=key="Default";
    }
    node(string k,string v){
        left=right=NULL;
        value=v;
        key=k;
    }
    void displaynode(){
        cout<<"\nKey= "<<key;
        cout<<"\nValue= "<<value<<endl;
    }
friend class bst;
friend class Stack;
};

class Stack{
	node* arr[20];
	int top=-1;
public:
	Stack(){
		for(int i=0;i<20;i++){
			arr[i]=NULL;
		}
	}
	void push(node *temp){
		arr[++top]=temp;

	}
	bool isempty(){
		if(top==-1){
			return true;
		}
		return false;
	}
	node* pop(){
		if(!isempty()){
			node* ret=arr[top];
			arr[top]=NULL;
			top--;
			return ret;

		}
		cout<<"\nEmpty returning NULL"<<endl;
		return NULL;

	}
};

class bst{
node* root;
public:
bst(){
    root=NULL;
}
int find(string k, node*&curr,node* &par){

    if(curr==NULL){
        return 1;
    }
    int count=0;
    while(curr!=NULL){
        if(k<curr->key){
            par=curr;
            curr=curr->left;
            count++;
        }else if(k==curr->key){
            return ++count;
        }
        else{
            par=curr;
            curr=curr->right;
            count++;

        }
    }
    return count;


}
void search(string k){
	node* curr=root;
	node* par=NULL;
	int comp=find(k,curr,par);
	if(curr==NULL){
		cout<<"\nData not found!"<<endl;
	}
	if(curr->key==k){
		cout<<"\nData found! in "<<comp<<" Comparisions."<<endl;
		curr->displaynode();
	}
}

void insert(string k,string v){
	if(root==NULL){
		node* n=new node(k,v);
		root=n;
		return;
	}
    node* curr=root;
    node* par=NULL;

    find(k,curr,par);
    if(curr!=NULL){
        cout<<"Duplicate found!"<<endl;
        return;
    }
    node* n=new node(k,v);

    if(k<par->key){
        par->left=n;
    }else {
        par->right=n;
    }

}
void inorder(node* r){
    if(r){
        inorder(r->left);
//        r->displaynode();
        cout<<r->key<<"--> ";
        inorder(r->right);
    }
}
void inorder_iterative(){
	Stack s;
    node* curr=root;
    s.push(curr);
    curr=curr->left;
    while(!s.isempty()||curr!=NULL){
        if(curr!=NULL){
            s.push(curr);
            curr=curr->left;
        }else{
            curr=s.pop();
            cout<<curr->key<<" --> ";
            curr=curr->right;
        }
    }



}

void preorder_iterative(){
    Stack s;
    node* curr=root;
    s.push(curr);
    curr->displaynode();
    curr=curr->left;
    while(!s.isempty() || curr!=NULL){
        if(curr!=NULL){
            s.push(curr);
            curr->displaynode();
            curr=curr->left;
        }else{
            curr=s.pop();
            curr=curr->right;

        }
    }

}
void postorder_iterative(){
    node* curr=root;
    Stack s1,s2;
    s1.push(curr);
    while(!s1.isempty()){
        curr=s1.pop();
        if(curr){
            s2.push(curr);
            s1.push(curr->left);
            s1.push(curr->right);
        }
    }
    while(!s2.isempty()){
        curr=s2.pop();
        curr->displaynode();
    }
}
void delete_1(node* curr,node* par){
    //if leaf node
    if(curr->left==NULL && curr->right==NULL){
        if(curr->key<par->key){
            par->left=NULL;
            delete curr;
            return;

        }
        else{
            par->right=NULL;
            delete curr;
            return;
        }
    }else{
        //not leaf
        if(curr->left!=NULL){
            //only left present
            if(curr->key<par->key){
            par->left=curr->left;
            delete curr;
            return;

        }
        else{
            par->right=curr->left;
            delete curr;
            return;
        }
        }else{
            //only right

             if(curr->right!=NULL){
            //only left present
            if(curr->key<par->key){
            par->left=curr->right;
            delete curr;
            return;

        }
        else{
            par->right=curr->right;
            delete curr;
            return;
        }
        }
    }
}
}
void delete_2ch(node* curr,node* par){
par=curr;
node* temp=curr->right;
while(temp->left!=NULL){
    curr=temp;
    temp=temp->left;
}
par->key=temp->key;
par->value=temp->value;
delete_1(temp,curr);
}
void delete_node(string k){
    node* todel=root;
    node* par=root;
    find(k,todel,par);
    if(todel->key==k){


    if(todel->left!=NULL && todel->right!=NULL){
        delete_2ch(todel,par);
    }else{
        delete_1(todel,par);
    }
    }else{
        cout<<"Entry not founD!"<<endl;
    }
}

node* getroot(){
    return root;
}
};

//dictionary bst key value,show comparison on search
int main(){
    bst bt;
    bt.insert("mango","fruit");
    bt.insert("apple","fruit");
    bt.insert("acord","fruit");
    bt.insert("turbuja","fruit");
    bt.insert("jackfruit","fruit");
    bt.insert("lemonde","fruit");
//    bt.inorder(bt.getroot());
//    bt.search("turuja");
    cout<<"Inorder iterative bellow"<<endl;
    bt.inorder_iterative();
    cout<<endl;
    bt.delete_node("apple");
    bt.inorder_iterative();

    return 0;
}
