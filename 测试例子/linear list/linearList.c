#include <stdio.h>
#include <stdlib.h>
typedef int elemType;
/************************************************************************/
/*                �����ǹ������Ա�˳��洢������16���㷨      */
/************************************************************************/
struct List{
    elemType *list;
    int size;
    int maxSize;
};
void againMalloc(struct List *L)
{   
    /* �ռ���չΪԭ����2��������pָ����ָ��ԭ���ݱ��Զ�������p��ָ��Ĵ洢�ռ� */
    elemType *p = realloc(L->list, (2+ L->maxSize) * sizeof(elemType));
	printf("malloc two ..\n");
    if(!p){    /* ����ʧ�����˳����� */
        printf("�洢�ռ����ʧ�ܣ� ");
        exit(1);
    }
    L->list = p;    /* ʹlistָ�������Ա�ռ� */
    L->maxSize = 2 + L->maxSize;    /* �����Ա�ռ��С�޸�Ϊ�µĳ��� */
}
/* 1.��ʼ�����Ա�L�������ж�̬�洢�ռ���䲢��LΪһ���ձ� */
void initList(struct List *L, int ms)
{
    /* ���ms�Ƿ���Ч������Ч�����˳����� */
    if(ms <= 0){
        printf("MaxSize�Ƿ��� ");
        exit(1);    /* ִ�д˺�����ֹ�������У��˺�����stdlib.h���ж��� */
    }
    L->maxSize = ms;    /* �������Ա�ռ��СΪms */
    L->size = 0;
    L->list = malloc(ms * sizeof(elemType));
	printf("malloc  ..\n");
    if(!L->list){
        printf("�ռ����ʧ�ܣ� ");
        exit(1);
    }
    return;
}
/* 2.������Ա�L�е�����Ԫ�أ��ͷŴ洢�ռ䣬ʹ֮��Ϊһ���ձ� */
void clearList(struct List *L)
{
    if(L->list != NULL){
        free(L->list);
		printf("free  ..\n");
        L->list = 0;
        L->size = L->maxSize = 0;
    }
    return;
}
/* 3.�������Ա�L��ǰ�ĳ��ȣ���LΪ���򷵻أ� */
int sizeList(struct List *L)
{
    return L->size;
}
/* 4.�ж����Ա�L�Ƿ�Ϊ�գ���Ϊ���򷵻�1, ���򷵻�0 */
int emptyList(struct List *L)
{
    if(L->size ==0){
        return 1;
    }
    else{
        return 0;
    }
}
/* 5.�������Ա�L�е�pos��Ԫ�ص�ֵ����pos������Χ����ֹͣ�������� */
elemType getElem(struct List *L, int pos)
{
    if(pos < 1 ||pos > L->size){    /* ��posԽ�����˳����� */
        printf("Ԫ�����Խ�磡 ");
        exit(1);
    }
    return L->list[pos - 1];    /* �������Ա������Ϊposֵ��Ԫ��ֵ */
}
/* 6.˳��ɨ�裨��������������Ա�L�е�ÿ��Ԫ�� */
void traverseList(struct List *L)
{
    int i;
    for(i = 0; i < L->size; i++){
        printf("%d ", L ->list[i]);
    }
    printf("\n");
    return;
}
/* 7.�����Ա�L�в���ֵ��x��ȵ�Ԫ�أ������ҳɹ��򷵻���λ�ã����򷵻�-1 */
int findList(struct List *L, elemType x)
{
    int i;
    for(i = 0; i < L->size; i++){
        if(L->list[i] == x){
            return i;
        }
    }
    return -1;
}
/* 8.�����Ա�L�е�pos��Ԫ�ص�ֵ�޸�Ϊx��ֵ�����޸ĳɹ�����1�����򷵻�0 */
int updatePosList(struct List *L, int pos, elemType x)
{
    if(pos < 1 ||  pos > L->size){    /* ��posԽ�����޸�ʧ�� */
        return 0;
    }
    L->list[pos - 1] = x;
    return 1;
}
/* 9.�����Ա�L�ı�ͷ����Ԫ��x */
void inserFirstList(struct List *L, elemType x)
{
    int i;
    if(L->size == L->maxSize){
        againMalloc(L);
    }
    for(i = L->size - 1; i >= 0; i--){
        L->list[i + 1] = L ->list[i];
    }
    L->list[0] = x;
    L->size ++;
    return;
}
/* 10.�����Ա�L�ı�β����Ԫ��x */
void insertLastList(struct List *L, elemType x)
{
    if(L->size == L ->maxSize){    /* ���·������Ĵ洢�ռ� */
        againMalloc(L);
    }
    L->list[L->size] = x;    /* ��x���뵽��β */
    L->size++;    /* ���Ա�ĳ������ӣ� */
    return;
}
/* 11.�����Ա�L�е�pos��Ԫ��λ�ò���Ԫ��x��������ɹ����أ������򷵻أ� */
int insertPosList(struct List *L, int pos, elemType x)
{
    int i;
    if(pos < 1 || pos > L->size + 1){    /* ��posԽ�������ʧ�� */
        return 0;
    }
    if(L->size == L->maxSize){    /* ���·������Ĵ洢�ռ� */
        againMalloc(L);
    }
	
    for(i = L->size - 1; i >= pos - 1; i--){
        L->list[i + 1] = L->list[i];
    }
    L->list[pos - 1] = x;
    L->size++;
    return 1;
}
/* 12.���������Ա�L�в���Ԫ��x,��ʹ�ò������Ȼ����*/
void insertOrderList(struct List *L, elemType x)
{
    int i, j;
    /* ������ռ����������·������Ĵ洢�ռ� */
    if(L->size == L->maxSize){
        againMalloc(L);
    }
    /* ˳����ҳ�x�Ĳ���λ�� */
    for(i = 0; i < L->size; i++){
        if(x < L->list[i]){
            break;
        }
    }
    /* �ӱ�β���±�iԪ�����κ���һ��λ�ã� ��i��λ�ÿճ��� */
    for(j = L->size - 1; j >= i; j--)
        L->list[j+1] = L->list[j];
    /* ��xֵ�����±�Ϊi��Ԫ�� */   
    L->list[i] = x;
    /* ���Ա�������1 */
    L->size++;
    return;
}
/* 13.�����Ա�L��ɾ����ͷԪ�ز�����������ɾ��ʧ����ֹͣ�������� */
elemType deleteFirstList(struct List *L)
{
    elemType temp;
    int i;
    if(L ->size == 0){
        printf("���Ա�Ϊ�գ����ܽ���ɾ�������� ");
        exit(1);
    }
    temp = L->list[0];
    for(i = 1; i < L->size; i++)
        L->list[i-1] = L->list[i];
    L->size--;
    return temp;
}
/* 14.�����Ա�L��ɾ����βԪ�ز�����������ɾ��ʧ����ֹͣ�������� */
elemType deleteLastList(struct List *L)
{
    if(L ->size == 0){
        printf("���Ա�Ϊ�գ����ܽ���ɾ�������� ");
        exit(1);
    }
    L->size--;
    return L ->list[L->size];        /* ����ԭ����βԪ�ص�ֵ */
}
/* 15.�����Ա�L��ɾ����pos��Ԫ�ز�����������ɾ��ʧ����ֹͣ�������� */
elemType deletePosList(struct List *L, int pos)
{
    elemType temp;
    int i;
    if(pos < 1 || pos > L->size){        /* posԽ����ɾ��ʧ�� */
        printf("posֵԽ�磬���ܽ���ɾ�������� ");
        exit(1);
    }
    temp = L->list[pos-1];
    for(i = pos; i < L->size; i++)
        L->list[i-1] = L->list[i];
    L->size--;
    return temp;
}
/* 16.�����Ա�L��ɾ��ֵΪx�ĵ�һ��Ԫ�أ����ɹ�����1��ʧ�ܷ���0 */
int deleteValueList(struct List *L, elemType x)
{
    int i, j;
    /* �����Ա���˳����ҳ�ֵΪx�ĵ�һ��Ԫ�� */
    for(i = 0; i < L->size; i++){
        if(L->list[i] == x){   
            break;
        }
    }
    /* ������ʧ�ܣ�����������ֵΪx��Ԫ�أ�����0 */
    if(i == L->size){
        return 0;
    }
    /* ɾ��ֵΪx��Ԫ��L->list[i] */
    for(j = i + 1; j < L->size; j++){
        L->list[j-1] = L->list[j];
    }
    L->size--;
    return 1;
}
void main()
{
    int a[5];
    int i,flag;
    struct List L;
    initList(&L, 3);
    for(i = 0; i < 5; i++){
		scanf("%d",&a[i]);
        insertLastList(&L, a[i]);
    }
	scanf("%d",&flag);  //flag can be 1,2,3,4 
	if(flag==1)
    {
		insertPosList(&L, 5, 48); 	
	}
	if(flag==2)
    {
		insertPosList(&L, 5, 48); 	
		insertPosList(&L, 3, 64);
	}
	if(flag==3)
    {
		insertPosList(&L, 5, 48); 	
		insertPosList(&L, 3, 64);
		insertPosList(&L, 1, 34);
	}
	if(flag==4)
    {
		insertPosList(&L, 5, 48); 	
		insertPosList(&L, 3, 64);
		insertPosList(&L, 1, 34);
		insertPosList(&L, 6, 45);
	}
//	printf("size:%d\n",sizeList(&L));
    printf("%d \n", getElem(&L, 1));
    traverseList(&L);
    printf("%d \n", findList(&L, 10));
    updatePosList(&L, 3, 20);
    printf("%d \n", getElem(&L, 3));
    traverseList(&L);	
    deleteFirstList(&L);           
  	deleteFirstList(&L);
	deleteLastList(&L);             
	deleteLastList(&L);
	deletePosList(&L, 2);         
   	deletePosList(&L, 1);  
    printf("%d \n", sizeList(&L));
    printf("%d \n", emptyList(&L));
    traverseList(&L);
    clearList(&L);
    return 0;
}