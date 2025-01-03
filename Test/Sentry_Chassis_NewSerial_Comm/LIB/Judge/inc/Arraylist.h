#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include "main.h"
#include "stdbool.h"
struct ArrayList
{
	unsigned char * qarr;
	int len;
	int total;
};

#define RM_ArrayList_InitArray initArray	//��ʼ�������б���
#define RM_ArrayList_ShowArray showArray	//��ʾ�б����г�Ա
#define RM_ArrayList_IsEmpty isEmpty	//�ж���Ա�Ƿ�Ϊ��
#define RM_ArrayList_AppendValue appendValue	//�������
#define RM_ArrayList_IsFull isFull	//�ж��Ƿ�����
#define RM_ArrayList_InsertValue insertValue	//����Ԫ��
#define RM_ArrayList_DeleteValue deleteValue	//ɾ��Ԫ��
#define RM_ArrayList_Inversion inversion	//��������
#define RM_ArrayList_GetValue getValue	//�õ�Ԫ��   �����±�
#define RM_ArrayList_FindValue findValue	//����Ԫ��   ����ֵ  
#define RM_ArrayList_GetArrayLength getArrayLength	//��ȡ���ݳ���
#define RM_ArrayList_DeleteAllValue deleteAllValue	//ɾ����������
#define RM_ArrayList_DeleteRangeValue deleteRangeValue //ɾ��ָ����Χ����
//��ʼ��  
void initArray(struct ArrayList * array, int length);
//��������  
void showArray(struct ArrayList * array);
//�Ƿ��ǿ�����  
bool isEmpty(struct ArrayList * array);
//׷��Ԫ��  
bool appendValue(struct ArrayList * array, unsigned char val);
//�Ƿ�Ϊ��  
bool isFull(struct ArrayList * array);
//����Ԫ��  
bool insertValue(struct ArrayList * array, int pos, unsigned char val);
//ɾ��Ԫ��  
bool deleteValue(struct ArrayList * array, int pos);
//��������  
void inversion(struct ArrayList *array);
//�õ�Ԫ��   �����±�  
bool getValue(struct ArrayList * array, int index, unsigned char * val);
//����Ԫ��   ����ֵ  
int findValue(struct ArrayList * array, unsigned char val);
//��ȡ����
int getArrayLength(struct ArrayList * array);
//ɾ����������
bool deleteAllValue(struct ArrayList * array);
//ɾ��ָ����Χ����
bool deleteRangeValue(struct ArrayList * array, int start, int end);
#endif 


