#include <iostream>
using namespace std;

class Node{
	public:	 
	int data;
	int height;
	Node* lchild;
	Node * rchild;	 
   // COnstructor 	
	Node(int x){
		data =x;
		lchild=rchild = nullptr;
		// Updateing height to 1 instead 0.
		height = 1;
	}
};



class AVL{
public:
  Node * root;
   // Constructor 
   AVL(){root= nullptr;}
   
  // Accessor
   Node* getRoot(){ return root;}
   void Inorder(Node *p);
   
  //Facilitators
   int Height(Node * p);
   int BalanceFactor(Node *p);
   
   //--- Hieght Balancers --
   Node* LLRotation(Node *p);
   Node* LRRotation(Node *p);
   Node* RLRotation(Node *p);
   Node* RRRotation(Node *p);
   
  // Modifiers
   Node* Insert(Node *p, int key);
 
   
};

Node* AVL::Insert(Node* p, int x){

   if(p == nullptr)
      return new Node(x); 
	  
   if( x > p->data)
       p->rchild = Insert(p->rchild, x);
	   
   if( x < p->data )
       p->lchild = Insert(p->lchild, x);
	
	// Update height of node
	p->height = Height(p);

    // Balancing Tree	   
	   
   if(BalanceFactor(p)==2){
         if(BalanceFactor(p->lchild)==1)
		    return LLRotation(p);
		 if(BalanceFactor(p->lchild)==-1)
		    return LRRotation(p);
   }
   else if(BalanceFactor(p) == -2){
         if(BalanceFactor(p->rchild)==1)
		    return RRRotation(p);
		 if(BalanceFactor(p->rchild)==-1)
		    return RLRotation(p);
  }
   return p;   
}


int AVL::Height(Node *p) {
    int hl;
    int hr;
 
    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;
 
    return hl > hr ? hl + 1 : hr + 1;
}
 
int AVL::BalanceFactor(Node *p) {
    int hl;
    int hr;
 
    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;
 
    return hl - hr;
}

void AVL :: Inorder(Node *p) {
    if(p){
	    Inorder(p->lchild);
        cout << p->data <<", " ;
        Inorder(p->rchild);
    }
}

Node* AVL::LLRotation(Node *p) {
    Node* pl = p->lchild;
    //Node* plr = pl->rchild;
    p->lchild = pl->rchild; 
    pl->rchild = p;

 
    // Update height
    p->height = Height(p);
    pl->height = Height(pl);
 
    // Update root
    if (root == p){
        root = pl;
    }
    return pl;
}
 
Node* AVL::RRRotation(Node *p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;
 
    pr->lchild = p;
    p->rchild = prl;
 
    // Update height
    p->height = Height(p);
    pr->height = Height(pr);
 
    // Update root
    if (root == p){
        root = pr;
    }
    return pr;
}

Node* AVL::LRRotation(Node * p){
	// Backup root-L-R node
    Node *newNode = p->lchild->rchild;
	
	p->lchild->rchild = newNode->lchild;
	p->lchild->height = Height(p->lchild);
	
	newNode->lchild = p->lchild;
	p->lchild = newNode->rchild;
	p->height = Height(p);
	
	newNode->rchild = p;
	newNode->height = Height(newNode);
	if(p== root){
		root = newNode;
	}
	return newNode;
}
Node* AVL::RLRotation(Node * p){
// Backup root-L-R node
    Node *newNode = p->rchild->lchild;
	
	p->rchild->lchild = newNode->rchild;
	p->rchild->height = Height(p->rchild);
	
	newNode->rchild = p->rchild;
	p->rchild = newNode->lchild;
	p->height = Height(p);
	
	newNode->lchild = p;
	newNode->height = Height(newNode);
	if(p== root){
		root = newNode;
	}
	return newNode;
}
int main()
{
  // LL Rotation
    AVL tll;
    tll.root = tll.Insert(tll.root, 30);
    tll.root = tll.Insert(tll.root, 20);
    tll.root = tll.Insert(tll.root, 25);
 
    tll.Inorder(tll.getRoot());
    cout << endl;
 
    // RR Rotation
    AVL trr;
    trr.root = trr.Insert(trr.root, 11);
    trr.root = trr.Insert(trr.root, 21);
    trr.root = trr.Insert(trr.root, 15);
 
    trr.Inorder(trr.getRoot());
    cout << endl;
 
    return 0;
}