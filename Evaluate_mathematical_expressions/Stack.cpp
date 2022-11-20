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
}//��ʼ��

int Destroy(SqStack* S) {
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
	return 1;
}//����

int ClearStack(SqStack* S) {
	S->top = S->base;
	return 1;
}//���

int EmptyStack(SqStack* S) {
	int judge;
	if (S->top == S->base) {
		judge = True;//��ջ
	}
	else {
		judge = False;//�ǿ�ջ
	}
	return judge;
}//ջ�п�

int StackLength(SqStack* S) {
	return (int) (S->top - S->base);
}//ջ��

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
}//ջ��Ԫ��

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
}//��ջ

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
}//��ջ