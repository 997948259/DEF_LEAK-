#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int data_type;

typedef struct avl
{
	data_type data;
	int bf;//AVL��ƽ�����ӣ�Banlance Factor��
	struct avl *lchild,*rchild;
}AVLNode,*AVL;

void AdjustLL(AVL *T)//�������
{
	AVL temp = (*T)->lchild;
	(*T)->lchild = temp->rchild;
	temp->rchild = (*T);
	*T = temp;
}

void AdjustRR(AVL *T)//���ҵ���   
{
	AVL temp = (*T)->rchild;
	(*T)->rchild = temp->lchild;
	temp->lchild = (*T);
	(*T) = temp;
}

void AdjustRL(AVL *T)//�������  
{
	AVL p1,p2;
	p1 = (*T)->rchild;
	p2 = p1->lchild;
	(*T)->rchild = p2->lchild;
	p1->lchild = p2->rchild;
	p2->lchild = (*T);
	p2->rchild = p1;
	(*T) = p2;
}

void AdjustLR(AVL *T)//���ҵ���
{
	AVL p1,p2;
	p1 = (*T)->lchild;
	p2 = p1->rchild;
	p1->rchild = p2->lchild;//p2��������p1���Һ���
	(*T)->lchild = p2->rchild;//p2�Һ�������(*T)������
	p2->lchild = p1;
	p2->rchild = (*T);
	(*T) = p2;
}

void LeftBanlance(AVL *T)// ��ƽ�⴦��LL LR ���
{
	AVL lc = (*T)->lchild,rc;
	switch(lc->bf)
	{
		case 1:	//LL���
			(*T)->bf = 0;
			lc->bf = 0;
			AdjustLL(T);
			break;
		case 0:				//ɾ��ʱ��Ҫ�����벻��Ҫ
			(*T)->bf = 1;
			lc->bf = -1;
			AdjustLL(T);
			break;
		case -1: //LR���
			rc = lc->rchild;
			switch(rc->bf)
			{
				case 1:
					(*T)->bf = -1;
					lc->bf = 0;
					break;
				case 0:
					(*T)->bf = 0;
					lc->bf = 0;
					break;
				case -1:
					(*T)->bf = 0;
					lc->bf = 1;
					break;
			}
			rc->bf = 0;
			AdjustLR(T);
			break;
	}
}

void RightBanlance(AVL *T)//��ƽ�⴦��RR RL���
{
	AVL rc = (*T)->rchild,lc;
	switch(rc->bf)
	{
		case -1:
			(*T)->bf  = 0;
			rc->bf = 0;
			AdjustRR(T);
			break;
		case 0:			//ɾ��ʱ��Ҫ�����벻��Ҫ
			(*T)->bf = -1;
			rc->bf = 1;
			AdjustRR(T);
			break;
		case 1:
			lc = rc->lchild;
			switch(lc->bf)
			{
				case 1:
					(*T)->bf = 0;
					rc->bf = -1;
					break;
				case 0:
					(*T)->bf = 0;
					rc->bf = 0;
					break;
				case -1:
					(*T)->bf = 1;
					rc->bf = 0;
					break;
			}
			lc->bf = 0;
			AdjustRL(T);
			break;
	}
}

int Insert(AVL *T,data_type data,int *taller)//����
{
	AVL newnode,p;
	newnode = (AVL)malloc(sizeof(AVLNode));
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	newnode->data = data;
	newnode->bf = 0;
	if((*T) == NULL)	//����ɹ����������
	{
		(*T) = newnode;
		*taller = 1;
	}
	else
	{
		if(data == (*T)->data)//�����Ѵ��ڣ�������
		{
			*taller = 0;
			return 0;
		}
		else if(data < (*T)->data)//�������в���
		{
			if(Insert(&(*T)->lchild,data,taller) == 0)//����ʧ��
			{
				return 0;
			}
			if((*taller) == 1)		//����ɹ���������ߣ���bf����Ӧ�޸��Լ�ƽ�����
			{
				switch((*T)->bf)
				{
					case 1:
						LeftBanlance(T);	//������ƽ�⣬�������ƽ�⴦���꣬�����߶Ȳ���
						*taller = 0;
						break;
					case 0:
						(*T)->bf = 1;
						*taller = 1;
						break;
					case -1:
						(*T)->bf = 0;
						*taller = 0;
						break;
				}
			}
		}
		else//�������в���
		{
			if(Insert(&(*T)->rchild,data,taller) == 0)//����ʧ��
			{
				return 0;
			}
			if((*taller) == 1)
			{
				switch((*T)->bf)
				{
					case 1:
						(*T)->bf = 0;
						*taller = 0;
						break;
					case 0:
						(*T)->bf = -1;
						*taller = 1;
						break;
					case -1:
						RightBanlance(T);
						*taller = 0;
						break;
				}
			}
		}
	}
	return 1;
}

/*
�����ڣ���ɾ��,���Ҹ߶Ƚ��ͣ��ڵݹ����ʱ�Ը�Ԫ��bf����Ӧ�޸�
��С�ڣ�����ߵݹ飬�����ڣ����ұߵݹ�
ֻ�е�ɾ���ɹ��������߶Ƚ���ʱ����bf��Ӧ�޸ģ��������������*/

int Delete(AVL *T,data_type data,int *shorter)//ɾ��
{
	if((*T) == NULL)
	{
		return 0;
	}
	else if(data == (*T)->data)		//ɾ��  �˴�ɾ���㷨ԭ��ͬ����������
	{
		AVL temp = (*T);
		if((*T)->lchild == NULL)
		{
			(*T) = (*T)->rchild;
			free(temp);
			*shorter = 1;
		}
		else if((*T)->rchild == NULL)
		{
			(*T) = (*T)->lchild;
			free(temp);
			*shorter = 1;
		}
		else
		{
			AVL p = (*T)->lchild;
			while(p->rchild)
			{
				p = p->rchild;
			}
			temp->data = p->data;
			Delete(&(temp->lchild),p->data,shorter);
		}
	}
	else if(data < (*T)->data)		//�������м�������
	{
		if(!Delete(&((*T)->lchild),data,shorter))//ɾ��ʧ��ֱ��return 0
		{
			return 0;
		}
		if(*shorter)	//�������н��ɾ���ɹ�,���������߶Ƚ���
		{
			switch((*T)->bf)
			{
				case 1:
					(*T)->bf = 0;
					*shorter = 1;
					break;
				case 0:				//�����߶Ȳ����͵��������:�����Ҷ��н�㣬ɾ��һ����Ӱ�������߶�
					(*T)->bf = -1;
					*shorter = 0;
					break;
				case -1:
					if((*T)->rchild->bf == 0)//ɾ��ʱ������������Һ��ӽ��bfΪ0�������߶Ȳ���
					{
						*shorter = 0;
					}
					else
					{
						*shorter = 1;
					}
					RightBanlance(T);		//������ƽ��
					break;
			}
		}
	}
	else				//�������м�������
	{
		if(!Delete(&(*T)->rchild,data,shorter))
		{
			return 0;
		}
		if(*shorter)	
		{
			switch((*T)->bf)
			{
				case 1:
					if((*T)->lchild->bf == 0)
					{
						*shorter = 0;
					}
					else
					{
						*shorter = 1;
					}
					LeftBanlance(T);
					break;
				case 0:
					(*T)->bf = 1;
					*shorter = 0;
					break;
				case -1:
					(*T)->bf = 0;
					*shorter = 1;
					break;
			}
		}
	}
	return 1;
}

int GetDeepth(AVL T)//�������
{
	int max,hl,hr;
	if(T == NULL)
	{
		return 0;
	}
	else
	{
		hl = GetDeepth(T->lchild);
		hr = GetDeepth(T->rchild);
		return max = (hl>hr?hl:hr)+1;
	}
}

void DispTree(AVL T,int deepth,char ch) //���������ʾ������
{
	int i;
    if(T)
    {
        for(i = 0;i < deepth + 1;i++)
        {
            printf("---");
        }
        printf("+%d(%c)(%d)\n",T->data,ch,T->bf);
        DispTree(T->lchild,--deepth,'L');
        DispTree(T->rchild,deepth,'R');
    }
}

void Inorder(AVL T)//�������
{
	if(T)
	{
		Inorder(T->lchild);
		printf("%d ",T->data);
		Inorder(T->rchild);
	}
}

void CreateAVL(AVL *T)//���������������ò����㷨����
{
	int deepth,taller;
	data_type data;
	char ch;
	printf("������Ҫ�����Ķ���������������(����֮���ÿո����,������ϰ��س�)��");
	do
	{
		taller = 0;
		scanf("%d",&data);
		ch = getchar();
		Insert(T,data,&taller);
		deepth = GetDeepth(*T);
		DispTree(*T,deepth,'R');
		puts("");
	}
	while (ch != 10);
}

int main()
{
	int deepth,taller,select,shorter;
	data_type data;
	AVL T;
	T = NULL;

	//CreateAVL(&T);
	//deepth = GetDeepth(T);
	//Inorder(T);

	//�����һ������
	taller = 0;
	printf("������Ҫ��������ݣ�");
	scanf("%d",&data);
	Insert(&T,data,&taller);
	deepth = GetDeepth(T);
	DispTree(T,deepth,'R');
	puts("");
	Inorder(T);

	//����ڶ�������
	taller = 0;
	printf("������Ҫ��������ݣ�");
	scanf("%d",&data);
	Insert(&T,data,&taller);
	deepth = GetDeepth(T);
	DispTree(T,deepth,'R');
	puts("");
	Inorder(T);

	//�������������
	taller = 0;
	printf("������Ҫ��������ݣ�");
	scanf("%d",&data);
	Insert(&T,data,&taller);
	deepth = GetDeepth(T);
	DispTree(T,deepth,'R');
	puts("");
	Inorder(T);

	return 0;
}

/*13 87 39 90 45 52 46 78 28 71 76 29 56 19 83 92 48 81 95 99 20*/