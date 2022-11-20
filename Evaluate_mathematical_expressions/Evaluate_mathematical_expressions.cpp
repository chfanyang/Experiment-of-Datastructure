#include "Stack.h"
#include <string.h>
#include <math.h>
#define ARGC_CNT 2

int Num(char ch);//判断当前取到的命令行参数是否是数字
void GetNumber(int& num, char* argv, SqStack* StackNum);//得到命令行参数中的每一个数字并将其放入数字栈中
void GetSignal(SqStack* StackSignal, SqStack* StackNum, int& num, char ch);//得到命令行参数中的运算符并将其放入符号栈中
char Precede(double signal, char ch);//运算符优先级判断函数
double clacute(double Num_delete_content_1, double Num_delete_content_2, double Signal_delete_content);//算式计算函数
double Final_Result_cal(char Stacksgnal, char ch, SqStack* StackNum, SqStack* StackSignal);//最终结果计算函数
void Output(double x);//格式化原样输出函数

int main(int argc, char* argv[]){
	if (argc != ARGC_CNT){
		printf("ERROR_01");
		getchar(); //等待用户输入
		return -1;
	}

	SqStack StackNum;//数字栈
	SqStack StackSignal;//符号栈
	int num = 0;//num用来遍历argv中的命令行参数
	char ch = argv[1][num];
	double signal;//最后判断是否有剩余算式时用来取栈顶元素的容器
	double Final_result = 0;//算式得到的最终结果
	
	InitStack(&StackNum);//初始化操作
	InitStack(&StackSignal);
	Push(&StackSignal, '#');//先在符号栈中压入一个元素'#'
	while (ch != '\0') {//在命令行参数未取完的情况下
		ch = argv[1][num];
		if (Num(ch)) {//从argv[1][num]中得到double类型的数字
			GetNumber(num, argv[1], &StackNum);
			ch = argv[1][num];
		}
		if(ch!='\0') {//从argv[1][num]中得到运算符
			GetSignal(&StackSignal, &StackNum, num, ch);
			ch= argv[1][num];
		}
	}
	GetTopElem(&StackSignal, signal);//因为最后可能会剩余一个算式如1+2或9+16*2，所以取栈顶元素做判断
	Final_result=Final_Result_cal((char)signal,ch, &StackNum, &StackSignal);//计算最终结果
	Output(Final_result);//原样输出结果
	return 0;
}

int Num(char ch) {//判断当前取到的命令行参数是否是数字
	int judge;
	if (ch >= '0' && ch <= '9') {//是数字
		judge = 1;
	}
	else {
		judge = 0;
	}
	return judge;
}

void GetNumber(int&num, char *argv, SqStack* StackNum) {//得到命令行参数中的每一个数字并将其放入数字栈中
	char ch = *(argv + num);
	double transfernum = 0;//存放char转化double后的数字
	double delete_content;//存放出栈的数字
	SqStack StackLittleNumtransferm;//用于将字符串argv中的小数部分转化成小数

	InitStack(&StackLittleNumtransferm);
	while (Num(ch)) {//整数部分
		transfernum = transfernum * 10 + (ch - '0');
		num++;
		ch = *(argv + num);
	}
	Push(StackNum, transfernum);
	transfernum = 0;
	if (ch == '.') {//小数部分
		num++;
		ch = *(argv + num);
		while (Num(ch)) {
			Push(&StackLittleNumtransferm, ch - '0');//压入小数栈
			num++;
			ch = *(argv + num);
		}
		while (!EmptyStack(&StackLittleNumtransferm)) {
			Pop(&StackLittleNumtransferm, delete_content);
			transfernum = (transfernum + delete_content) / 10;//此时transfernum存放小数部分
		}
		Pop(StackNum, delete_content);//delete_content存放整数部分
		transfernum += delete_content;//transfernum中存放完整的数
		Push(StackNum, transfernum);
	}
}

void GetSignal(SqStack* StackSignal, SqStack* StackNum, int& num, char ch) {//得到命令行参数中的运算符并将其放入符号栈中
	double signal;//栈顶元素
	double Signal_delete_content;//符号栈 出栈元素
	double Num_delete_content_1;//两个数字栈 出栈元素
	double Num_delete_content_2;
	double i;//计算中间变量
	GetTopElem(StackSignal, signal);
	switch (Precede(signal, ch)) {//比较栈顶元素和待入栈元素优先级大小
	case '<'://栈顶元素优先级低
		Push(StackSignal, ch);
		num++;
		break;
	case '=':
		Pop(StackSignal, Signal_delete_content);
		num++;
		break;
	case '>'://栈顶元素优先级高
		if (!Pop(StackNum, Num_delete_content_1) || !Pop(StackNum, Num_delete_content_2)) {//数字栈或符号栈出栈失败，说明有符号多余 如1++2
			printf("ERROR_02");
			getchar();
			exit(1);
		}
		Pop(StackSignal, Signal_delete_content);
		i = clacute(Num_delete_content_1, Num_delete_content_2, Signal_delete_content);
		Push(StackNum, i);
		break;
	case 'E'://部分括号不匹配Err
		printf("ERROR_02");
		getchar();
		exit(1);
		break;
	}
}

char Precede(double signal,char ch) {//运算符优先级判断函数
	char sig = (char)signal;
	char judge;
	char depot[12][12] = {
		/*+*/{'>','>','<','<','<','<','>','<','>','<','>','N'},
		/*-*/{'>','>','<','<','<','<','>','<','>','<','>','N'},
		/***/{'>','>','>','>','<','<','>','<','>','<','>','N'},
		/*/*/{'>','>','>','>','<','<','>','<','>','<','>','N'},
		/*^*/{'>','>','>','>','>','<','>','<','>','<','>','N'},
		/*(*/{'<','<','<','<','<','<','=','E','E','E','E','N'},
		/*)*/{'>','>','>','>','>','E','E','E','>','E','>','N'},
		/*[*/{'<','<','<','<','<','<','E','<','=','E','E','N'},
		/*]*/{'>','>','>','>','>','E','E','E','E','E','>','N'},
		/*{*/{'<','<','<','<','<','<','E','<','E','<','=','N'},
		/*}*/{'>','>','>','>','>','E','E','E','E','E','E','N'},
		/*#*/{'<','<','<','<','<','<','<','<','<','<','<','N'},
	};
	int x = 0,y=12;
	char signalx[12] = { '+','-','*','/','^','(',')','[',']','{','}','#' };
	int length = sizeof(signalx) / sizeof(signalx[0]);
	for (int i = 0; i < length; i++) {//遍历找到栈顶元素对应x坐标
		if (sig == signalx[i]) {
			x = i;
			break;
		}
	}
	for (int j = 0; j < length; j++) {//遍历找到待入栈元素元素对应y坐标
		if (ch == signalx[j]) {
			y = j;
			break;
		}
	}
	if (y == length || ch=='#') {//输入栈中的符号不是上面优先级中规定的符号
		printf("ERROR_02");
		getchar();
		exit(1);
	}
	judge = depot[x][y];
	return judge;
}

double clacute(double Num_delete_content_1, double Num_delete_content_2, double Signal_delete_content) {//算式计算函数
	double result = 0;
	double x1 = Num_delete_content_1, x2 = Num_delete_content_2;
	char x = (char)Signal_delete_content;
	switch (x) {
	case '+':
		result = x2 + x1;
		break;
	case '-':
		result = x2 - x1;
		break;
	case '*':
		result = x2 * x1;
		break;
	case '/':
		if (x1==0) {//除数为0的异常情况
			printf("ERROR_03");
			getchar();
			exit(1);
		}
		result = x2 / x1;
		break;
	case '^':
		result = pow(x2, x1);
		break;
	}
	return result;
}

double Final_Result_cal(char Stacksgnal, char ch, SqStack* StackNum, SqStack* StackSignal){//最终结果计算函数
	double signal;
	double final_result = 0;//用来存放得到的最后结果
	while (ch == '\0' && Stacksgnal != '#') {
		if (Stacksgnal == ')' || Stacksgnal == ']' || Stacksgnal == '}') {
			printf("ERROR_02");
			getchar();
			exit(1);
		}
		double Num_delete_content_1;
		double Num_delete_content_2;
		Pop(StackNum, Num_delete_content_1);
		Pop(StackNum, Num_delete_content_2);
		Pop(StackSignal, signal);
		final_result = clacute(Num_delete_content_1, Num_delete_content_2, signal);
		Push(StackNum, final_result);//结果再压回数字栈
		GetTopElem(StackSignal, signal);//再得到符号栈顶元素，判断算式是否做完
		Stacksgnal = (char)signal;
	}
	return final_result;
}

void Output(double x) {//格式化原样输出函数
	int num = x;
	double l;
	printf("%d", num);//输出整数部分
	x -= num;//x中存放小数部分
	if (x != 0) {
		printf(".");
	}//输出小数点
	double xnum = 0.0000001;
	x = x + xnum;//浮点数恢复原样
	do{
		num = (x * 10);
		l = x * 10;
		x = l - num;
		if (num != 0) {
			printf("%d", num);
		}
	} while (num != 0);
}