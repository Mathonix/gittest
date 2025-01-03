
#include "ArrayList.h"
/*************************************************************************
*  函数名称：initArray
*  功能说明：初始化数组列表
*  参数说明：struct ArrayList * array：数组指针,int length:数组长度
*  函数返回：无	 
*  备    注：pvPortMalloc申请内存，不可采用malloc 
*************************************************************************/
void initArray(struct ArrayList * array,int length)
{  
	array->qarr =  (unsigned char *)pvPortMalloc(sizeof(unsigned char) * length);  	//
    if(NULL == array->qarr)  
    {  
        printf("分配内存失败");  
    }  
    array->len = length;  
    array->total = 0;  
    return;  
}  
  
/*************************************************************************
*  函数名称：showArray
*  功能说明：初始数组列表
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：printf初始数据
*************************************************************************/
void showArray(struct ArrayList * array)  
{  
    if(isEmpty(array))  
    {  
        printf("该数组是空的");  
    }  
    else  
    {  
        for(int i=0;i<array->total;i++)  
        {  
            printf("0x%x \t",(array->qarr)[i]);  
        }  
    }  
}  


/*************************************************************************
*  函数名称：getArrayLength
*  功能说明：获取数据长度
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：无
*************************************************************************/
int getArrayLength(struct ArrayList * array)
{
	return array->total;
}

/*************************************************************************
*  函数名称：appendValue
*  功能说明：加入数据
*  参数说明：struct ArrayList * array：数组指针,int val：插入的数值
*  函数返回：无	 
*  备    注：列表末尾插入数据
*************************************************************************/
bool appendValue(struct ArrayList * array,unsigned char val)  
{  
    if (isFull(array)) {  
        return false;  
    }  
    array->qarr[array->total]=val;  
    array->total++;  
    return true;  
}  

/*************************************************************************
*  函数名称：insertValue
*  功能说明：插入数据
*  参数说明：struct ArrayList * array：数组指针,int pos：插入位置,int val：插入的数值
*  函数返回：无	 
*  备    注：列表指定位置插入数据
*************************************************************************/
bool insertValue(struct ArrayList * array,int pos,unsigned char val)  
{  
    if(pos<0 || pos>array->total)  
    {  
        return false;  
    }  
    else if (isFull(array))  
    {  
        return false;  
    }  
    for (int i=array->total-1; i>=pos-1; i--) {  
        array->qarr[i+1] = array->qarr[i];  
    }  
    array->qarr[pos-1] = val;  
    array->total++;  
    return true;  
}  
  
/*************************************************************************
*  函数名称：deleteValue
*  功能说明：删除指定数据
*  参数说明：struct ArrayList * array：数组指针,int pos：删除数据位置
*  函数返回：无	 
*  备    注：列表指定位置删除数据，所有数据前移

*************************************************************************/
bool deleteValue(struct ArrayList * array,int pos)  
{  
    if (isEmpty(array)) 
	{  
        return false;  
    }
    else if(pos<0 || pos>array->total)  
    {  
		return false;  
    }
	

	for (int i=pos; i<=array->total-1; i++) 
	{  
		array->qarr[i-1] = array->qarr[i];
		array->qarr[i]=0;
	}
	array->total--; 
    return true;  
}  

/*************************************************************************
*  函数名称：deleteAllValue
*  功能说明：删除全部数据
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：删除全部数据
*************************************************************************/
bool deleteAllValue(struct ArrayList * array)
{
	int len = array->total;
	for (int i = 0; i < len; i++)
	{
		if (!deleteValue(array, 0))
		{
			return false;
		}
	}
	return true;
}

/*************************************************************************
*  函数名称：insertValue
*  功能说明：插入数据
*  参数说明：struct ArrayList * array：数组指针,int start：开始位置,int end：结束位置
*  函数返回：无	 
*  备    注：列表指定范围位置插入数据
*************************************************************************/
bool deleteRangeValue(struct ArrayList * array,int start,int end)
{
	if (start > end)
	{
		return false;
	}
	if (end>array->total-1)
	{
		end = array->total-1;
	}
	for (int i = 0; i < (end-start); i++)
	{
		if (!deleteValue(array, start))
		{
			return false;
		}
	}
	return true;

}

/*************************************************************************
*  函数名称：getValue
*  功能说明：获取数据
*  参数说明：struct ArrayList * array：数组指针,int index：获取数据位置,int val：插入的数值
*  函数返回：无	 
*  备    注：获取指定数据
*************************************************************************/
bool getValue(struct ArrayList * array,int index ,unsigned char * val)	
{  
    if (index<0 || index>array->total-1) {  
        return false;  
    }  
    else  
    {  
        *val = array->qarr[index];  
        return true;  
    }  
}  
  
/*************************************************************************
*  函数名称：isEmpty
*  功能说明：判断是否为空
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：无
*************************************************************************/
bool isEmpty(struct ArrayList * array)  
{  
    if(array->total == 0)  
    {  
        return true;  
    }  
    else  
    {  
        return false;     
    }  
}  
 
/*************************************************************************
*  函数名称：findValue
*  功能说明：判断是否为空
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：无
*************************************************************************/
int findValue(struct ArrayList * array,unsigned char value)  
{  
    int index=0;  
    for (int i=0; i<array->total; i++) 
	{  
        if (array->qarr[i]==value) 
		{  
            index=i;  
            break;  
        }  
        if (i==array->total-1) 
		{  
            return -1;  
        }  
    }
    return index;  
}  

/*************************************************************************
*  函数名称：isFull
*  功能说明：判断是否已满
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：无
*************************************************************************/
bool isFull(struct ArrayList * array)  
{  
      
    if (array->total==array->len) {  
        return true;  
    }  
    else  
    {  
        return false;  
    }  
      
}  

/*************************************************************************
*  函数名称：inversion
*  功能说明：倒置列表
*  参数说明：struct ArrayList * array：数组指针
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void inversion(struct ArrayList * array)  
{  
    int i=0;  
    int j=array->total-1;  
    int temp;  
    while (i<j)  
    {  
        temp=array->qarr[i];  
        array->qarr[i]=array->qarr[j];  
        array->qarr[j]=temp;  
        i++;  
        j--;  
    }  
      
}  


