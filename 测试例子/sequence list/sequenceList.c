/*
  ������˳��洢�����Ա��ֱ�����һЩ�������ݣ�ÿ��˳����д�ŵ����ݶ��Ǵ�С�������С�дһ�����򣬽�����˳���ϲ����ϲ�������һ���µ�˳�����Ҳ�Ǵ�С��������
�����ɵ�˳���Ӧ�ô�����ϵͳ�Ķ��ڴ��ϣ�Ҳ���Ƕ�̬�������˳��������±���ܸ��ݱ�1�ͱ�2�ĳ��ȶ�̬����
*/
#include "stdio.h"
typedef int ElemType;
typedef struct{
	int *elem;
	int length;
	int listsize;
}Sqlist;
void initSqlist(Sqlist *L,int size)
{
	L->elem=(int*)malloc(size*(sizeof(ElemType)));
	if(!L->elem)
		exit(0);
	L->length=0;
	L->listsize=size;
}
void InsertElem(Sqlist *L,int i,ElemType item)
{//��˳���L�е�i��λ���ϲ���Ԫ��item
	ElemType *base,*insertPtr,*p;
	if(i<1||i>L->length+1) //����λ�÷Ƿ�
		exit(0);
	if(L->length>=L->listsize)//˳���ռ䲻�㣬׷���ڴ�
	{
		base=(ElemType*)realloc(L->elem,(L->listsize+10)*sizeof(ElemType));
		L->elem=base;
		L->listsize=L->listsize+100;
	}
	insertPtr=&(L->elem[i-1]);//ָ��insertPtrָ�����λ��
	for(p=&(L->elem[L->length-1]);p>=insertPtr;p--)
	{
		*(p+1)=*p;
	}
	*insertPtr=item;
	L->length++;
}
void DestroySqList(Sqlist *list)
{//����˳���list���ͷ���ռ�еĿռ�
	int *p=list->elem;
	free(p);
	printf("come here....\n");
	list->elem=NULL;
	list->length=0;
	list->listsize=0;
}
Sqlist MergeList(Sqlist list1,Sqlist list2)
{
	int *p1,*p2,*p3,*p1_last,*p2_last;
	Sqlist list3;
	p1=list1.elem;
	p2=list2.elem;
	initSqlist(&list3,list1.length+list2.length);
	p3=list3.elem;
	p1_last=list1.elem+list1.length-1;
	p2_last=list2.elem+list2.length-1;
	while(p1<=p1_last&&p2<=p2_last)
	{
		if(*p1<=*p2)
		{
			*p3=*p1;
			p1++;
			p3++;
		}
		else
		{
			*p3=*p2;
			p2++;
			p3++;
		}
		list3.length++;
	}
	if(p1<=p1_last)
	{
		while(p1<=p1_last)
		{
			*p3=*p1;
			p1++;
			p3++;
			list3.length++;
		}
	}
	else
	{
		while(p2<=p2_last)
		{
			*p3=*p2;
			p2++;
			p3++;
			list3.length++;
		}
	}
	return list3;
}
main()
{
	Sqlist list1,list2,list3;
	int n,i,e;
	int flag=0;
	printf("please input the length of list1\n");
	scanf("%d",&n);
	initSqlist(&list1,n);
	printf("please input list_1 from little to large\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&e);
		if(e<0)
		{
			flag=1;
		}
		InsertElem(&list1,i,e);
	}
	printf("please input the length of list2\n");
	scanf("%d",&n);
	initSqlist(&list2,n);
	printf("please input list_2 from little to large\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&e);
		if(e<0)
		{
			flag=1;
		}
		InsertElem(&list2,i,e);
	}
	if(flag==0)
	{
		list3=MergeList(list1,list2);
		printf("the content of list3 is\n");
		for(i=0;i<list3.length;i++)
		{
			printf("%d ",list3.elem[i]);
		}
		DestroySqList(&list1);
     	DestroySqList(&list2);
		DestroySqList(&list3);
	}
	else
	{
		printf("the list has invalid input.\n");
	}
}
