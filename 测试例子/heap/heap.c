#include <stdio.h>
#include <stdlib.h>

typedef int elemType;
/************************************************************************/
/*                    �����ǹ��ڶ�˳��洢������5���㷨                 */
/************************************************************************/
/* ����ѵ�˳��洢���� */
struct heap{
    elemType *heap;        /* ����ָ��̬����ռ��ָ�� */
    int len;            /* ���屣��ѳ��ȵı��� */
    int maxSize;        /* ���ڱ����ʼ��ʱ�����Ķ�̬����ռ�Ĵ�С */
};


/* 1.��ʼ���� */
void initHeap(struct heap *hbt, int ms)
{
    /* ���ms��ֵ�Ƿ���Ч */
    if (ms <= 0){
        printf("���鳤�Ȳ����Ƿ���");
        exit(1);
    }
    
    /* ��̬����洢������ռ� */
    hbt->heap = malloc(ms * sizeof(elemType));
    
    if (hbt->heap == NULL){
        printf("�ռ����ʧ�ܣ�");
        exit(1);
    }

    /* ����maxSize���len���ֵ */
    hbt->maxSize = ms;
    hbt->len = 0;

    return;
}

/* 2.����� */
void clearHeap(struct heap *hbt)
{
    if (hbt->heap != NULL){
        free(hbt->heap);
		printf("free ...\n");
        hbt->heap = NULL;
        hbt->len = 0;
        hbt->maxSize = 0;
    }

    return;
}

/* 3.���һ�����Ƿ�Ϊ�� */
int emptyHeap(struct heap *hbt)
{
    if (0 == hbt->len){
        return 1;
    }else{
        return 0;
    }
}

/* 4.����в���һ��Ԫ�� */
void insertHeap(struct heap *hbt, elemType x)
{
    int i;
    /* ����ʱ����ռ���չΪԭ����2����
       ԭ���ݱ��Զ�������p��ָ��Ĵ洢�ռ���*/
    if (hbt->len == hbt->maxSize){
        elemType *p;
        p = realloc(hbt->heap,( 2 + hbt->maxSize )* sizeof(elemType));
		printf("realloc ...\n");
        if (p == NULL){
            printf("�洢�ռ����ʧ�ܣ�");
            exit(1);
        }

        hbt->heap = p;        /* ������ռ�ָ���¿ռ� */
        hbt->maxSize = 2 + hbt->maxSize;        /* �޸�����ռ�Ĵ�С */
    }

    /* ���β�����Ԫ�� */
    hbt->heap[hbt->len] = x;
    hbt->len++;

    /* ��iָ�������Ԫ�ص�λ�ã���ʼָ����Ԫ�����ڵĶ�βλ�� */
    i = hbt->len - 1;

    /* Ѱ����Ԫ�ص�����λ�ã�ÿ��ʹ˫��Ԫ������һ�� */
    while (0 != i){
        int j = (i - 1) / 2;        /* jָ���±�Ϊi��Ԫ�ص�˫�� */
        /* �Ƚϵ��������˳�ѭ�� */
        if (x >= hbt->heap[j]){        
            break;
        }
        hbt->heap[i] = hbt->heap[j];        /* ˫��Ԫ������ */
        i = j;
    }
    hbt->heap[i] = x;        /* ����Ԫ�ص���������λ�� */

    return;
}

/* 5.�Ӷ���ɾ��Ԫ�� */
elemType deleteHeap(struct heap *hbt)
{
    elemType temp, x;
    int i, j;
    
    /* ��Ϊ�նѣ�����ʾ������Ϣ���˳����� */
    if (0 == hbt->len){
        printf("���ѿգ��˳����У�");
        exit(1);
    }
    
    /* ���Ѷ�Ԫ���ݴ���temp���Ա㷵�� */
    temp = hbt->heap[0];
    hbt->len--;

    /* ��ɾ���������Ϊ�ն��򷵻� */
    if (0 == hbt->len){
        return temp;
    }

    /* ���������Ķ�βԪ���ݴ���x�У��Ա��������λ�� */
    x = hbt->heap[hbt->len];
    /* ��iָ�������Ԫ�ص�λ�ã���ʼָ��Ѷ�λ�� */
    i = 0;
    /* ��jָ��i������λ�ã���ʼָ���±�1��λ�� */
    j = 2 * i + 1;
    /* Ѱ�Ҵ�����Ԫ�ص�����λ�ã�ÿ��ʹ����Ԫ������һ�� */
    while (j <= hbt->len - 1){        /* ����������Ϊ��ʱֹ */
        /* ���Һ��Ӵ��ڲ��ҽ�С��Ӧʹjָ���Һ��� */
        if ((j < hbt->len - 1) && (hbt->heap[j] > hbt->heap[j+1])){
            j++;
        }
        /* ����������������������˳�ѭ�� */
        if (x <= hbt->heap[j]){
            break;
        }
        /* ����Ԫ�����Ƶ�˫��λ�� */
        hbt->heap[i] = hbt->heap[j];
        /* ʹi��j�ֱ�ָ����һ���� */
        i = j;
        j = 2 * i + 1;
    }
    /* �Ѵ�����Ԫ�طŵ�����λ�� */
    hbt->heap[i] = x;
    
    return temp;
}

/************************************************************************/

int main(void)
{
    int i, x;
    int a[10];// = {23, 56, 40, 62, 38, 55, 10, 16};
    struct heap b;

    initHeap(&b, 3);
    /* ���b�����β�������a�е�ÿһ��Ԫ�� */
    for (i = 0; i < 10; i++){
		scanf("%d",&a[i]);
		if (a[i]!=-1)
		{
			insertHeap(&b, a[i]);
		}
        else
			break;
    }

    while (!emptyHeap(&b)){
        x = deleteHeap(&b);
        printf("%d", x);
        if (!emptyHeap(&b)){
            printf(",");
        }
    }

    printf("");
    clearHeap(&b);

    return 0;
}