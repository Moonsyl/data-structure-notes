#include <iostream>
#include <cstdlib>
using namespace std;
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;//Status是函数返回值类型，取值OK，ERROR，OVERFLOW 
typedef int ElemType;
typedef struct{
	ElemType *elem;//动态数组基址 
	int length;//当前元素个数 
}SqList;
//构造一个空的顺序表L （初始化） 
Status InitList(SqList &L){
	L.elem=new ElemType[MAXSIZE];//C++ new分配数组空间 
	if(!L.elem) exit(OVERFLOW);//内存分配失败 
	L.length=0;//设置空表长度为0 
	return OK;
}
//销毁链表（释放内存） 
void DestroyList(SqList &L){
	delete[] L.elem;//释放数组类型的动态内存 
	L.elem=NULL;
	L.length=0;
} 
//置空（清空元素，不销毁内存）
Status ClearList(SqList &L){
	L.length=0;
	return OK;
} 
//取值，按位序i（不是下标）取元素e
Status GetElem(SqList L,int i,ElemType &e){
	if(i<1||i>L.length){
		return ERROR;
	}
	e=L.elem[i-1];//注意下标从0开始 
	return OK;
} 
//按值查找，找到返回位序，找不到返回0
int LocateElem(SqList L,ElemType e){
	for(int i=0;i<L.length;i++){
		if(L.elem[i]==e){
			return i+1;
		}
	}
	return 0;
} 
//按位插入（高频）
Status ListInsert(SqList &L,int i,ElemType e){
	if(i<1||i>L.length+1){
		//length=3，元素位序：1，2，3；可插入位置1 2 3 4 
		return ERROR;
	}
	if(L.length>=MAXSIZE){
		return OVERFLOW;
	}
	for(int j=L.length-1;j>=i-1;j--){
		//从后往前，把元素向后移动一格，腾出插入位置 
		L.elem[j+1]=L.elem[j];
	}
	L.elem[i-1]=e;//等价于L.elem[j]=e 
	L.length++;
	return OK;
} 
//按位删除（高频）
Status ListDelete(SqList &L,int i,ElemType &e){
	//删除第i个元素，用e带回被删的值 
	if(i<1||i>L.length){
		return ERROR;
	}
	e=L.elem[i-1];
	//后续元素向前覆盖 
	for(int j=i;j<L.length;j++){
		L.elem[j-1]=L.elem[j];
	}
	L.length--;
	return OK;
} 
// 打印顺序表，方便观察结果
void PrintList(SqList L)
{
    if(L.length == 0)
    {
        cout << "顺序表为空！" << endl;
        return;
    }
    for(int k = 0; k < L.length; k++)
    {
        cout << L.elem[k] << " ";
    }
    cout << endl;
}
int main()
{
    SqList L;
    Status sta;
    ElemType e;
    int pos;

    //1.初始化顺序表
    sta = InitList(L);
    if(sta == OK)
        cout << "1.初始化顺序表成功" << endl;

    //2.插入元素：在1,2,3位插入 10,20,30
    ListInsert(L,1,10);
    ListInsert(L,2,20);
    ListInsert(L,3,30);
    cout << "2.插入10,20,30后：";
    PrintList(L);

    //3.取值：取出第2个元素
    sta = GetElem(L,2,e);
    if(sta == OK)
        cout << "3.第2个位序的元素是：" << e << endl;
    else
        cout << "取值失败" << endl;

    //4.按值查找20
    pos = LocateElem(L,20);
    if(pos != 0)
        cout << "4.值20所在位序：" << pos << endl;
    else
        cout << "4.未找到该元素" << endl;

    //5.在第2个位置插入99
    ListInsert(L,2,99);
    cout << "5.在第2位插入99后：";
    PrintList(L);

    //6.删除第3位元素
    sta = ListDelete(L,3,e);
    if(sta == OK)
        cout << "6.删除的元素是：" << e << endl;
    cout << "删除第3位后顺序表：";
    PrintList(L);

    //7.清空顺序表
    ClearList(L);
    cout << "7.执行ClearList置空后：";
    PrintList(L);

    //8.销毁顺序表，释放内存
    DestroyList(L);
    cout << "8.顺序表已销毁" << endl;

    return 0;
}
