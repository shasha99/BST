#include <iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

enum returnCode
{
    NOT_FOUND,
    DUPLICATE,
    SUCCESS,
    UNRECOGNIZED
};

enum TraversalType
{
    PREORDER,
    INORDER,
    POSTORDER
};


typedef struct TreeNode
{
    int data;
    struct TreeNode *left,*right;
}TreeNode;

typedef struct NodeWithHeight
{
	int height;
	TreeNode* node;
}NodeWithHeight;


class BST
{
    TreeNode* root;
    
    public:
    BST();
    BST(TreeNode *ptr);
    TreeNode* getRoot(void);
    void setRoot(TreeNode* ptr);
    returnCode insertElement(TreeNode* node);
    returnCode insertElement(int val);
    returnCode searchElement(int val,TreeNode** ret);
    void preOrder(TreeNode* ptr);
    void inOrder(TreeNode* ptr);
    void postOrder(TreeNode* ptr);
    returnCode printTree(TraversalType t);
    void clearTree(TreeNode* ptr);
    returnCode deleteElement(int val);
    bool isHavingAPathSumEqualsGivenNumber(TreeNode* ptr,int val,int sum=0);
    int diameter(TreeNode* ptr,int* diameter);
    void printLeftView(TreeNode* ptr,int height=0);
    void printRightView(TreeNode* ptr,int height=0);
    void printSpiralInLinearTime();
    void printSpiralInQuadTime();
    void printSpiralUtility(TreeNode* ptr,int label,bool isEven=true,int height=0);
    bool deletePathWithWeightNotEqualsGivenVal(TreeNode* ptr,int val,int sum=0);
    bool deleteNonHeavyPaths(TreeNode* ptr,int val,int sum=0);
    void removeAllHalfNodes(TreeNode* ptr,TreeNode* parent=NULL);
    int sumOfAllLeaves(TreeNode* ptr);
    void printAllRootToLeafPaths(TreeNode* ptr,int height=0);
};

BST::BST()
{
	root=NULL;
}
    
BST::BST(TreeNode *ptr)
{
	this->root=ptr;
}

TreeNode* BST::getRoot(void)
{
	return root;
}

void BST::setRoot(TreeNode* root)
{
	this->root=root;
}

returnCode BST::InsertElement(TreeNode* node)
{
	if(root==NULL)root=node;
	else
	{
		TreeNode* temp=root;
		TreeNode* prev=NULL;
		while(temp!=NULL)
		{
			prev=temp;
			int comp=temp->data-node->data;
			if(!comp)return DUPLICATE;
			else if(comp>0) temp=temp->left;
			else temp=temp->right;
		}
		int comp=prev->data-node->data;
		if(comp>0)prev->left=node;
		else prev->right=node;
	}
	return SUCCESS;
}

returnCode BST::InsertElement(int val)
{
	TreeNode *node=new TreeNode;
	node->data=val;
	node->left=node->right=NULL;
	return InsertElement(node);
}

returnCode BST::SearchElement(int val,TreeNode** ret)
{
	TreeNode* temp=root;
	while(temp!=NULL)
	{
		int comp=temp->data-val;
		if(!comp)
		{
			*ret=temp;
			return SUCCESS;
		}
		else if(comp>0) temp=temp->left;
		else temp=temp->right;
	}
	return NOT_FOUND;
}

void BST::PreOrder(TreeNode* ptr)
{
	if(ptr!=NULL)
	{
		cout<<ptr->data<<"  ";
		PreOrder(ptr->left);
		PreOrder(ptr->right);
	}
}

void BST::InOrder(TreeNode* ptr)
{
	if(ptr!=NULL)
	{
		InOrder(ptr->left);
		cout<<ptr->data<<"  ";
		InOrder(ptr->right);
	}
}

void BST::PostOrder(TreeNode* ptr)
{
	if(ptr!=NULL)
	{
		PostOrder(ptr->left);
		PostOrder(ptr->right);
		cout<<ptr->data<<"  ";
	}
}

returnCode BST::PrintTree(TraversalType t)
{
	if(t==PREORDER)PreOrder(root);
	else if(t==INORDER)InOrder(root);
	else if(t==POSTORDER)PostOrder(root);
	else return UNRECOGNIZED;
	return SUCCESS;
}

//more changes are reuired in this.
void BST::ClearTree(TreeNode* ptr)
{
	if(ptr!=NULL)
	{
		ClearTree(ptr->left);
		ClearTree(ptr->right);
		delete ptr;
	}
}

returnCode BST::DeleteElement(int val)
{
	TreeNode *prev=NULL,*temp=root;
	while(temp!=NULL && temp->data!=val)
	{
		prev=temp;
		if(temp->data > val)temp=temp->left;
		else temp=temp->right;
	}
	if(temp!=NULL)
	{
		if(temp->left!=NULL && temp->right!=NULL)
		{
			TreeNode *ptr=temp;
			if(prev->left==temp)prev->left=temp->right;
			else prev->right=temp->right;
			temp=temp->right;
			while(temp->left!=NULL)temp=temp->left;
			temp->left=ptr->left;
			delete ptr;
			return SUCCESS;
		}
		else if(temp->right==NULL)
		{
			if(temp==prev->right)prev->right=temp->left;
			else prev->left=temp->left;
		}
		else
		{
			if(temp==prev->right)prev->right=temp->right;
			else prev->left=temp->right;
		}
	}
	else
	{
		return NOT_FOUND;
	}
}

bool BST::IsHavingAPathSumEqualsGivenNumber(TreeNode* ptr,int val,int sum)
{
	if(ptr==NULL)return false;
	if(ptr->left==NULL && ptr->right==NULL)
	{
		if(sum+ptr->data==val)return true;
		return false;
	}
	return IsHavingAPathSumEqualsGivenNumber(ptr->left,val,sum+ptr->data) || IsHavingAPathSumEqualsGivenNumber(ptr->right,val,sum+ptr->data);
}


//return length of longest path and returns diameter of tree in parameter passed.
int BST::Diameter(TreeNode* ptr,int* diameter)
{
	static int diam=0;
	int leftLen,rightLen,currDiam;
	if(ptr==NULL)return 0;
	leftLen=Diameter(ptr->left,diameter);
	rightLen=Diameter(ptr->right,diameter);
	currDiam=leftLen+rightLen+1;
	if(currDiam>diam)diam=currDiam;
	if(diameter!=NULL)*diameter=diam;
	if(leftLen>rightLen)return leftLen+1;
	else return rightLen+1;
}

void BST::PrintLeftView(TreeNode* ptr,int height)
{
	static int printHeight=0;
	if(ptr!=NULL)
	{
		if(height==printHeight)
		{
			cout<<ptr->data<<"  ";
			printHeight++;
		}
		PrintLeftView(ptr->left,height+1);
		PrintLeftView(ptr->right,height+1);
	}
}

void BST::PrintRightView(TreeNode* ptr,int height)
{
	static int printHeight=0;
	if(ptr!=NULL)
	{
		if(height==printHeight)
		{
			cout<<ptr->data<<"  ";
			printHeight++;
		}
		PrintRightView(ptr->right,height+1);
		PrintRightView(ptr->left,height+1);
	}
}

void BST::PrintSpiralInLinearTime()
{
	int currHeight=0;
	queue<NodeWithHeight> q;
	stack<int> s;
	NodeWithHeight temp,p;
	p.height=0;
	p.node=root;
	q.push(p);
	while(!q.empty())
	{
		
		p=q.front();
		//cout<<"Value is : "<<p.node->data<<endl;
		q.pop();
		temp.height=p.height+1;
		if(p.node->left!=NULL)
		{
			temp.node=p.node->left;
			q.push(temp);
		}
		
		if(p.node->right!=NULL)
		{
			temp.node=p.node->right;
			q.push(temp);
		}
		
		if(currHeight<p.height)
		{
			while(!s.empty())
			{
				cout<<s.top()<<"  ";
				s.pop();
			}
			currHeight=p.height;
		}
		
		if(currHeight%2)s.push(p.node->data);
		else cout<<p.node->data<<"  ";
	}
	while(!s.empty())
	{
		cout<<s.top()<<"  ";
		s.pop();
	}
}
	
void BST::PrintSpiralInQuadTime()
{
	int i;
	int height=Diameter(root,NULL);
	bool isEven=true;
	for(i=0;i<height;i++)
	{
		PrintSpiralUtility(root,i,isEven);
		isEven=!isEven;
	}
}

void BST::PrintSpiralUtility(TreeNode* ptr,int label,bool isEven,int height)
{
	if(ptr==NULL)return;
	if(height==label)cout<<ptr->data<<"  ";
	if(isEven)
	{
		PrintSpiralUtility(ptr->left,label,isEven,height+1);
		PrintSpiralUtility(ptr->right,label,isEven,height+1);
	}
	else
	{
		PrintSpiralUtility(ptr->right,label,isEven,height+1);
		PrintSpiralUtility(ptr->left,label,isEven,height+1);
	}
}

bool BST::DeletePathWithWeightNotEqualsGivenVal(TreeNode* ptr,int val,int sum)
{
	if(ptr==NULL)return false;
	else if(ptr->left==NULL && ptr->right==NULL)
	{
		if(sum+ptr->data==val)return true;
		else return false;
	}
	else
	{
		TreeNode* temp;
		bool bLeft=DeletePathWithWeightNotEqualsGivenVal(ptr->left,val,sum+ptr->data);
		bool bRight=DeletePathWithWeightNotEqualsGivenVal(ptr->right,val,sum+ptr->data);
		if(!bLeft)
		{
			temp=ptr->left;
			ptr->left=NULL;
			delete temp;
		}
		if(!bRight)
		{
			temp=ptr->right;
			ptr->right=NULL;
			delete temp;
		}
		return bLeft || bRight;
	}
}

bool BST::DeleteNonHeavyPaths(TreeNode* ptr,int val,int sum)
{
	if(ptr==NULL)return false;
	else if(sum+ptr->data>=val)return true;
	else
	{
		TreeNode* temp;
		bool bLeft=DeleteNonHeavyPaths(ptr->left,val,sum+ptr->data);
		bool bRight=DeleteNonHeavyPaths(ptr->right,val,sum+ptr->data);
		if(!bLeft)
		{
			temp=ptr->left;
			ptr->left=NULL;
			delete temp;
		}
		if(!bRight)
		{
			temp=ptr->right;
			ptr->right=NULL;
			delete temp;
		}
		return bLeft || bRight;
	}
}

void BST::RemoveAllHalfNodes(TreeNode* ptr,TreeNode* parent)
{
	if(ptr==NULL)return;
	else
	{
		if(ptr->left!=NULL && ptr->right!=NULL)
		{
			RemoveAllHalfNodes(ptr->left,ptr);
			RemoveAllHalfNodes(ptr->right,ptr);
		}
		else if(ptr->left!=NULL)
		{
			if(parent==NULL)root=ptr->left;
			else if(ptr==parent->left) parent->left=ptr->left;
			else parent->right=ptr->left;
			RemoveAllHalfNodes(ptr->left,parent);
		}
		else if(ptr->right!=NULL)
		{
			if(parent==NULL)root=ptr->right;
			else if(ptr==parent->left)parent->left=ptr->right;
			else parent->right=ptr->right;
			RemoveAllHalfNodes(ptr->right,parent);
		}
	}
}

int BST::SumOfAllLeaves(TreeNode* ptr)
{
	if(ptr==NULL)return 0;
	else if(ptr->left==NULL && ptr->right==NULL)return ptr->data;
	return SumOfAllLeaves(ptr->left)+SumOfAllLeaves(ptr->right);
}

void BST::PrintAllRootToLeafPaths(TreeNode* ptr,int height)
{
	static vector<int> v;
	int i;
	if(ptr==NULL)return;
	
	if(v.size()<height+1) v.push_back(ptr->data);	
	else v[height]=ptr->data;

	if (ptr->left==NULL && ptr->right==NULL)
	{
		for(i=0;i<=height;i++) cout<<v[i]<<"  ";
		cout<<endl;
	}
	else
	{
		PrintAllRootToLeafPaths(ptr->left,height+1);
		PrintAllRootToLeafPaths(ptr->right,height+1);
	}
}


returnCode BST::lowestCommonAncestor(TreeNode* ptr,int val1,int val2,TreeNode** retVal)
{
	if(searchElement(val1)==SUCCESS && searchElement(val2)==SUCCESS)
	{
		bool bLesser,bGreater;
		while(ptr!=NULL)
		{
			bLesser=(val1 < ptr->data) && (val2 < ptr->data);
			bGreater=(val1 > ptr->data) && (val2 > ptr->data);
			if(bLesser)ptr=ptr->left;
			else if(bGreater)ptr=ptr->right;
			else
			{
				if(retVal!=NULL)
				{
					*retval=ptr;
				}
				break;
			 } 
		}
		return SUCCESS;
	}
	else
	{
		return NOT_FOUND;
	}
}

bool BST::isIdentical(TreeNode* ptr1, TreeNode* ptr2)
{
	if(ptr1==NULL && ptr2==NULL)return true;
	else if(ptr1!=NULL && ptr2!=NULL)
	{
		if(isIdentical(ptr1->left,ptr2->left) && isIdentical(ptr1->right,ptr2->right) && (ptr1->data==ptr2->data))
			return true;
	}
		
	return false;
}

//incomplete
bool BST::isMirror(TreeNode* ptr1, TreeNode* ptr2)
{
	if(ptr1==NULL && ptr2==NULL)return true;
	else if()
}


void BST::mirrorTree(TreeNode* ptr)
{
		if(ptr==NULL)return;
		mirrorTree(ptr->right);
		TreeNode* temp=ptr->left;
		ptr->left=ptr->right;
		ptr->right=temp;
}

int BST::treeSize(TreeNode* ptr)
{
	if(ptr==NULL)return 0;
	return treeSize(ptr->left)+treeSize(ptr->right)+1;
}

void BST::printPathsHavingSumEqualsGivenvalue(TreeNode* ptr,int val,int sum,int height)
{
	static vector<int> v;
	int i;
	if(ptr==NULL)return;
	
	if(v.size()<height+1) v.push_back(ptr->data);	
	else v[height]=ptr->data;

	if (ptr->left==NULL && ptr->right==NULL && sum+ptr->data==val)
	{
		for(i=0;i<=height;i++) cout<<v[i]<<"  ";
		cout<<endl;
	}
	else
	{
		PrintAllRootToLeafPaths(ptr->left,val,sum+ptr->data,height+1);
		PrintAllRootToLeafPaths(ptr->right,val,sum+ptr->data,height+1);
	}
}

int BST::countLeafNodes(TreeNode* ptr)
{
	if(ptr==NULL)return 0;
	else if(ptr->left==NULL && ptr->right==NULL)return 1;
	return countLeafNodes(ptr->left)+ countLeafNodes(ptr->right);
}

void BST::printBSTKeysInRange(int start,int end)
{
	while(ptr!=NULL)
	{
		if(ptr->data > end)ptr=ptr->left;
		else if(ptr->data < start)ptr=ptr->right;
	}
	if(ptr!=NULL)printBSTKeysInRangeUtil(ptr,start,end);
}

void BST::printBSTKeysInRangeUtil(TreeNode*ptr,int start,int end)
{
	if(ptr==NULL)return;
	if(ptr->data >= start)printBSTKeysInRangeUtil(ptr->left,start,end);
	cout<<ptr->data<<"  ";
	if(ptr->data <= end)printBSTKeysInRangeUtil(ptr->right,start,end);
}

void BST::levelOrderTraversal(TreeNode* ptr)
{
	int i;
	int height=Diameter(root,NULL);
	for(i=0;i<height;i++) PrintSpiralUtility(root,i,isEven);
}

void BST::levelOrderTraversalUtil(TreeNode* ptr,int label,int height)
{
	if(ptr==NULL)return;
	if(height==label)cout<<ptr->data<<"  ";
	levelOrderTraversalUtil(ptr->left,label,height+1);
	levelOrderTraversalUtil(ptr->right,label,height+1);
}

int BST::maxWidth(int* l,int* r)
{
	int left=0,right=0;
	maxWidthUtil(root,&left,&right,0);
	if(l!=NULL)*l=left;
	if(r!=NULL)*r=right;
	return left-right+1;
}

void BST::maxWidthUtil(TreeNode* ptr,int* left,int* right,int width)
{
	if(ptr==NULL)return;
	if(width < *right)*right=width;
	else if(width > *left)*left=width;
	maxWidthUtil(ptr->left,left,right,l+1,r);
	maxWidthUtil(ptr->right,left,right,l,r-1);
}


int* BST::verticalSum()
{
	int right,width;
	width=maxWidth(root,&right);
	int* arr=(int*)malloc(sizeof(int)*width); //vector with default value 0;
	memset(arr,sizeof(int)*width,0);
	maxWidthUtil(root,arr,0);
	return arr;
}

void BST::verticalSumUtil(TreeNode* ptr,int* arr,int index)
{
	if(ptr==NULL)return;
	arr[index]=ptr->data;
	verticalSumUtil(ptr->left,arr,index-1);
	verticalSumUtil(ptr->right,arr,index+1);
}


//this one is for binary tree as well.mostly valid for binary tree.
bool isFollowingChildrenSumProperty(TreeNode* ptr)
{
	if(ptr==NULL)return true;
	bool left=isFollowingChildrenSumProperty(ptr->left);
	bool right=isFollowingChildrenSumProperty(ptr->right);
	int sum=0;
	if(ptr->left!=NULL)sum+=ptr->left->data;
	if(ptr->right!=NULL)sum+=ptr->right->data;
	return left && right && (ptr->data==sum);
}


//ikmprovement needed;
bool BST::isSumTreeUtil(TreeNode* ptr,int sum)
{
	if(ptr==NULL)return true;
	else if(ptr->left==NULL && ptr->right==NULL)
	{
		sum=ptr->data;
		return true;
	}
	bool bLeft=isSumTreeUtil(ptr->left,sum);
	bool bRight=isSumTreeUtil();
	
}

bool BST::isEachInternalNodeHaveExactlyOneChild(TreeNode* ptr)
{
	if(ptr==NULL || (ptr->next==NULL && ptr->right==NULL))return true;
	bool bLeft=isEachInternalNodeHaveExactlyOneChild(ptr->left);
	bool bRight=isEachInternalNodeHaveExactlyOneChild(ptr->right);
	if(bLeft && bRight && ptr->left!=NULL && ptr->right!=NULL)return false;
	return true;
}


//incomplete
bool BST::isSubTreeOfAnother(TreeNode *ptr1,TreeNode* ptr2)
{
	return isSubTreeOfSecond(ptr1,ptr2) || isSubTreeOfSecond(ptr2,ptr1); 
}

bool BST::isSubTreeOfSecond(TreeNode* child,TreeNode* parent)
{
	if(child==NULL && parent==NULL)return true;
	while(parent!=NULL)
	{
		if(child->data > parent->data)parent=parent->right;
		else if(child->data < parent->data)	parent=parent->left;
		else break;
	}
	
	if(parent!=NULL)
	{
		if()
	}
}


void BST::printBoundry(TreeNode* ptr,int h)
{
	static int lHeight=-1,rHeight=0;
	if(ptr==NULL)return;
	if(lHeight>h)
	{
		cout<<ptr->data<<"  ";
		height=h;
	}
	printBoundry(ptr->left,h-1);
	printBoundry(ptr->right,h+1);
}











