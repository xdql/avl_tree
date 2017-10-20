#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int v, height;//v为节点的权值，height为当前子树的高度
	node *lchild, *rchild;//定义左右孩子指针
}*root;
//生成一个新的节点，v为节点的权值
node* newNode(int v)
{
	node* Node = new node;
	Node->v = v;//权值
	Node->height = 1;//高度为1
	Node->lchild = Node->rchild = NULL;//左右子树为空
	return Node;//返回相应的地址
}
//获取以root为根节点的子树的当前height
int getHeight(node* root)
{
	if (root == NULL)
		return 0;//空节点高度为0
	return root->height;
}
//更新节点root的高度
void updateHeight(node* root)
{
	//max(左孩子节点的height，右孩子节点的height)+1
	root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}
//计算节点root的平衡因子
int getBalanceFactor(node* root)
{
	//左子树高度减去右子树高度
	return getHeight(root->lchild) - getHeight(root->rchild);
}
//左旋 (Left Rotation)
void L(node* &root)
{
	node* temp = root->rchild;//root指向节点A,temp指向节点B
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root);//更新节点B的高度
	updateHeight(temp);//更新节点A的高度
	root = temp;
}
//右旋
void R(node* &root)
{
	node* temp = root->lchild;//root指向节点B，temp指向节点A
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);//更新B高度
	updateHeight(temp);//更新A高度
	root = temp;
}
//插入权值为v的节点
void insert(node* &root, int v)
{
	if (root == NULL)//若到达空节点的位置
	{
		root = newNode(v);
		return;
	}
	if (v < root->v)//v比根节点权值小
	{
		insert(root->lchild, v);//往左子树里插
		updateHeight(root);
		return;
	}
	if (v > root->v)//v比根节点权值大
	{
		insert(root->rchild, v);//往右子树里插
		updateHeight(root);//更新树高
	//	return;
		if (getBalanceFactor (root)== 2)
		{
			if (getBalanceFactor(root->rchild)==1)//LL型
			{
				R(root);
			}
			else if (getBalanceFactor(root->lchild )== -1)//LR型
			{
				L(root->lchild);
				R(root);
			}
		}
		else
		{
			//v比根节点权值大
			insert(root->rchild, v);
			updateHeight(root);
			if (getBalanceFactor(root) == 2)
			{
				if (getBalanceFactor(root->rchild)==-1)//RR型
				{
					L(root);
				}
				else if(getBalanceFactor(root->rchild)==1)
				{	
					R(root->rchild);
					L(root);
				}
			}
		}
	}

}
node* Create(int data[], int n)
{
	node* root = NULL;
	for (int i = 0; i < n; i++)
	{
		insert(root,data[i]);
	}
	return root;
}
int main()
{
	int n, v;
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&v);
		insert(root,v);
	}
	printf("%d",root->v);
	system("pause");
	return 0;
}
