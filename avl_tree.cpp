#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int v, height;//vΪ�ڵ��Ȩֵ��heightΪ��ǰ�����ĸ߶�
	node *lchild, *rchild;//�������Һ���ָ��
}*root;
//����һ���µĽڵ㣬vΪ�ڵ��Ȩֵ
node* newNode(int v)
{
	node* Node = new node;
	Node->v = v;//Ȩֵ
	Node->height = 1;//�߶�Ϊ1
	Node->lchild = Node->rchild = NULL;//��������Ϊ��
	return Node;//������Ӧ�ĵ�ַ
}
//��ȡ��rootΪ���ڵ�������ĵ�ǰheight
int getHeight(node* root)
{
	if (root == NULL)
		return 0;//�սڵ�߶�Ϊ0
	return root->height;
}
//���½ڵ�root�ĸ߶�
void updateHeight(node* root)
{
	//max(���ӽڵ��height���Һ��ӽڵ��height)+1
	root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}
//����ڵ�root��ƽ������
int getBalanceFactor(node* root)
{
	//�������߶ȼ�ȥ�������߶�
	return getHeight(root->lchild) - getHeight(root->rchild);
}
//���� (Left Rotation)
void L(node* &root)
{
	node* temp = root->rchild;//rootָ��ڵ�A,tempָ��ڵ�B
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root);//���½ڵ�B�ĸ߶�
	updateHeight(temp);//���½ڵ�A�ĸ߶�
	root = temp;
}
//����
void R(node* &root)
{
	node* temp = root->lchild;//rootָ��ڵ�B��tempָ��ڵ�A
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);//����B�߶�
	updateHeight(temp);//����A�߶�
	root = temp;
}
//����ȨֵΪv�Ľڵ�
void insert(node* &root, int v)
{
	if (root == NULL)//������սڵ��λ��
	{
		root = newNode(v);
		return;
	}
	if (v < root->v)//v�ȸ��ڵ�ȨֵС
	{
		insert(root->lchild, v);//�����������
		updateHeight(root);
		return;
	}
	if (v > root->v)//v�ȸ��ڵ�Ȩֵ��
	{
		insert(root->rchild, v);//�����������
		updateHeight(root);//��������
	//	return;
		if (getBalanceFactor (root)== 2)
		{
			if (getBalanceFactor(root->rchild)==1)//LL��
			{
				R(root);
			}
			else if (getBalanceFactor(root->lchild )== -1)//LR��
			{
				L(root->lchild);
				R(root);
			}
		}
		else
		{
			//v�ȸ��ڵ�Ȩֵ��
			insert(root->rchild, v);
			updateHeight(root);
			if (getBalanceFactor(root) == 2)
			{
				if (getBalanceFactor(root->rchild)==-1)//RR��
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
