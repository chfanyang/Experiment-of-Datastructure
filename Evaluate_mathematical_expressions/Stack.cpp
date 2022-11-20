#include "Stack.h"

int InitStack(SqStack* S) {
	S->base = (ElemType*) malloc(StackSize * sizeof(ElemType));
	if (S->base == NULL) {
		return 0;
		exit(1);
	}
	S->stacksize = StackSize;
	S->top = S->base;
	return 1;
}//³õÊ¼»¯

int Destroy(SqStack* S) {
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
	return 1;
}//Ïú»Ù

int ClearStack(SqStack* S) {
	S->top = S->base;
	return 1;
}//Çå¿Õ

int EmptyStack(SqStack* S) {
	int judge;
	if (S->top == S->base) {
		judge = True;//¿ÕÕ»
	}
	else {
		judge = False;//·Ç¿ÕÕ»
	}
	return judge;
}//Õ»ÅĞ¿Õ

int StackLength(SqStack* S) {
	return (int) (S->top - S->base);
}//Õ»³¤

int GetTopElem(SqStack* S, ElemType& e) {
	int judge;
	if (S->top != S->base) {
		e = *(S->top - 1);
		judge = True;
	}
	else {
		judge = False;
	}
	return judge;
}//Õ»¶¥ÔªËØ

int Push(SqStack* S, ElemType e) {
	int judge;
	if (S->top - S->base >= S->stacksize) {
		S->base = (ElemType*)realloc(S->base, sizeof(ElemType) * (StackSize + IncreaseSize));
		if (S->base == NULL) {
			return False;
			exit(1);
		}
		else {
			S->stacksize = S->stacksize + IncreaseSize;
		}
	}
	else {
		*(S->top) = e;
		(S->top)++;
		judge = True;
	}
	return judge;
}//ÈëÕ»

int Pop(SqStack* S, ElemType& e) {
	int judge;
	if (S->top != S->base) {
		e = *(S->top - 1);
		(S->top)--;
		judge = True;
	}
	else {
		judge = False;
	}
	return judge;
}//³öÕ»