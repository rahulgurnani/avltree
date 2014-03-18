#include "Avl.h"
#include <iostream>
/*to delete tree*/
template<typename T>
void AVLTree<T>::deleteTree()
{
	AVLNode <T>*root=this->root;
	if(root!=NULL)
	{
		root->left->deleteNode();
		root->right->deleteNode();
	}
	delete root;
}

template<typename T>
void AVLNode<T>::deleteNode()	/*to delete a specific node*/
{
	AVLNode <T>*root=this;
	if(root!=NULL)
	{
		root->left->deleteNode();
		root->right->deleteNode();
	}
	delete root;
}
template<typename T>
AVLNode<T>* AVLTree<T>::lookup(const T &key)	/*to search for a key*/
{
	AVLNode <T>*root=this->root;
	if(this==NULL)
		return NULL;
	while(root!=NULL)
	{
		if(key<root->root->key)
		{	
			root=root->left;
		}
		else if(key>root->root->key)
		{
			root=root->right;
		}
		else
		{
			return this;
		}
	}
	if(root==NULL)
		return root;
}
int max(int a,int b)	/*to find max out of two numbers*/
{
	return ((a>b)?a:b);
}
int absolute(int a)	/*to return absolute value*/
{
	return ((a>0)?a:(-a));
}
template<typename T>
int new_height(AVLNode<T>* a)	/*returns updated height*/
{
	return(1+max(a->right->get_height(),a->left->get_height()));
}
	




template<typename T>
AVLNode<T>* AVLTree<T>::insert(const T &key)	/*to insert a key*/
{
	/*	
		the following variables:
		root->used for traversing along the tree
		prev->the previous(or parent)of root
	*/
	AVLNode <T>*root=this->root;
	AVLNode <T>*prev=NULL;		
	/*
		Traversing along the tree to reach the place where to insert the new node or returns 
		the node if it is already present in the tree
	*/
	while(root!=NULL)
	{
		
		if(key<root->key)
			{
				prev=root;
				root=root->left;
		}
		else if(key>root->key)
			{
				prev=root;
				root=root->right;
		}
		else
			return root;
	}
	root=new AVLNode<T>(key,prev);
	/*In case the tree was empty the folowing is executed*/
	if(prev==NULL)
	{
		this->root=root;
		return root;
	}
	
	/*the following code attaches the new node (root) to the tree*/
	if(key>prev->key)
		prev->right=root;
	else
		prev->left=root;
	
	AVLNode <T>*ans=root;		/*ans stores the node to be returned*/
	root=prev;
	/*the following maintains height and balance of the tree*/
	while(root!=NULL)
	{
		if(root->get_height()!=new_height(root))
		{
			root->set_height(new_height(root));
			if(root->parent==NULL)  //locha can be removed
				this->root=root;
		}
		/*if the tree is lft heavy the following code is executed*/
		if((root->right->get_height()-root->left->get_height())==-2)
		{
			if(key<root->left->key)
				root->rotateR(this);
			else
				root->rotateLR(this);
		}
		/*if the tree is right heavy then the following code is executed*/
		else if((root->right->get_height()-root->left->get_height())==2)
		{
			if(key>root->right->key)
				root->rotateL(this);
			else
				root->rotateRL(this);
		}
		root=root->parent;
		
	}

	return ans;
}
template<typename T>
void AVLNode<T>::rotateL(AVLTree<T>* t)
{
	AVLNode<T> *a,*b,*c;
	a=this;
	if(this!=NULL)
		b=this->right;
	if(this->right!=NULL)
		c=this->right->left;
	else
		c=NULL;
	if(b!=NULL)
		b->parent=this->parent;
	if(this->parent!=NULL && b!=NULL)
	{
		if(this->parent->key>b->key)
			this->parent->left=b;
		else
			this->parent->right=b;
	}
	else 
		t->root=b;
	if(a!=NULL)
	{
		a->right=c;
		a->height=new_height(a);
	}
	if(a!=NULL)
		a->parent=b;
	if(b!=NULL)
	{
		b->left=a;
		b->height=new_height(b);
	}
	if(c!=NULL)
		c->parent=a;
	
}
template<typename T>
void AVLNode<T>::rotateR(AVLTree<T>* t)
{
	AVLNode<T> *a,*b,*c;
	a=this;
	if(this!=NULL)
		b=this->left;
	if(this->left!=NULL)
		c=this->left->right;
	else
		c=NULL;
	if(b!=NULL)
		b->parent=this->parent;
	if(this->parent!=NULL && b!=NULL)
	{
		if(this->parent->key>b->key)
			this->parent->left=b;
		else
			this->parent->right=b;
	}
	else 
		t->root=b;
	if(a!=NULL)
	{
		a->left=c;
		a->height=new_height(a);
	}
	if(a!=NULL)
		a->parent=b;
	if(b!=NULL)
	{
		b->right=a;
		b->height=new_height(b);
	}
	if(c!=NULL)
		c->parent=a;
	
}

template<typename T>
void AVLNode<T>::rotateLR(AVLTree<T>* t)
{
	this->left->rotateL(t);
	this->rotateR(t);

}
template<typename T>
void AVLNode<T>::rotateRL(AVLTree<T>* t)
{
	this->right->rotateR(t);

	this->rotateL(t);
}
template<typename T>
void AVLNode<T>::printTree()
{
	if(this==NULL)
		return;
	else
	{
		cout<<"\nkey ="<<this->key<<" height= "<<height;
		if(this->left!=NULL)
			cout<<" left ="<<this->left->key;
		if(this->right!=NULL)
			cout<<" right ="<<this->right->key;
		if(this->parent==NULL)
			cout<<" parent=NULL";
		else
			cout<<" parent="<<this->parent->key;
		this->left->printTree();
		this->right->printTree();
	}
}

template<typename T>
void AVLTree<T>::remove(const T& key)
{
   /*	

		the following variables:
		root->used for traversing along the tree
		prev->the previous(or parent)of root
   */	
   	cout<<"\nDeleting key= 	"<<key<<"\n";
	AVLNode <T>*root=this->root;
	AVLNode <T>*prev=NULL;		
	/*
		Traversing along the tree to reach the place where to insert the new node or returns 
		the node if it is already present in the tree
	
	*/
   
	while(root!=NULL)
	{
			
		if(key<root->key)
			{
				prev=root;
				root=root->left;
		}
		else if(key>root->key)
			{
				prev=root;
				root=root->right;
		}
		else
			break;
	}
	/* No occurrence of key found */   
	if(root==NULL)
		return;
   	/* key is found */
   
   
   
   AVLNode<T> *q1;
   int a,b,c;	

   /* Now delete key currently pointed to by root. */
   /* The parent is pointed to by prev. It is NULL, if q is the root. */

   if (root -> left == NULL) {
      if (prev == NULL) this->root = root -> right;                           /* Root is deleted */
      else if (key < prev -> key) {
      	prev -> left = root -> right;
      	 while(1)
      	{
      		prev->set_height(new_height(prev));	
		/*if the tree is right heavy then the following code is executed*/
		if((prev->right->get_height()-prev->left->get_height())==2)
		{
			a=prev->left->get_height();
			b=prev->right->left->get_height();
			c=prev->right->right->get_height();
			if((c-a)==1)
				prev->rotateL(this);
			else
				prev->rotateRL(this);
		}      		
      		
      		prev=prev->parent;
 		if(prev==NULL)
      				break;     		
      	}
      }
      else {
      	prev -> right = root -> right;
  	 while(1)
      	{
      		
      		prev->set_height(new_height(prev));
      		/*if the tree is left heavy then the following code is executed*/
		if((prev->left->get_height()-prev->right->get_height())==2)
		{
			
			a=prev->right->get_height();
			b=prev->left->right->get_height();
			c=prev->left->left->get_height();
			if((c-a)==1)
				prev->rotateR(this);
			else
				prev->rotateLR(this);
		}
		/*if the tree is right heavy then the following code is executed*/
	      		if((prev->right->get_height()-prev->left->get_height())==2)
			{
				a=prev->left->get_height();
				b=prev->right->left->get_height();
				c=prev->right->right->get_height();
				if((c-a)==1)
					prev->rotateL(this);
				else
					prev->rotateRL(this);
			}
		
      		
      		prev=prev->parent;
      		if(prev==NULL)
      			break;
      	}
      }
   } else if (root -> right == NULL) {
      if (prev == NULL) this->root = root ->left;                           /* Root is deleted */
      else if (key < prev -> key) {
      		prev -> left = root -> left;
      	      	 while(1)
	      	{

	      		prev->set_height(new_height(prev));
		/*if the tree is left heavy then the following code is executed*/
		if((prev->left->get_height()-prev->right->get_height())==2)
		{
			a=prev->right->get_height();
			b=prev->left->right->get_height();
			c=prev->left->left->get_height();
			if((c-a)==1)
				prev->rotateR(this);
			else
				prev->rotateLR(this);
		}
		/*if the tree is right heavy then the following code is executed*/
	      	if((prev->right->get_height()-prev->left->get_height())==2)
		{
			a=prev->left->get_height();
			b=prev->right->left->get_height();
			c=prev->right->right->get_height();
			if((c-a)==1)
				prev->rotateL(this);
			else
				prev->rotateRL(this);
		}
	      		prev=prev->parent;
	      		if(prev==NULL)
      				break;
	      		
	      	}
      }
      else 
      {
      		prev -> right = root -> left;
      	      	 while(1)
	      	{
	      		prev->set_height(new_height(prev));
		/*if the tree is left heavy then the following code is executed*/
		if((prev->left->get_height()-prev->right->get_height())==2)
		{
			a=prev->right->get_height();
			b=prev->left->right->get_height();
			c=prev->left->left->get_height();
			if((c-a)==1)
				prev->rotateR(this);
			else
				prev->rotateLR(this);
		}
	      		/*if the tree is right heavy then the following code is executed*/
	      	if((prev->right->get_height()-prev->left->get_height())==2)
		{
			a=prev->left->get_height();
			b=prev->right->left->get_height();
			c=prev->right->right->get_height();
			if((c-a)==1)
				prev->rotateL(this);
			else
				prev->rotateRL(this);
		}
	      		prev=prev->parent;
	      		if(prev==NULL)
      				break;
	      	}
      }
   } else {                                       /* Find immediate successor */
      q1 = root;
      prev = root; root = root -> right;
      while (root -> left != NULL) {
         prev = root;
         root = root -> left;
      }
      q1 -> key = root -> key;                  /* Swap with immediate successor */
      AVLNode<T>* root1=root;
      if (prev == q1) {
	      	prev -> right = root -> right;         /* Delete the immediate successor */
		 while(1)
	      	{
	      		prev->set_height(new_height(prev));
	      		/*if the tree is left heavy then the following code is executed*/
			if((prev->left->get_height()-prev->right->get_height())==2)
			{
				a=prev->right->get_height();
				b=prev->left->right->get_height();
				c=prev->left->left->get_height();
				if((c-a)==1)
					prev->rotateR(this);
				else
					prev->rotateLR(this);
			}
	      		/*if the tree is right heavy then the following code is executed*/
	      		if((prev->right->get_height()-prev->left->get_height())==2)
			{
				a=prev->left->get_height();
				b=prev->right->left->get_height();
				c=prev->right->right->get_height();
				if((c-a)==1)
					prev->rotateL(this);
				else
					prev->rotateRL(this);
			}
	      		prev=prev->parent;
	      		if(prev==NULL)
      				break;
	      	}
      }
      else {
	      prev -> left = root -> right;
	      while(1)
	      {
	      	prev->set_height(new_height(prev));
	      	/*if the tree is left heavy then the following code is executed*/
		if((prev->left->get_height()-prev->right->get_height())==2)
		{
			a=prev->right->get_height();
			b=prev->left->right->get_height();
			c=prev->left->left->get_height();
			if((c-a)==1)
				prev->rotateR(this);
			else
				prev->rotateLR(this);
		}
	      	/*if the tree is right heavy then the following code is executed*/
	      	if((prev->right->get_height()-prev->left->get_height())==2)
		{
			a=prev->left->get_height();
			b=prev->right->left->get_height();
			c=prev->right->right->get_height();
			if((c-a)==1)
				prev->rotateL(this);
			else
				prev->rotateRL(this);
		}
	      	prev=prev->parent;
		if(prev==NULL)
      				break;	      	
	      }
      }
      
   }

   delete root;
   
}
