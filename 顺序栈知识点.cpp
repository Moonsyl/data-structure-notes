#include <iostream>   // 引入输入输出流头文件，用于cin、cout
using namespace std;  // 使用标准命名空间，不用写std::cin std::cout
#define OK 1           // 宏定义：操作成功返回1
#define ERROR 0        // 宏定义：操作失败返回0
#define OVERFLOW -1    // 宏定义：内存溢出返回-1
#define MAXSIZE 100    // 宏定义：顺序栈最大容量
typedef int Status;    // 函数返回状态类型，取值OK/ERROR/OVERFLOW
typedef int SElemType; // 栈中元素的数据类型，这里是int
// 顺序栈结构体定义（指针版，严蔚敏教材）
typedef struct{
	SElemType *top;   // 栈顶指针：指向栈顶元素下一个位置
	SElemType *base;  // 栈底指针：指向数组起始地址
	int stacksize;    // 栈的最大容量
}SqStack;
// 初始化顺序栈
Status InitStack(SqStack &S){
	S.base=new SElemType[MAXSIZE]; // 分配一块连续堆内存作为栈空间
	if(!S.base) exit(OVERFLOW);    // 内存分配失败，退出程序，返回溢出
	S.top=S.base;                  // 栈空时，栈顶指针=栈底指针
	S.stacksize=MAXSIZE;           // 设置栈最大容量
	return OK;                     // 初始化成功
}
// 入栈操作：将元素e压入栈S
Status Push(SqStack &S,SElemType e){
	if(S.top-S.base==S.stacksize) return ERROR; // 判断栈满，满则入栈失败
	*S.top++=e;  // 把e写入top指向位置，然后top指针后移一位
	return OK;   // 入栈成功
}
// 出栈操作：删除栈顶元素，用e带回该元素的值
Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR; // 判断栈空，空则无法出栈
	e=*--S.top;  // top先向前移动一位，取出栈顶元素存入e
	return OK;   // 出栈成功
}
// 判断栈是否为空
Status StackEmpty(SqStack S){
	if(S.top==S.base)
	  return OK;    // top==base代表栈空，返回OK
	else
	  return ERROR; // 栈非空返回ERROR
}
// 获取栈当前元素个数
int StackLength(SqStack S){
	return S.top-S.base; // 指针相减，得到元素数量
}
// 遍历栈：从栈底到栈顶依次输出
void StackTraverse(SqStack S){
	if(StackEmpty(S)){
		cout<<"栈为空"<<endl;
		return;
	}
	SElemType *p=S.base; // p从栈底开始遍历
	while(p!=S.top){     // p没走到栈顶位置就继续循环
		cout<<*p<<" ";   // 输出p指向的元素
		p++;             // 指针后移
	}
	cout<<endl;
}
// 销毁栈：释放堆内存
void DestroyStack(SqStack &S){
	delete[] S.base;     // 释放new出来的数组内存
	S.base=NULL;         // 栈底指针置空，防止野指针
	S.top=NULL;          // 栈顶指针置空
	S.stacksize=0;       // 栈容量清零
}
// 清空栈：逻辑清空，不释放内存
Status ClearStack(SqStack &S){
	S.top = S.base; // 栈顶指针直接移到栈底，逻辑上全部元素清空
	return OK;
}
// 判断栈是否满
Status StackFull(SqStack S){
	if(S.top - S.base == S.stacksize)
		return OK;
	else
		return ERROR;
}
// 获取栈顶元素，元素通过引用e带出，返回操作状态
Status GetTop(SqStack S, SElemType &e){
	if(StackEmpty(S)) return ERROR; // 如果栈空，获取失败
	e = *(S.top - 1);               // 栈非空，取出栈顶元素存入e
	return OK;                      // 获取成功
}

int main(){
	SqStack S;                // 定义一个顺序栈变量S
	InitStack(S);             //【调用】初始化栈
	
	int n;
	cout << "请输入元素个数n：";
	cin >> n;                 // 读取元素总数n
	
	cout << "请依次输入" << n << "个整数：" << endl;
	SElemType e;              // 临时变量，存放输入的元素
	for(int i = 0; i < n; i++){
		cin >> e;             
		Push(S, e);          //【调用】循环入栈
	}

	// ========== 逐个调用所有函数 ==========
	cout << "\n===== 调用 StackTraverse 遍历栈 =====" << endl;
	cout << "栈内元素（栈底→栈顶）：";
	StackTraverse(S);         //【调用】遍历输出栈内所有元素

	cout << "\n===== 调用 StackLength 获取栈长度 =====" << endl;
	cout << "栈当前长度：" << StackLength(S) << endl; //【调用】输出元素个数

	cout << "\n===== 调用 StackFull 判断栈是否满 =====" << endl;
	if(StackFull(S))         //【调用】判断栈满
		cout << "栈已满" << endl;
	else
		cout << "栈未满" << endl;

	cout << "\n===== 调用 GetTop 获取栈顶 =====" << endl;
	SElemType top_e;          
	GetTop(S, top_e);         //【调用】获取栈顶元素
	cout << "栈顶元素：" << top_e << endl;

	cout << "\n===== 调用 Pop 出栈 =====" << endl;
	Pop(S, e);                //【调用】出栈
	cout << "弹出的元素是：" << e << endl;
	cout << "出栈后栈：";
	StackTraverse(S);

	cout << "\n===== 调用 StackEmpty 判断栈是否空 =====" << endl;
	if(StackEmpty(S))         //【调用】判断栈空
		cout << "栈是空的" << endl;
	else
		cout << "栈非空" << endl;

	cout << "\n===== 调用 ClearStack 清空栈（逻辑清空，不释放内存） =====" << endl;
	ClearStack(S);            //【调用】清空栈
	cout << "清空后栈：";
	StackTraverse(S);

	cout << "\n===== 再次调用 StackEmpty =====" << endl;
	if(StackEmpty(S))
		cout << "清空后栈为空" << endl;
	else
		cout << "清空后栈非空" << endl;

	DestroyStack(S);          //【调用】销毁栈，释放内存
	cout << "\n===== 调用 DestroyStack，栈已销毁 =====" << endl;
	return 0;
}

