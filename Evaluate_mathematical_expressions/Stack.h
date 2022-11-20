#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define StackSize 50
#define IncreaseSize 1

typedef double ElemType;
//typedef char ElemType2;

typedef struct {
	ElemType* base;
	ElemType* top;
	int stacksize;
}SqStack;

int InitStack(SqStack* S);//��ʼ��

int Destroy(SqStack* S);//����

int ClearStack(SqStack* S);//���

int EmptyStack(SqStack* S);//ջ�п�

int StackLength(SqStack* S);//ջ��

int GetTopElem(SqStack* S, ElemType &e);//ջ��Ԫ��

int Push(SqStack* S, ElemType e);//��ջ

int Pop(SqStack* S, ElemType& e);//��ջ