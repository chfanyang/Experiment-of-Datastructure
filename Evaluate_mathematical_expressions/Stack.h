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

int InitStack(SqStack* S);//初始化

int Destroy(SqStack* S);//销毁

int ClearStack(SqStack* S);//清空

int EmptyStack(SqStack* S);//栈判空

int StackLength(SqStack* S);//栈长

int GetTopElem(SqStack* S, ElemType &e);//栈顶元素

int Push(SqStack* S, ElemType e);//入栈

int Pop(SqStack* S, ElemType& e);//出栈