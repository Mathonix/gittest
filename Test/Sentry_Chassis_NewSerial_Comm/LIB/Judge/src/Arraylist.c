
#include "ArrayList.h"
/*************************************************************************
*  �������ƣ�initArray
*  ����˵������ʼ�������б�
*  ����˵����struct ArrayList * array������ָ��,int length:���鳤��
*  �������أ���	 
*  ��    ע��pvPortMalloc�����ڴ棬���ɲ���malloc 
*************************************************************************/
void initArray(struct ArrayList * array,int length)
{  
	array->qarr =  (unsigned char *)pvPortMalloc(sizeof(unsigned char) * length);  	//
    if(NULL == array->qarr)  
    {  
        printf("�����ڴ�ʧ��");  
    }  
    array->len = length;  
    array->total = 0;  
    return;  
}  
  
/*************************************************************************
*  �������ƣ�showArray
*  ����˵������ʼ�����б�
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע��printf��ʼ����
*************************************************************************/
void showArray(struct ArrayList * array)  
{  
    if(isEmpty(array))  
    {  
        printf("�������ǿյ�");  
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
*  �������ƣ�getArrayLength
*  ����˵������ȡ���ݳ���
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע����
*************************************************************************/
int getArrayLength(struct ArrayList * array)
{
	return array->total;
}

/*************************************************************************
*  �������ƣ�appendValue
*  ����˵������������
*  ����˵����struct ArrayList * array������ָ��,int val���������ֵ
*  �������أ���	 
*  ��    ע���б�ĩβ��������
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
*  �������ƣ�insertValue
*  ����˵������������
*  ����˵����struct ArrayList * array������ָ��,int pos������λ��,int val���������ֵ
*  �������أ���	 
*  ��    ע���б�ָ��λ�ò�������
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
*  �������ƣ�deleteValue
*  ����˵����ɾ��ָ������
*  ����˵����struct ArrayList * array������ָ��,int pos��ɾ������λ��
*  �������أ���	 
*  ��    ע���б�ָ��λ��ɾ�����ݣ���������ǰ��

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
*  �������ƣ�deleteAllValue
*  ����˵����ɾ��ȫ������
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע��ɾ��ȫ������
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
*  �������ƣ�insertValue
*  ����˵������������
*  ����˵����struct ArrayList * array������ָ��,int start����ʼλ��,int end������λ��
*  �������أ���	 
*  ��    ע���б�ָ����Χλ�ò�������
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
*  �������ƣ�getValue
*  ����˵������ȡ����
*  ����˵����struct ArrayList * array������ָ��,int index����ȡ����λ��,int val���������ֵ
*  �������أ���	 
*  ��    ע����ȡָ������
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
*  �������ƣ�isEmpty
*  ����˵�����ж��Ƿ�Ϊ��
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע����
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
*  �������ƣ�findValue
*  ����˵�����ж��Ƿ�Ϊ��
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע����
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
*  �������ƣ�isFull
*  ����˵�����ж��Ƿ�����
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע����
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
*  �������ƣ�inversion
*  ����˵���������б�
*  ����˵����struct ArrayList * array������ָ��
*  �������أ���	 
*  ��    ע����
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


