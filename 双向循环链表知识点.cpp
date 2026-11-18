#include <iostream>
#include <cstdlib>
using namespace std;
#define OK 1
#define OVERFLOW -2
#define ERROR 0
typedef int Status;
typedef int ElemType;

//双向循环链表结点定义
typedef struct DNode{
	ElemType data;
	struct DNode *prior;  //前驱指针，指向前一个结点
	struct DNode *next;   //后继指针，指向后一个结点
}DNode,*DLinkList;

//初始化：创建头结点，自环
Status InitList(DLinkList &L){
	L = new DNode;
	if(!L) exit(OVERFLOW);
	L->next = L;
	L->prior = L;
	return OK;
}

//销毁链表：释放全部结点（含头结点）
void DestroyList(DLinkList &L){
	DNode *p,*q;
	p = L->next;
	while(p != L){
		q = p->next;
		delete p;
		p = q;
	}
	delete L;
	L = NULL;
}

//置空链表：保留头结点，删除所有数据结点，变回空双向循环表
Status ClearList(DLinkList &L){
	DNode *p,*q;
	p = L->next;
	while(p != L){
		q = p->next;
		delete p;
		p = q;
	}
	L->next = L;
	L->prior = L;
	return OK;
}

//按位取值：取第i个元素，位序从1开始
Status GetElem(DLinkList L,int i,ElemType &e){
	DNode *p = L->next;
	int j=1;
	while(p != L && j < i){
		p = p->next;
		j++;
	}
	if(p == L || j>i) return ERROR;
	e = p->data;
	return OK;
}

//按值查找，返回位序，找不到返回0
int LocateElem(DLinkList L,ElemType e){
	DNode *p = L->next;
	int j=1;
	while(p != L){
		if(p->data == e) return j;
		p = p->next;
		j++;
	}
	return 0;
}

//【重点】按位插入：在第i个位置插入e
Status ListInsert(DLinkList &L,int i,ElemType e){
	DNode *p = L;
	int j=0;
	//找到i-1位置结点p
	while(p->next != L && j < i-1){
		p = p->next;
		j++;
	}
	if(p->next == L && j < i-1) return ERROR;
	DNode *s = new DNode;
	s->data = e;

	//双向链表插入4步顺序！考试默写重点
	s->prior = p;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return OK;
}

//【重点】按位删除：删除第i个结点，e带回值
Status ListDelete(DLinkList &L,int i,ElemType &e){
	DNode *p = L;
	int j=0;
	while(p->next != L && j < i-1){
		p = p->next;
		j++;
	}
	if(p->next == L || j>i-1) return ERROR;
	DNode *q = p->next;  //待删结点q
	e = q->data;

	//双向链表删除2步
	p->next = q->next;
	q->next->prior = p;
	delete q;
	return OK;
}

//打印双向循环链表
void PrintList(DLinkList L){
	DNode *p = L->next;
	if(p == L){
		cout<<"链表为空"<<endl;
		return;
	}
	while(p != L){
		cout<<p->data<<" ";
		p = p->next;
	}
	cout<<endl;
}

//头插法建立双向循环链表
void ListHeadInsert(DLinkList &L,int n){
	InitList(L);
	DNode *s;
	ElemType x;
	for(int i=0;i<n;i++){
		cin>>x;
		s = new DNode;
		s->data = x;
		//头插
		s->prior = L;
		s->next = L->next;
		L->next->prior = s;
		L->next = s;
	}
}

//尾插法建立双向循环链表
void ListTailInsert(DLinkList &L,int n){
	InitList(L);
	DNode *s,*r = L; //r尾指针，初始指向头结点
	ElemType x;
	for(int i=0;i<n;i++){
		cin>>x;
		s = new DNode;
		s->data = x;
		//接到尾部
		s->prior = r;
		s->next = L;
		L->prior = s;
		r->next = s;
		r = s;
	}
}

int main()
{
    DLinkList L;
    ElemType e;
    Status sta;

    cout << "尾插输入3个数字：";
    ListTailInsert(L,3);
    cout << "链表："; PrintList(L);

    sta = GetElem(L,2,e);
    if(sta == OK) cout << "第2个元素：" << e << endl;
    int pos = LocateElem(L,e);
    cout << e << "的位序：" << pos << endl;

    ListInsert(L,2,99);
    cout << "第2位插入99："; PrintList(L);

    ListDelete(L,3,e);
    cout << "删除第3位，被删值=" << e << "，链表："; PrintList(L);

    ClearList(L);
    cout << "Clear置空后："; PrintList(L);
    DestroyList(L);
    cout << "销毁完成"<<endl;
    return 0;
}

