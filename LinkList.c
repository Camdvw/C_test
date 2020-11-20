#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include"LinkList.h"

#define OK 1
#define ERROR 0
#define TURE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList;

//初始化单链表
Status InitList(LinkList *L) {
    //创建头结点，为头结点申请空间
    *L = (LinkList)malloc(sizeof(Node));
    //判定存储分配是否成功
    if(!(*L))
    return ERROR;
    (*L)->next = NULL; //()的优先级高于->，(*L)->next既是强调是*L是一个整体

    return OK;
}

//判定单链表是否为空表
//操作：如L为空表返回TRUE，否则返回FALSE
Status ListEmpty (LinkList L) {
    if(L->next)
    return FALSE;
    else
    return TURE;
}

//将单链表置空
//操作：将L重置为空表
Status ClearList(LinkList *L) {
    LinkList p, r;
    //由于*L是头结点的位置，须保留，故从(*L)->next开始删
    p = (*L)->next;

    while(p) {
        //先将p->next交给r再删除结点，保证不丢失链表的后继
        r = p->next;
        free(p); //释放p所在当前结点的内存
        p = r;
    }
    //当将所有结点释放后，别忘了让头结点指向空
    (*L)->next = NULL;

    return OK;
}

//获取链表的元素个数
//操作：返回L中数据元素个数
int ListLength(LinkList L) {
    int i = 0;
    LinkList p;

    p = L->next; //注意不能将头结点算在内
    //如果改成是while(p->next)会导致最后一个结点不会别计入
    while(p) {
        p = p->next;
        i++;
    }
    return i;
}

//获取指定元素
//操作：用e返回L中第i个数据元素
Status GetElem(LinkList L, int i, ElemType *e) {
    int j = 1; //由于p=L->next;是从第一个结点开始，则j需从1开始计数
    LinkList p;
    p = L->next;
    //当p不为空或计数器j还没等于i时，循环继续
    while(p && j < i) {
        p = p->next;
        j++;
    }
    //判定第i个元素是否存在
    if(j > i||!p)
    return ERROR;
    *e = p->data;

    return OK;
}

//找到第一个满足指定关系的元素的位置
//操作：返回L中第1个与e满足关系的元素位序，若不存在该元素，则返回0，此处以"与e相等"为条件
int LocateElem(LinkList L, ElemType e) {
    int i = 0;
    LinkList p;
    p = L->next;

    while(p) {
        i++;
        //不可以先p=p->next再判定，否则i会比实际小1
        if(p->data == e)
        return i;
        p = p->next;
    }

    return 0;
}

//在指定位置插入元素
//操作：在L中第i个位置之前插入新的数据元素e
Status ListInsert(LinkList *L, int i, ElemType e) {
    //要使插入后的元素在链表中排第i位，则需从第i-1位和第i位之间插入，故重点应放在第i-1位元素上
    int j = 1;
    LinkList p, s;
    p=*L; //不同于GetElem函数，p需从头结点开始，才能使p最终停留在第i-1位元素上

    while(p && j < i) {
        p = p->next;
        j++;
    }
    //插入操作只需在意前一位是否存在，故需判定第i-1个元素是否存在
    if(!p || j > i)
    return ERROR;
    //为新结点s申请动态内存
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    //以下两步不可调换，若先p->next=s;，会导致丢失链表后继
    s->next = p->next;
    p->next = s;

    return OK;
}

//删除指定位置的元素
//操作：删除L中第i个数据元素，并用e返回其值
Status ListDelete(LinkList *L, int i, ElemType *e) {
    //虽然要删除的元素是第i个元素，但是要把重点放在第i-1个元素上
    int j = 1;
    LinkList p, q;
    p=*L; //定义p的作用是找到第i-1个元素，故p需从头结点开始
    //不同于ListInsert函数，删除操作更在意要删除的元素是否存在，故要以p->next是否存在为判定标准
    while(p->next && j < i) {
        j++;
        p = p->next;
    }
    //同理，要以p->next是否存在为判定标准
    if(!(p->next) || j > i)
    return ERROR;
    //以下两步不可调换，否则会导致丢失后继
    q = p->next; //此时q为第i个元素，是需要被删除的元素
    p->next = q->next;
    *e = q->data;
    free(q);

    return OK;
}

//遍历输出链表内容
//操作：依次对L的每个数据元素输出
Status ListTraverse(LinkList L) {
    LinkList p;
    p = L->next;

    while(p) {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");

    return OK;
}

//头插法产生n个随机值的链表
//操作：产生n个带随机元素值的结点，依次从头结点之后的位置插入形成链表L
Status CreateListHead(LinkList *L, int n) {
    int i;
    LinkList p;
    srand(time(0)); //初始化随机数
    //先建立一个空链表
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;

    for(i = 1; i <= n; i++) {
        p = (LinkList)malloc(sizeof(Node)); //生成新结点
        p->data = rand()%10+1; //随机生成一个10以内的数字
        p->next = (*L)->next;
        (*L)->next = p; //插入到表头
    }

    return OK;
}

//尾插法产生n个随机值的链表
//操作：产生n个带随机元素值的结点，依次接到表尾的位置形成链表
Status CreateListTail(LinkList *L, int n) {
    int i;
    LinkList p, q;
    srand(time(0));

    *L = (LinkList)malloc(sizeof(Node));
    q=*L;

    for(i = 1; i <= n; i++) {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand()%10+1;
        q->next = p;
        q = p;
    }
    q->next = NULL; //可以在最后由q->next = NULL;来使表尾指向空，可对空表和非空表的情况统一处理，更为简洁

    return OK;
}

//根据用户输入创建链表
//操作：每读取一个用户输入的数值便创建一个结点接在上一个结点之后，如用户输入-1，则链表结束
Status CreateList(LinkList *L) {
    int x = 1;
    LinkList p, q;

    *L = (LinkList)malloc(sizeof(Node));
    q=*L;
    printf("请输入要存储的数据(输入-1即为停止存储)：");
    while(x != -1) {
        scanf("%d", &x);
        if(x == -1)
        break;
        p = (LinkList)malloc(sizeof(Node));
        q->next = p;
        p->data = x;
        q = p;
    }
    q->next = NULL;

    return OK;
}

//最快速度找出链表的中间位序并输出其值
//操作：用快慢指针找出链表的中间位序交给i，将其值交给e
Status GetMidElem(LinkList L, int *i, ElemType *e) {
    int j = 0;
    LinkList fast, slow;
    fast = L;
    slow = L;

    while(fast->next != NULL) {
        if(fast->next->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }else
        {
            fast = fast->next; //保证fast指向最后一个元素，使程序跳出while循环
        }
        j++;
    }

    *i = j;
    *e = slow->data;

    return OK;
}
