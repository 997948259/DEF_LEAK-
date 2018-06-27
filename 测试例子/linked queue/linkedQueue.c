//LinkQueue.c  
  
//��ͷ�ڵ����ʽ����  
#include <stdio.h>  
#include <stdlib.h>  
#define    OK 1  
#define ERROR 0  
#define OVERFLOW -2  
typedef char elemType;//Ԫ������  
  
typedef struct _QNode  
{  
elemType data;  
struct _QNode *next;  
}QNode;//�ڵ�����  
  
typedef struct  
{  
QNode *front;//  
QNode *rear;  
}LinkQueue;//��������  
  
//��ʼ������  
int InitQueue(LinkQueue *q)  
{  
q->front=q->rear=(QNode *)malloc(sizeof(QNode)); 
printf("malloc...\n");  
if(!q->front) exit(OVERFLOW);  
q->front->next=NULL;  
return OK;  
}  
//���ٶ���  
int DestroyQueue(LinkQueue *q)  
{  
while(q->front)  
{  
q->rear=q->front->next;  
free(q->front);  
q->front=q->rear;  
}  
return OK;  
}  
//��β����Ԫ��e  
int EnQueue(LinkQueue *q,elemType e)  
{  
QNode *p=(QNode *)malloc(sizeof(QNode));  
printf("malloc...\n"); 
if(!p) exit(OVERFLOW);  
p->data=e;  
p->next=NULL;  
q->rear->next=p;  
q->rear=p;  
return OK;  
}  
//ɾ����ͷԪ�أ�����ӡ��ֵ  
int DeQueue(LinkQueue *q)  
{  
QNode *p=q->front->next;//��Ϊ��ͷ�ڵ㣬���Զ�ͷ��ͷ�ڵ�ĺ�һ��Ԫ��  
if(q->front==q->rear) return ERROR;  
//printf("��ɾ����ͷԪ��%c\n",p->data);  
q->front->next=p->next;  
if(q->rear==p) q->rear=q->front;  
free(p);
printf("free...\n");   
return OK;  
}  
//��������  
void TraverseQueue(LinkQueue *q)  
{  
QNode *p=q->front->next;  
if(q->front==q->rear)  
printf("����Ϊ��\n");  
else  
{  
printf("�����е�Ԫ��Ϊ:\n");  
while(p!=q->rear)  
{  
printf(" %c",p->data);  
p=p->next;  
}  
printf(" %c",q->rear->data);  
printf("\n");  
}  
}  
  
void main()  
{  
	int n;
LinkQueue *q=(LinkQueue *)malloc(sizeof(LinkQueue)); 
printf("malloc...\n"); 
InitQueue(q);  
TraverseQueue(q);  
//printf("��β����Ԫ��.....\n");  
EnQueue(q,'a');  
EnQueue(q,'b');  
EnQueue(q,'c');  
EnQueue(q,'d'); 
EnQueue(q,'e'); 
EnQueue(q,'f'); 
EnQueue(q,'g'); 
EnQueue(q,'h'); 
EnQueue(q,'i'); 
EnQueue(q,'j'); 
 
TraverseQueue(q);  
//printf("ɾ������Ԫ��...\n"); 
printf("please input n:(1-10)\n");
scanf("%d",&n);
if (n<=10)
{
	while (n>0)
	{
		DeQueue(q); 
		n--;
	}
}

TraverseQueue(q);  
} 