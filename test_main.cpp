#include<iostream>
#include "BST.h"
using namespace std;

int main()
{
	BST bst;
	int element,n;
	cout<<"Number of elements :";
	cin>>n;
	while(n--)
	{
		cin>>element;
		if(bst.InsertElement(element)==DUPLICATE)
		cout<<"Duplicate Entry"<<endl;
	}
	
	cout<<"Inorder traversal returns"<<endl;
	bst.InOrder(bst.getRoot());
	
	cout<<"PreOrderTraversal returns"<<endl;
	bst.PreOrder(bst.getRoot());
	
	/*
	TreeNode *ptr=new TreeNode;
	if(bst.searchElement(0,&ptr)==NOT_FOUND)cout<<"element not found"<<endl;
	else cout<<"element found"<<endl;
	if(bst.searchElement(18,&ptr)==NOT_FOUND)cout<<"element not found"<<endl;
	else cout<<"element found"<<endl;
	
	//deleting elements
	if(bst.DeleteElement(4)==NOT_FOUND)cout<<"element not found"<<endl;
	else
	{
		cout<<"inorder after deletion :"<<endl;
		bst.PrintTree(INORDER);
	}
	
	if(bst.DeleteElement(2)==NOT_FOUND)cout<<"element not found"<<endl;
	else
	{
		cout<<"inorder after deletion :"<<endl;
		bst.PrintTree(INORDER);
	}
	*/
	//check whether a path sum equals a given number
	if(bst.IsHavingAPathSumEqualsGivenNumber(bst.getRoot(),41))cout<<"path exists"<<endl;
	else cout<<"No path exists"<<endl;
	if(bst.IsHavingAPathSumEqualsGivenNumber(bst.getRoot(),61))cout<<"path exists"<<endl;
	else cout<<"No path exists"<<endl;
	if(bst.IsHavingAPathSumEqualsGivenNumber(bst.getRoot(),165))cout<<"path exists"<<endl;
	else cout<<"No path exists"<<endl;
	if(bst.IsHavingAPathSumEqualsGivenNumber(bst.getRoot(),200))cout<<"path exists"<<endl;
	else cout<<"No path exists"<<endl;
	
	//find lenght of longest path and the diameter
	int diameter=500;
	cout<<"length of longest path is :"<<bst.Diameter(bst.getRoot(),&diameter)<<endl;
	cout<<"diameter is : "<<diameter<<endl;
	
	//printing left view
	//bst.PrintLeftView(bst.getRoot());
	cout<<endl;
	//printing right view
	//bst.PrintRightView(bst.getRoot());
	
	//print in spiral order
	bst.PrintSpiralInLinearTime(); 
	cout<<endl;
	//print spiral in quad time
	bst.PrintSpiralInQuadTime();
	cout<<endl;
	
	/*
	//remove non heavy paths
	bst.DeleteNonHeavyPaths(bst.getRoot(),70);
	bst.PrintTree(INORDER);
	cout<<endl;
	*/
	
	/*//remove all half nodes
	bst.RemoveAllHalfNodes(bst.getRoot());
	bst.PrintTree(INORDER);
	cout<<endl;
	*/
	
	//sum of all leaves
	cout<<"sum is : "<<bst.SumOfAllLeaves(bst.getRoot())<<endl;
	
	bst.PrintAllRootToLeafPaths(bst.getRoot());
	
return 0;		
}

