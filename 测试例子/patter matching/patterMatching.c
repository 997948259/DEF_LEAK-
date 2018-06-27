/******************************************************** 
 *                    ���ļ�ģʽƥ��                  *
 ********************************************************/ 

#include <stdio.h>
#include <stdlib.h>

/* ���嵥����ṹ�� */
struct node
{
    char ch;
    struct node *next;
};

/* ��ʼ�������� */
void init(struct node **h)
{
    *h = (struct node*)malloc(sizeof(struct node));
    (*h)->next = NULL;
    return;
}

/* ��x�����뵽����� */
void append(struct node *p, int x)
{
    struct node *s;

    s = (struct node*)malloc(sizeof(struct node));
    s->ch = x;
    s->next = NULL;
    /* �ƶ�����β */
    while (p->next != NULL)
    {
        p = p->next;
    }
    
    p->next = s;
    
    return;
}

void display(struct node *p)
{
    printf("You typed string is: ");
    while (p->next != NULL)
    {
        printf("%c", p->next->ch);
        p = p->next;
    }
    printf("\n");

    return;
}

int main(int argc, char *argv[])
{
    struct node *t, *s;    /* sΪ����, tΪģʽ�� */
    struct node *sNext, *p, *q;
    int i, x = 0;
    
    init(&s);
    printf("Please type main string: ");
    while (x != ' ')
    {
        x = getchar();
        if (x != ' ')
        {
            append(s, x);        /* ��ӵ���β */
        }
    }
    display(s);
    
    init(&t);
    printf("Please type substring: ");
    x = 0;
    while (x != ' ')
    {
        x = getchar();
        if (x != ' ')
        {
            append(t, x);        /* ��ӵ���β */
        }
    }
    display(t);
    
    /* ��ʼ�� */
    sNext = s->next;
    p = sNext;
    q = t->next;
    i = 1;        
    /* �ӿ�ʼ�ַ����бȽ� */
    while ((p->next != NULL) && (q->next != NULL))
    {
        /* ����ƥ����� */
        if (p->ch == q->ch)
        {
            p = p->next;
            q = q->next;
        }
        else    
        {
            sNext = sNext->next;
            p = sNext;        /* ָ�������е���һ�� */
            q = t->next;    /* ָ��������¿�ʼƥ�� */
            i++;        /* ��¼λ�� */
        }
    }
    /* ������ */
    if ((q->next) == NULL && (t->next->ch == s->next->ch))
    {
        printf("match position: %d", i);
    }
    else
    {
        printf("Not match!");
    }
    printf("\n");
    
    return 0;
}