/* a small main function to demonstrate AVLTree class*/
#include "Avl.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int main()
{
	int v;
	AVLTree<int> t;
	for(int i=0;i<10;i++)
	{	
		
		v=rand()%50;
	 	cout<<"\nInserting "<<(i+1)<<"th number= "<<v<<"\n";
		t.insert(v);
		
		
	}
	cout<<"\ntree after all insertions\n";
	t.root->printTree();
	t.remove(35);
	cout<<"\noutput\n";
	t.root->printTree();
	t.remove(49);
	cout<<"\noutput\n";
	t.root->printTree();
	
	
}
