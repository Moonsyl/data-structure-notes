#include <iostream>       // 引入输入输出流库，用于cin、cout
using namespace std;      // 使用标准命名空间，不用写std::cin std::cout
#define OK 1               // 宏定义：函数执行成功返回1
#define ERROR 0            // 宏定义：函数执行失败返回0
#define OVERFLOW -1        // 宏定义：内存溢出返回-1
typedef int Status;        // Status是int的别名，用来表示函数状态OK/ERROR
typedef int SElemType;     // SElemType是int别名，栈操作元素类型
typedef int ElemType;      // ElemType是int别名，结点存储数据类型

// 定义链栈结点结构体
typedef struct StackNode{
	ElemType data;         // 数据域：存放结点里的数据
	struct StackNode *next;// 指针域：存放下一个结点的地址
}StackNode,*LinkStack; 
// StackNode：结构体类型别名（结点本体）
// LinkStack：结构体指针别名，等价 StackNode *，代表栈顶指针

// 初始化链栈
Status InitStack(LinkStack &S){
	S=NULL;                 // 栈顶指针置空，表示栈里没有结点
	return OK;              // 初始化成功，返回OK
}

// 入栈：头插法，把元素e压入栈顶
Status Push(LinkStack &S,SElemType e){
	StackNode *p;           // 定义结点指针p，用来指向新建结点
	p=new StackNode;        // 在堆内存开辟一个新结点，p保存结点地址
	p->data=e;              // 新结点数据域赋值为e
	p->next=S;              // 新结点的next指向原来的栈顶结点
	S=p;                    // 更新栈顶指针S，S指向新结点（新栈顶）
	return OK;              // 入栈成功返回OK
}

// 出栈：删除栈顶元素，用e带出栈顶的值
Status Pop(LinkStack &S,SElemType &e){
	if(S==NULL) return ERROR;// 如果栈顶指针为空，栈空，出栈失败
	e=S->data;               // 把栈顶结点的数据取出，存入e（引用带回main）
	StackNode *p=S;          // p保存栈顶结点地址，准备释放
	S=S->next;               // 栈顶指针移动到下一个结点（新栈顶）
	delete p;                // 释放原来栈顶结点的堆内存，防止内存泄漏
	return OK;               // 出栈成功返回OK
}

// 获取栈顶元素，不删除结点
SElemType GetTop(LinkStack S){
	if(S!=NULL)              // 如果栈不为空
		return S->data;      // 返回栈顶结点的数据
	else
		return ERROR;        // 栈空返回ERROR
}

// 判断栈是否为空
Status StackEmpty(LinkStack S){
	if(S==NULL)              // 栈顶指针等于NULL代表空栈
		return OK;           // 空栈返回OK
	else
		return ERROR;        // 栈非空返回ERROR
}

// 遍历链栈：从栈顶打印到栈底
void StackTraverse(LinkStack S){
	if(StackEmpty(S)){       // 先判断栈是否为空
		cout<<"栈为空"<<endl;
		return;
	}
	StackNode *p=S;          // p从栈顶开始遍历
	while(p!=NULL){          // p不为空，说明还有结点
		cout<<p->data<<" ";  // 打印当前结点的数据
		p=p->next;           // p移动到下一个结点
	}
	cout<<endl;              // 换行
}

int main(){                 // 主函数，程序入口
	LinkStack S;             // 定义栈顶指针S（StackNode *S）
	InitStack(S);            // 调用函数初始化链栈S
	int n,x,e;               // n：元素个数；x：输入临时变量；e：保存出栈元素
	cin>>n;                  // 输入要入栈的元素数量n
	for(int i=0;i<n;i++){    // 循环n次，依次入栈
		cin>>x;               // 输入一个数字x
		Push(S,x);            // 将x入栈
	}
	cout<<"栈内元素(栈顶→栈底): ";
	StackTraverse(S);        // 遍历打印当前栈
	
	Pop(S,e);                // 出栈，出栈元素存入e
	cout<<"出栈元素："<<e<<endl;
	cout<<"出栈后栈内元素：";
	StackTraverse(S);        // 打印出栈后的栈
	
	SElemType topVal=GetTop(S); // 获取当前栈顶元素
	cout<<"当前栈顶元素："<<topVal<<endl;
	
	return 0;                // 主函数正常结束
}

