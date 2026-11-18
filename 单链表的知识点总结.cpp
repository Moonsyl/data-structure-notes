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
/*
1.struct LNode 定义结构体，名字叫LNode，
用来表示链表的一个结点
2.ElemType data 结点的数据域，
用来存放结点保存的值
(ElemType是前面 typedef 好的 int)
3.struct LNode *next 指针域，
是一个struct LNode类型的指针，
存下一个结点的地址，把链表串起来
4.typedef作用：给struct LNode起别名
LNode等价于struct LNode，代表--单个结点
LinkList等价于struct LNode *，
代表--结点指针，习惯用来表示整个链表（链表头指针）
一句话记：LNode是结点，LinkList是结点指针（链表）
*/
//初始化（创建头结点） 
Status InitList(LinkList &L){
	L=new LNode;//新建头结点 
	if(!L) exit(OVERFLOW);
	L->next=NULL;//头结点next置空，空表 
	return OK;
} 
//销毁链表（释放全部结点）
void DestroyList(LinkList &L){
	LNode *p,*q;
	p=L;//p一开始 = L，p指向【头结点】！
	while(p){//while(p)等价 while(p != NULL)：p不为空就循环
		q=p->next;//q保存p的下一个结点地址（先把下一站存起来，不然delete p之后找不到了）
		delete p;//释放p当前指向的结点内存
		p=q;//p移动到刚才q保存的下一个结点
	}
	L=NULL;//把头指针置空，防止野指针
} 
//置空（保留头结点，删除所有数据结点）
Status ClearList(LinkList &L){
	LNode *p,*q;
	p=L->next;//p指向第一个数据结点
	while(p){
		q=p->next;
		delete p;
		p=q;
	}
	L->next=NULL;//头结点next置空，只剩头结点
	return OK;
} 
//按位取值（第i个元素，位序从1开始）
Status GetElem(LinkList L,int i,ElemType &e){
	LNode *p=L->next;
	/*L是头指针，L指向头结点，
	L->next是头结点里的next指针，
	存放首元结点地址
	即p一开始就指向首元结点 
	*/ 
	int j=1;
	while(p&&j<i){//p不为空且没走到i
		p=p->next;
		j++;
	}
	if(!p||j>i) return ERROR;//i非法
	e=p->data;
	return OK;
} 
//按值查找，返回位序（找不到返回0）
int LocateElem(LinkList L,ElemType e){
	LNode *p=L->next;
	int j=1;
	while(p){
		if(p->data==e) return j;
		p=p->next;
		j++;
	}
	return 0;
} 
//按位插入（在第i个位置插入e，高频）
Status ListInsert(LinkList &L,int i,ElemType e){
	LNode *p=L;
	int j=0;
	//找到第i-1个结点p
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1) return ERROR;//i不合法
	LNode *s=new LNode;
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
} 
//按位删除（删除第i个结点，e带回值，高频）
Status ListDelete(LinkList &L,int i,ElemType &e){
	LNode *p=L;
	int j=0;
	//找到i-1号结点
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!(p->next)||j>i-1) return ERROR;
	LNode *q=p->next;//q是待删结点
	e=q->data;
	p->next=q->next;
	delete q;
	return OK;
} 
//打印链表
void PrintList(LinkList L){
	LNode *p=L->next;
	if(p==NULL){
		cout<<"链表为空"<<endl;
		return;
	}
	while(p){
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
} 
//头插法，读入n个元素，用头插法建立单链表
//输入顺序10 20 30
//结果链表30 20 10 
void ListHeadInsert(LinkList &L,int n){
	InitList(L);
	LNode *s;
	ElemType x;
	for(int i=0;i<n;i++){
		cin>>x;
		s=new LNode;
		s->data=x;
		s->next=L->next;
		L->next=s;
	}
} 
//尾插法，读入n个元素，尾插建立单链表
//输入顺序10 20 30
//结果链表10 20 30 
void ListTailInsert(LinkList &L,int n){
	InitList(L);//创建头结点
	LNode *s,*r=L;//r为尾指针，一开始指向头结点
	ElemType x;
	for(int i=0;i<n;i++){
		cin>>x;
		s=new LNode;//新建结点s
		s->data=x;
		r->next=s;//原来尾结点的next指向新结点s
		r=s;//尾指针r向后移动，r现在变成新的尾结点
	}
	r->next=NULL;//最后尾结点next置NULL！！【千万不能漏】
} 
int main()
{
    LinkList L;
    ElemType e;
    Status sta;
    //尾插建表
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

