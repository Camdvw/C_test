typedef int Status;
typedef struct Node *LinkList;
typedef int ElemType;

Status InitList(LinkList *L);
Status ListEmpty (LinkList L);
Status ClearList(LinkList *L);
int ListLength(LinkList L);
Status GetElem(LinkList L, int i, ElemType *e);
int LocateElem(LinkList L, ElemType e);
Status ListInsert(LinkList *L, int i, ElemType e);
Status ListDelete(LinkList *L, int i, ElemType *e);
Status ListTraverse(LinkList L);
Status CreateListHead(LinkList *L, int n);
Status CreateListTail(LinkList *L, int n);
Status CreateList(LinkList *L);
Status GetMidElem(LinkList L,int *i,ElemType *e);
