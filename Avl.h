#ifndef __AVL_H	// Control inclusion of header files
#define __AVL_H
#include <iostream>
using namespace std;
template<class T>
class AVLTree;
/*AVLNode class represents a node of the tree*/
template<typename T>
class AVLNode{
	public:
	/*
	left->left child
	right->right child
	parnet->parent
	*/
	AVLNode *left,*right,*parent;
	T key;
	int height;
	
	AVLNode()		//default constructor
	{
		left=NULL;
		right=NULL;
		this->set_parent(NULL);
		height=0;
	}
	AVLNode(T a,AVLNode<T> *p)	//parameterized constructor
	{
		key=a;
		height=0;
		parent=p;
		left=NULL;
		right=NULL;
	}
	int get_height()		//returns height
	{
		if(this==NULL)
			return -1;
		else
			return this->height;
	}
	void deleteNode();		//deletes node
	void set_height(const int h)	//sets height of "this" node
	{
		height=h;
	}
	void operator=(const AVLNode<T>& a)		//overloading = operator  locha
	{
		if(&a==NULL)
			{
				return;
		}
		this->left=a.left;
		this->right=a.right;
		this->height=a.height;
		this->set_parent(a.parent);
		this->key=a.key;
	}
	T get_key()				//returns key
	{
		return key;
	}
	void set_key(T k)		//to set key to a particular value
	{
		key=k;
	}
	AVLNode<T>* get_parent()	//returns parent
	{
		return parent;
	}
	void set_parent(AVLNode *p)		//sets parent
	{
	
		parent=p;
	}
	~AVLNode()			//destructor
	{
	}
	void rotateL(AVLTree<T>* t);	//to rotate left
	void rotateR(AVLTree<T>* t);	//to rotate right
	void rotateLR(AVLTree<T>* t);	//left right rotation
	void rotateRL(AVLTree<T>* t);	//right left rotation
	void printTree();
	
};
/*AVLTree class represents the AVLTree*/
template<typename T>
class AVLTree{
public:
	AVLNode<T> *root;	//root->root node of the tree
	AVLTree()		//default constructor
	{
		root=NULL;
	}
	AVLTree(T a)		//parameterized constructor
	{
		root=new AVLNode<T>;
		root->key=a;
	}
	~AVLTree()		//destructor
	{
		deleteTree();
	}
	void deleteTree();	//function that deletes tree
	AVLNode<T> *lookup(const T &key);	//to search for a key and retrun the corresponding node
	AVLNode<T> *insert(const T &key);	//to insert a key at its position
	void remove(const T &key);	//to remove a node of given key
	void printAVL();	//to print AVLTree
	
};


#include "Avl.inl"

#endif 
