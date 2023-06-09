#include<iostream>
using namespace std;
class node{
int data;
node *left;
node *right;
node(){
    left=right=NULL;
    data=0;

}
node(int dat){
    left=right=NULL;
    data=dat;

}
friend class BT;
};

class BT{
node* root=NULL;
public:
void insert_rec(node * r){
   if(r){
     int val;
    cout<<"Enter data value to left of "<<r->data<<" (press 99 for skip)";
    cin>>val;
    if(val!=99){
        node * n=new node(val);
        r->left=n;
    }
    cout<<"Enter data value to right of "<<r->data<<" (press 99 for skip)";
    cin>>val;
    if(val!=99){
        node * n=new node(val);
        r->right=n;
    }
    insert_rec(r->left);
    insert_rec(r->right);
    }


}
void add_data(int dat){
    if(root==NULL){
        root=new node(dat);
    }
    insert_rec(root);

}

void inorder(node* r){
    if(r){

    inorder(r->left);
    cout<<r->data<<" --> ";
    inorder(r->right);
    }
}
node* getroot(){
    return root;
}

void manualfeed(){
    root=new node(10);
    root->left=new node(5);
    root->right=new node(15);
    root->left->left=new node(3);
    root->left->right=new node(7);
    root->right->left=new node(12);
    
    root->right->right=new node(18);
    
    
}
void swap(node* r){
    if(r){
        node* n=r->left;
        r->left=r->right;
        r->right=n;
        swap(r->left);
        swap(r->right);
    }
}

int height(node* r){
    if(r){
        int l=height(r->left);
        int h=height(r->right);
        return (max(l,h)+1);
    }
    return -1;
}


void copy(node * r,node* &temp){
        if(r){
            copy(r->left,temp->left);
            copy(r->right,temp->right);
            temp->data=r->data;
        }

    }
void operator=(node* &temp){
    copy(root,temp);
}
};

int main(){
    BT b;
    // b.add_data(10);
    b.manualfeed();
    b.inorder(b.getroot());
    cout<<endl;
    // b.swap(b.getroot());
    // BT p=b;
    // p.inorder(p.getroot());
    cout<<b.height(b.getroot());

    cout<<endl;
    return 0;
}