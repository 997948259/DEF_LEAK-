#include<stdio.h>
#include<malloc.h>

int zuheshu(float s[],int n); // ������ĺ���
float zuhe[4]={0}; // ��ʱ������
int sum=0; // ���ڼ���
// ��̬����n��float����������
float * fsz(int n)
{
	return (float *)malloc(sizeof(float)*n);
}

int zuhefu(); //�������
int yunsuan(float s[],char p[],int k0[],int k1[]); // ��ʽ���
float qiujie(float suanshi[],int n); // ��ʽ���

int hefa(float suanshi[],int r); // ��ʽ��ȷ�Լ��
float jianjie(float suanshi[],int r); // ��ʽ����Լ��

int fuhe=0; // ����������ʽ��

void main()
{
	// �����ĸ���
	/*float shu[4]={0};
	printf("������4������(1~10):\n");
	scanf("%f",&shu[0]);
	scanf("%f",&shu[1]);
	scanf("%f",&shu[2]);
	scanf("%f",&shu[3]);
	//float shu[4]={1,2,3,4};
	printf("�����4������������: %.0f %.0f %.0f %.0f\n",shu[0],shu[1],shu[2],shu[3]);*/
	float s[4]={3,3,3,3},shu[4]={0};
	printf("�������ĸ���(0-9):\n");
	for(int i=0;i<4;i++)
	{
		scanf("%f",&s[i]);
		for(int j=i;j>0;j--)
		{
			if(s[j]<=s[j-1])
			{
				float s0=s[j-1];
				s[j-1]=s[j];
				s[j]=s0;
			}
		}
	}
	/*printf("�ĸ�����:");
	for(i=0;i<4;i++)
	{
		printf("%.0f ",s[i]);
	}
	printf("\n");*/
	zuheshu(s,4);
	
	printf("��%d����ʽ����\n",fuhe);
}

// �������������yunsuan
int zuheshu(float s[],int n)
{
	if(n==1)
	{
		zuhe[4-n]=s[0];
		zuhefu();
		return 1;
	}
	for(int i=0;i<n;i++)
	{
		if(i==0)
		{
			// ֱ������s[0],����ͺ�ѡ����ȥ������,�ݹ�
			zuhe[4-n]=s[i];//n=4
			float *p=fsz(n-1);
			int o=0;
			for(int k=0;k<n;k++)
			{
				if(k!=i)
					p[o++]=s[k];
			}
			zuheshu(p,n-1);
			free(p);
		}
		else if(s[i]!=s[i-1])
		{
			// ֱ������s[0],����ͺ�ѡ����ȥ������,�ݹ�
			zuhe[4-n]=s[i];
			float *p=fsz(n-1);
			int o=0;
			for(int k=0;k<n;k++)
			{
				if(k!=i)
					p[o++]=s[k];
			}
			zuheshu(p,n-1);
			//free(p);
		}
	}
}

// ����������,������yunsuan
int zuhefu()
{
	// �Բ�����'+','��','*','/'���
	char opter[4]={'+','-','*','/'};
	for(int h=0;h<4;h++) // ��һ��������
	{
		for(int i=0;i<4;i++) // �ڶ���������
		{
			for(int j=0;j<4;j++) // ������������
			{
				char op[3]; // ���ò�����
				op[0]=opter[h];
				op[1]=opter[i];
				op[2]=opter[j];
				// ���������
				/* 0 1 1 1 2 2 2 3*/
				int khzh[8][3]={{0,0,0},{0,0,1},{0,1,0},{1,0,0},{0,1,1},{1,0,1},{1,1,0},{1,1,1}}; // ��������
				for(int k=0;k<=3;k++)
				{
					switch(k)
					{
					case 0: // ��0������
						{
							yunsuan(zuhe,op,khzh[0],khzh[0]);
						}
						break;
					case 1: // ��1������
						{
							for(int m=1;m<=3;m++) // ������
							{
								for(int n=1;n<=3;n++) //������
								{//���뽫��ʽ��ϣ����ж���ȷ��;����(����)010��100Ϊ�������,010��010�޴������,001��100Ϊ�������,ͬʱ100��001������������Ӧ���ˣ��������ź�Ӳ�����,������,�����ǲ�����,�����ţ�
									//��ȷ���������
									if((m==2&&n==3)||(m==1&&n==2)||(m==3&&n==1)||(m==1&&n==3))
										continue;
									yunsuan(zuhe,op,khzh[m],khzh[n]);
								}
							}
						}
						break;
					case 2: // ��2������
						{
							//���뽫��ʽ��ϣ����ж���ȷ��;����(����)*1*��1**Ϊ������ϣ�**1��*1*Ϊ������ϣ�Ӧ���ˣ��������ź�Ӳ��������������������ǲ������������ţ�ͬʱ����1**��**1ҲӦ��Ϊ0**��**0
							//��ȷ����ֻ��һ�ּ�101��101
							yunsuan(zuhe,op,khzh[5],khzh[5]);
						}
						break;
					case 3: //��3������,������
						//����khzu[7]���뽫��ʽ��ϣ����ж���ȷ��(����ȷ)
						break;
					}
				}
			}
		}
	}
	return 1;
} 

// ��s[]�е��ĸ�������p[]��k[]�е������������ϲ�����qiujie()���������жϽ���Ƿ�Ϊ24
int yunsuan(float s[],char p[],int k0[],int k1[])
{
	float suanshi0[13]={'0'}; // �ϳɵ�ʽ
	int r=0; // ��ʽ�ĳ���
	// ��ϵ�ʽ
	for(int q=0;q<13;q++)
	{
		switch(q)
		{
		case 0:
			{
				if(k0[0]==1)
					suanshi0[r++]='(';
			}
			break;
		case 1:
			{
				suanshi0[r++]=s[0];
			}
			break;
		case 2:
			{
				suanshi0[r++]=p[0];
			}
			break;
		case 3:
			{
				if(k0[1]==1)
					suanshi0[r++]='(';
				
			}
			break;
		case 4:
			{
				suanshi0[r++]=s[1];
			}
			break;
		case 5:
			{
				if(k1[0]==1)
					suanshi0[r++]=')';
			}
			break;
		case 6:
			{
				suanshi0[r++]=p[1];
			}
			break;
		case 7:
			{
				if(k0[2]==1)
					suanshi0[r++]='(';
			}
			break;
		case 8:
			{
				suanshi0[r++]=s[2]; 
			}
			break;
		case 9:
			{
				if(k1[1]==1)
					suanshi0[r++]=')';
			}
			break;
		case 10:
			{
				suanshi0[r++]=p[2];
			}
			break;
		case 11:
			{
				suanshi0[r++]=s[3];
			}
			break;
		case 12:
			{
				if(k1[2]==1)
					suanshi0[r++]=')';
			}
			break;
		}
	}
	
	float * suanshi=fsz(r); // ��̬�ռ�����
	for(int i=0;i<r;i++)
	{
		suanshi[i]=suanshi0[i];
	}
	// �����ʽ����ȷ�Լ��
	/*float f=hefa(suanshi,r);
	if(f==0)
	{
		return 0;
	}
	// �����ʽ�ļ���Լ��
	//f=jianjie(suanshi,r);
	if(f==0)
	{
		return 0;
	}*/
	// ���ú��������Ϊ24�������ʽ
	float sum0=qiujie(suanshi,r);
	if(sum0==24)
	{
		fuhe++;
		for(int t=0;t<r;t++)
		{
			if(suanshi[t]>10)
				printf("%c",char(suanshi[t]));
			else
				printf("%0.0f",suanshi[t]);
		}
		printf("=%0.0f",sum0);
		printf("\n");
	}
	free(suanshi);
	return 1;
}

// ��ʽ��ȷ�Լ��
int hefa(float suanshi[],int r)
{
	float * p=&suanshi[0]; // Ϊ��ǰָ��
	float * q=&suanshi[1]; // Ϊ��һָ��
	int flag=1; // ��ʽ��ȷ���
	while(1)
	{
		if(*p==40) // �ж��Ƿ�Ϊ'('
		{
			if((*q>=0)&&(*q<=9))
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if((*p>=0)&&(*p<=9)) // �ж��Ƿ�Ϊ��
		{
			if((p-suanshi)>=(r-1))
			{
				break;
			}
			if(*q==')'||((*q>41)&&(*q<48))) // '+','-','*','/'�ڴη�Χ��
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if(*p==41) // �ж��Ƿ�Ϊ')'
		{
			if((p-suanshi)>=(r-1))
			{
				break;
			}
			if((*q>41)&&(*q<48)) // '+','-','*','/'�ڴη�Χ��
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if((*p>41)&&(*p<48)) // // �ж��Ƿ�Ϊ����
		{
			if(*q==40||((*q>=0)&&(*q<=9)))
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
	}
	return flag;
}

// ��ʽ����Լ��
float jianjie(float suanshi[],int r)
{
	float re=1; // �Ƿ����Ų�Ӱ����ʽ���
	float *p=&re,*q=&re;
	int k=0; // ������Ŀ
	int k1=0; // ������ĸ���
	float r0=0; // '('ǰ����������ȼ�
	float r2=1; // ��ʽ��������ȼ�
	float r1=0; // ')'�����������ȼ�
	int r3=0;
	for(int i=0;i<r;i++)
	{
		if(suanshi[i]=='(')
		{
			k++;
			if(*p!='('||k==1)
			{
				p=&suanshi[i];
				if(i!=0)
				{
					if(*(p-1)=='+'||*(p-1)=='-')
					{
						r0=1;
					}
					else if(*(p-1)=='*'||*(p-1)=='/')
					{
						r0=2;
					}
					if(*(p-1)=='-')
					{
						r0+=100;
					}
					else if(*(p-1)=='/')
					{
						r0+=1000;
					}
				}
			}
		}
		else if(suanshi[i]==')')
		{
			if(k--==1)
			{
				q=&suanshi[i];
				if(i!=r-1)
				{
					if(*(q+1)=='+'||*(q+1)=='-')
					{
						r1=1;
					}
					else if(*(q+1)=='*'||*(q+1)=='/')
					{
						r1=2;
					}
				}
				//�ݹ�
				re=jianjie(p+1,q-p-1); // ���������ڵ����ȼ�
				if(int(r0/100)>=1) // ����'('����ּ��Ż����
				{
					if((int(r0/100))==1&&(int(re/100))==1) // ����'('����ּ���,�����ڳ���+��-
					{
						continue;
					}
					else if((int(r0/1000))==1&&(int(re/1000))==1) // ����'('����ֳ���,�����ڳ���*��/
					{
						continue;
					}
				}
				if(int(re/100)==1)
					re-=100;
				if(int(re/1000)==1)
					re-=1000;
				if(int(r0/100)==1)
					r0-=100;
				else if(int(r0/1000)==1)
					r0-=1000;
				if(re==0)
					return 0;
				if(re>=r0&&re>=r1)
					return 0;
			}
		}
		else if(k==0)
		{
			if(suanshi[i]=='+'||suanshi[i]=='-')
			{
				r2=((r2*k1)+1)/(++k1);
				r3=r3/10+1;
			}
			else if(suanshi[i]=='*'||suanshi[i]=='/')
			{
				r2=(r2*k1+2)/(++k1);
				r3=r3%10+10;
			}
		}
	}
	if(r3%10==1)
		r2+=100;
	if(r3/10==1)
		r2+=1000;
	return r2;
}

// ���ú��������Ϊ24�������ʽ
float qiujie(float suanshi[],int n)
{
	if(n==3)
	{
		float a=0;
		switch(char(suanshi[1]))
		{
		case '+':
			return (suanshi[0]+suanshi[2]);
		case '-':
			return (suanshi[0]-suanshi[2]);
		case '*':
			return (suanshi[0]*suanshi[2]);
		case '/':
			return (suanshi[0]/suanshi[2]);
		}
	}
	// ���˵�������
	float pq='0';
	float * p=&pq; // ָ����ʽ�ĵ�һ��������
	float * q=&pq; // ָ����ʽ�����һ����������Եķ�����
	int k=0;
	float suanshi1[7]={'0'}; // ��ȥ���ź����ʽ
	int s=0; // ������¼suanshi1����ĳ���
	float sum=0; // ��ʽ��ֵ
	for(int m=0;m<n;m++)
	{
		if(suanshi[m]=='(')
		{
			k++;
			if((*p)!='(')
			{
				p=&suanshi[m];
			}
			continue;
		}
		if(suanshi[m]==')')
		{
			if(k--==1)
			{
				q=&suanshi[m];
				suanshi1[s++]=qiujie(p+1,q-p-1);
				p=&pq;
				q=&pq;
			}
			continue;
		}
		if(k==0)
		{
			suanshi1[s++]=suanshi[m];
			continue;
		}
	}
	if(s==3)
	{
		sum=qiujie(suanshi1,s);
	}
	else
	{
		p=&suanshi1[0]; // ָ���һ����
		q=&suanshi1[2]; // ֻ��ڶ�����
		for(m=0;m<(s-1)/2;m++)
		{
			switch(char(suanshi1[2*m+1]))
			{
			case '+':
				if((s-1)/2!=1&&(suanshi1[2*(m+1)+1]=='*'||suanshi1[2*(m+1)+1]=='/'))
				{
					*q=qiujie(p+2,3);
					int ws=&suanshi1[s-1]-&suanshi1[2*(m+1)];
					for(int w=1;w<=ws;w++)
					{
						if(((q+w+2)-(q+ws))>0)
						{
							*(q+w)=-1;
						}
						else
						{
							*(q+w)=*(q+w+2);
						}
					}
					s=s-2;
					m--;
				}
				else
				{
					if(m==0)
					{
						sum+=*p+*q;
					}
					else
					{
						sum+=*q;
					}
					p=p+2;
					q=q+2;
				}
				break;
			case '-':
				if((s-1)/2!=1&&(suanshi1[2*(m+1)+1]=='*'||suanshi1[2*(m+1)+1]=='/'))
				{
					*q=qiujie(p+2,3);
					int ws=&suanshi1[s-1]-&suanshi1[2*(m+1)];
					for(int w=1;w<=ws;w++)
					{
						if(((q+w+2)-(q+ws))>0)
						{
							*(q+w)=-1;
						}
						else
						{
							*(q+w)=*(q+w+2);
						}
					}
					s=s-2;
					m=-1;
				}
				else
				{
					if(m==0)
						sum+=*p-*q;
					else
						sum-=*q;
					p=p+2;
					q=q+2;
				}
				break;
			case '*':
				if(m==0)
					sum+=(*p)*(*q);
				else
					sum*=*q;
				p=p+2;
				q=q+2;
				break;
			case '/':
				if(m==0)
				{
					sum+=(*p)/(*q);
				}
				else
				{
					sum/=*q;
				}
				p=p+2;
				q=q+2;
				break;
			}
		}
	}
	return sum;
}
