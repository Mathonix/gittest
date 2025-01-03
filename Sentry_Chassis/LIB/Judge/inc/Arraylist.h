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

#define RM_ArrayList_InitArray initArray	//初始化数据列表函数
#define RM_ArrayList_ShowArray showArray	//显示列表所有成员
#define RM_ArrayList_IsEmpty isEmpty	//判读成员是否为空
#define RM_ArrayList_AppendValue appendValue	//添加数据
#define RM_ArrayList_IsFull isFull	//判断是否已满
#define RM_ArrayList_InsertValue insertValue	//插入元素
#define RM_ArrayList_DeleteValue deleteValue	//删除元素
#define RM_ArrayList_Inversion inversion	//倒置数组
#define RM_ArrayList_GetValue getValue	//得到元素   传入下标
#define RM_ArrayList_FindValue findValue	//查找元素   传入值  
#define RM_ArrayList_GetArrayLength getArrayLength	//获取数据长度
#define RM_ArrayList_DeleteAllValue deleteAllValue	//删除所有数据
#define RM_ArrayList_DeleteRangeValue deleteRangeValue //删除指定范围数据
//初始化  
void initArray(struct ArrayList * array, int length);
//遍历数组  
void showArray(struct ArrayList * array);
//是否是空数组  
bool isEmpty(struct ArrayList * array);
//追加元素  
bool appendValue(struct ArrayList * array, unsigned char val);
//是否为满  
bool isFull(struct ArrayList * array);
//插入元素  
bool insertValue(struct ArrayList * array, int pos, unsigned char val);
//删除元素  
bool deleteValue(struct ArrayList * array, int pos);
//倒置数组  
void inversion(struct ArrayList *array);
//得到元素   传入下标  
bool getValue(struct ArrayList * array, int index, unsigned char * val);
//查找元素   传入值  
int findValue(struct ArrayList * array, unsigned char val);
//获取长度
int getArrayLength(struct ArrayList * array);
//删除所有数据
bool deleteAllValue(struct ArrayList * array);
//删除指定范围数据
bool deleteRangeValue(struct ArrayList * array, int start, int end);
#endif 


