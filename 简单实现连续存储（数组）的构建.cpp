#include<stdio.h>
#include<malloc.h>//包含了 malloc函数 
#include<stdlib.h>//包含了exit函数 

struct Arr
{
	int *pBase;//存储的是数组的第一个元素的地址 
	int len;//数组当前所能容纳的最大元素的个数 
	int cnt;//当前数组有效的元素的个数
//	int increment;//自动增长因子 
}; 

void init_arr(struct Arr *,int);//初始化 
bool append_arr (struct Arr *,int );//追加 
bool insert_arr (struct Arr *,int ,int );//插入
bool delete_arr(struct Arr*,int ,int *);//删除
int get();//获取
bool is_empty(struct Arr *);//是否为空
bool is_full();//是否为满
void sort_arr(struct Arr*);//排序 
void show_arr(struct Arr *);
void inversion_arr(struct Arr *);//倒置
 

int main(void)
{
	struct Arr arr;
	//此时，还没有生成一个数组，因为struct Arr 中的pBase、len、cnt全是垃圾数字
	//需要用 init_arr 这个函数来让 变量arr 初始化（pBase指向一个数组）
	int val;
	               
	init_arr(&arr,6);			    
	               
	show_arr(&arr); 
	
	append_arr(&arr,4);
	
	if(delete_arr(&arr,1,&val)  )
	{
		printf("删除成功!\n");
		printf("您删除的元素是：%d\n ",val);
	}
	else
	{
		printf("删除失败!\n");
	}
	
	
	
	append_arr(&arr,5);
	append_arr(&arr,9);
	append_arr(&arr,23);
	
	insert_arr(&arr,2,99);
	insert_arr(&arr,1,8);
	insert_arr(&arr,8,0);//没插入进去,因为没有第八个位置 
	
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

//初始化 
void init_arr (struct Arr * parr,int length)
{
	parr->pBase = (int *)malloc(sizeof(int) * length );
	//要检验pBase是否分配成功 ，若不成功他就为NULL 
	if( NULL == parr->pBase )
	{
		printf("FAIL");
		exit(-1);//表示终止整个程序 
	}
	else
	{ 
		parr->len = length;   
		parr->cnt = 0;
	}
	
	return ;
}

//判断数组是否为空 
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

//输出

void show_arr(struct Arr * parr)
//如果数组为空，则提示用户数组为空；否则，输出数组内容 
{
	int i;
	
	if(is_empty(parr) == true )
	{
		printf("该数组为空!\n");
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
 
 //判断是否为满
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
 
 
 //追加 
bool append_arr (struct Arr * parr,int val )
//如果数组满了，就不能追加了,val为追加的数 
{
	//满返回true 
 	if(is_full(parr) == true)
 	{
 		return false;
	}
	//不满返回false
	else
	{
		parr->pBase[parr->cnt] = val;
		(parr->cnt) ++;
		return true;
	} 
} 
 
 
 //插入
bool insert_arr (struct Arr *parr,int pos ,int val ) 
//pos的范围从1开始 ，val 表示插入的值 
{
	//应该先把要插入的位置以后的数字往后移，不然先插入的话，就有一个原先的数字被覆盖
	//数组满了 或 输入的 pos 小于1 或者 大于 len-1 
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
	//不想要对应位置上的数字消失，与主函数的输出相对应 
	for(i = pos ; i<parr->cnt;i++ )
	{
		parr->pBase[i-1] = parr->pBase[i];
	}
	parr->cnt --;
	
} 

//倒序 
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
//冒泡排序
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
 
