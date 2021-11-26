#include<stdio.h>
#include<malloc.h>//������ malloc���� 
#include<stdlib.h>//������exit���� 

struct Arr
{
	int *pBase;//�洢��������ĵ�һ��Ԫ�صĵ�ַ 
	int len;//���鵱ǰ�������ɵ����Ԫ�صĸ��� 
	int cnt;//��ǰ������Ч��Ԫ�صĸ���
//	int increment;//�Զ��������� 
}; 

void init_arr(struct Arr *,int);//��ʼ�� 
bool append_arr (struct Arr *,int );//׷�� 
bool insert_arr (struct Arr *,int ,int );//����
bool delete_arr(struct Arr*,int ,int *);//ɾ��
int get();//��ȡ
bool is_empty(struct Arr *);//�Ƿ�Ϊ��
bool is_full();//�Ƿ�Ϊ��
void sort_arr(struct Arr*);//���� 
void show_arr(struct Arr *);
void inversion_arr(struct Arr *);//����
 

int main(void)
{
	struct Arr arr;
	//��ʱ����û������һ�����飬��Ϊstruct Arr �е�pBase��len��cntȫ����������
	//��Ҫ�� init_arr ����������� ����arr ��ʼ����pBaseָ��һ�����飩
	int val;
	               
	init_arr(&arr,6);			    
	               
	show_arr(&arr); 
	
	append_arr(&arr,4);
	
	if(delete_arr(&arr,1,&val)  )
	{
		printf("ɾ���ɹ�!\n");
		printf("��ɾ����Ԫ���ǣ�%d\n ",val);
	}
	else
	{
		printf("ɾ��ʧ��!\n");
	}
	
	
	
	append_arr(&arr,5);
	append_arr(&arr,9);
	append_arr(&arr,23);
	
	insert_arr(&arr,2,99);
	insert_arr(&arr,1,8);
	insert_arr(&arr,8,0);//û�����ȥ,��Ϊû�еڰ˸�λ�� 
	
	show_arr(&arr); 
	
	inversion_arr(&arr);
	show_arr(&arr); 
	 
	sort_arr(&arr);
	
/* 
	append_arr(&arr,9);
	append_arr(&arr,1);
	if(append_arr(&arr,2))
	{
		printf("success!\n");
	}
	else
	{
		printf("fail!\n");
	}
	
*/
	
	show_arr(&arr); 
	
	
	return 0;
}

//��ʼ�� 
void init_arr (struct Arr * parr,int length)
{
	parr->pBase = (int *)malloc(sizeof(int) * length );
	//Ҫ����pBase�Ƿ����ɹ� �������ɹ�����ΪNULL 
	if( NULL == parr->pBase )
	{
		printf("FAIL");
		exit(-1);//��ʾ��ֹ�������� 
	}
	else
	{ 
		parr->len = length;   
		parr->cnt = 0;
	}
	
	return ;
}

//�ж������Ƿ�Ϊ�� 
bool is_empty(struct Arr * parr)
{
	if( 0== parr->cnt )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//���

void show_arr(struct Arr * parr)
//�������Ϊ�գ�����ʾ�û�����Ϊ�գ���������������� 
{
	int i;
	
	if(is_empty(parr) == true )
	{
		printf("������Ϊ��!\n");
	}
	else
	{
		for(i=0;i<parr->cnt;++i)
		{
			printf("%-5d",parr->pBase[i]);
		}
		printf("\n");
	}
}
 
 //�ж��Ƿ�Ϊ��
 bool is_full(struct Arr *parr)
{
 	if(parr->cnt == parr->len)
 	{
 		return true;
	}
	else
	{
		return false;
	}
} 
 
 
 //׷�� 
bool append_arr (struct Arr * parr,int val )
//����������ˣ��Ͳ���׷����,valΪ׷�ӵ��� 
{
	//������true 
 	if(is_full(parr) == true)
 	{
 		return false;
	}
	//��������false
	else
	{
		parr->pBase[parr->cnt] = val;
		(parr->cnt) ++;
		return true;
	} 
} 
 
 
 //����
bool insert_arr (struct Arr *parr,int pos ,int val ) 
//pos�ķ�Χ��1��ʼ ��val ��ʾ�����ֵ 
{
	//Ӧ���Ȱ�Ҫ�����λ���Ժ�����������ƣ���Ȼ�Ȳ���Ļ�������һ��ԭ�ȵ����ֱ�����
	//�������� �� ����� pos С��1 ���� ���� len-1 
	int i;
	
	if(is_full(parr))
	{
		return false;
	} 
	
	if( pos > parr-> cnt + 1 || pos < 1 )
	{
		return false;
	}
	
	for(i = parr->cnt - 1 ; i >= pos-1 ; --i )
	{
		parr->pBase[i+1]  =  parr->pBase[i];
	} 
	
	parr->pBase[pos-1] = val;
	(parr->cnt)++;
	
	return true;
}

bool delete_arr(struct Arr* parr,int pos,int * pval)
{
	int i;
	if(is_empty(parr))
	{
		return false;
	}
	if( pos < 1 || pos > parr->cnt  )
	{
		return false;
	}
	
	*pval = parr->pBase[pos-1];
	//����Ҫ��Ӧλ���ϵ�������ʧ������������������Ӧ 
	for(i = pos ; i<parr->cnt;i++ )
	{
		parr->pBase[i-1] = parr->pBase[i];
	}
	parr->cnt --;
	
} 

//���� 
void inversion_arr(struct Arr*parr)
{
	int i = 0;
	int j = parr->cnt - 1;
	int t;
	
	while(i<j)
	{
		t = parr->pBase[i];
		parr->pBase[i] = parr->pBase[j];
		parr->pBase[j] = t;
		++i;
		--j;
		
	}
	
}
//ð������
void sort_arr(struct Arr* parr)
{
	int i;
	int j;
    int t;
	for(i=0;i< parr->cnt -1 ;i++ )
	{
		for(j=0;j< parr->cnt-1-i ; j++)
		{
			if(parr->pBase[j] > parr->pBase[j+1])
			{
				t = parr->pBase[j];
				parr->pBase[j] = parr->pBase[j+1];
				parr->pBase[j+1] = t;
			}
		}
		 
	}
}
 
