#include <iostream>
#include <cstdlib>
using namespace std;
#define OK 1
#define OVERFLOW -2
#define ERROR 0
typedef int Status;
typedef int ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

//初始化：创建头结点，头结点自环 L->next = L
Status InitList(LinkList &L){
	L=new LNode;
	if(!L) exit(OVERFLOW);
	L->next = L;  //循环链表重点！空表头结点指向自己
	return OK;
}

//销毁链表：释放所有结点（含头结点）
void DestroyList(LinkList &L){
	LNode *p,*q;
	p = L->next;
	while(p != L){    //循环链表终止条件 p不等于头结点L
		q = p->next;
		delete p;
		p = q;
	}
	delete L;   //释放头结点
	L = NULL;
}

//置空链表：保留头结点，删除全部数据结点，变回空循环表
Status ClearList(LinkList &L){
	LNode *p,*q;
	p = L->next;
	while(p != L){
		q = p->next;
		delete p;
		p = q;
	}
	L->next = L; //头结点指向自己，空循环表
	return OK;
}

//按位取值：取第i个元素，位序从1开始
Status GetElem(LinkList L,int i,ElemType &e){
	LNode *p = L->next;
	int j=1;
	while(p != L && j < i){
		p = p->next;
		j++;
	}
	if(p == L || j > i) return ERROR; //i越界
	e = p->data;
	return OK;
}

//按值查找，返回位序；找不到返回0
int LocateElem(LinkList L,ElemType e){
	LNode *p = L->next;
	int j=1;
	while(p != L){
		if(p->data == e) return j;
		p = p->next;
		j++;
	}
	return 0;
}

//按位插入：在第i个位置插入元素e
Status ListInsert(LinkList &L,int i,ElemType e){
	LNode *p = L;
	int j=0;
	//找到第i-1个结点
	while(p->next != L && j < i-1){
		p = p->next;
		j++;
	}
	if(p->next == L && j < i-1) return ERROR;
	LNode *s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

//按位删除：删除第i个结点，e带回删除的值
Status ListDelete(LinkList &L,int i,ElemType &e){
	LNode *p = L;
	int j=0;
	while(p->next != L && j < i-1){
		p = p->next;
		j++;
	}
	if(p->next == L || j>i-1) return ERROR;
	LNode *q = p->next;
	e = q->data;
	p->next = q->next;
	delete q;
	return OK;
}

//打印循环链表
void PrintList(LinkList L){
	LNode *p = L->next;
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

//头插法建立循环单链表，输入n个元素
void ListHeadInsert(LinkList &L,int n){
	InitList(L);
	LNode *s;
	ElemType x;
	for(int i=0;i<n;i++){
		cin>>x;
		s=new LNode;
		s->data=x;
		s->next = L->next;
		L->next = s;
	}
}

//尾插法建立循环单链表，输入n个元素
void ListTailInsert(LinkList &L,int n){
	InitList(L);
	LNode *s,*r=L; //r尾指针，初始指向头结点
	ElemType x;
	for(int i=0;i<n;i++){
		cin>>x;
		s=new LNode;
		s->data=x;
		r->next = s;
		r = s;
	}
	r->next = L; //【重点！尾结点指向头结点，不是NULL】
}

int main()
{
    LinkList L;
    ElemType e;
    Status sta;
    //尾插建循环链表
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
/*核心区别：尾结点 next=L（头结点），不再是NULL;
遍历终止条件p！=L 
*/ 
