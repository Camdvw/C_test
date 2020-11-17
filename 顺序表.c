#include<stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
//函数结果状态值
#define MAXSIZE 20//存储空间初始分配量
typedef int ElemType;//ElemType类型可根据实际情况改变，这里假定为int类型
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SqList;

typedef int Status;//Status是函数的类型，其值为函数结果状态代码

//初始化顺序表
Status InitList(SqList *L)
{
    L->length=0;
    return OK;
}

//判定顺序表是否为空表
//操作：若为空表返回TRUE，否则返回FALSE
Status ListEmpty(SqList L)
{
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

//将顺序表置空
//操作：将L重置为空表
Status ClearList(SqList *L)
{
    L->length=0;
    return OK;
}

//获取顺序表当前长度
//操作：返回L中数据元素个数
int ListLength(SqList L)
{
    return L.length;
}

//在指定位置插入元素
//操作：在L中第i个元素之前插入一个新元素e，L的长度加1
Status ListInsert(SqList *L,int i,ElemType e)
{
    //判定L是否还有空余空间
    if(L->length==MAXSIZE)
        return ERROR;
    //判定i是否合理
    if(i<1||i>L->length+1)
        return ERROR;
    //判定i是否在表尾
    if(i<=L->length)
    {
        //第i位之后均后移一位，注意：第i为元素的值==L->data[i-1]
        for(int j=L->length-1;j>=i-1;j--)
            L->data[j+1]=L->data[j];
    }
    //插入新元素
    L->data[i-1]=e;
    //易遗漏点
    L->length++;
    return OK;
}

//删除指定元素
//操作：将L中第i个元素的值传给e后删除，L的长度减1
Status ListDelete(SqList *L,int i,ElemType *e)
{
    //判定是否为空表
    if(L->length==0)
        return ERROR;
    //判定i是否合理
    if(i<1||i>L->length)
        return ERROR;
    *e=L->data[i-1];
    //第i位后均前移一位
    if(i<L->length)
    {
        for(int j=i-1;j<L->length-1;j++)
            L->data[j]=L->data[j+1];
    }
    //易遗漏点
    L->length--;
    return OK;
}

//获取指定元素
//操作：用e返回L中第i个数据元素的值
Status GetElem(SqList L,int i,ElemType *e)
{
    //先判定L内是否有第i个元素
    if(L.length=0||i<1||i>L.length-1)
        return ERROR;
    *e=L.data[i-1];
    return OK;
}

//找到第一个满足指定关系的元素的位置
//操作：返回L中第1个与e满足关系的元素位序，若不存在该元素，则返回0，此处以"与e相等"为条件
int LocateElem(SqList L,ElemType e)
{
    int i;
    //判定是否为空表
    if(L.length==0)
        return ERROR;
    for(i=0;i<L.length;i++)
    {
        if(L.data[i]==e)
            break;
    }
    if(i==L.length)
        return 0;
    return i+1;
}

//遍历输出顺序表的数据元素
//操作：输出L中每一个元素的值
Status ListTraverse(SqList L)
{
    if(L.length==0)
        return ERROR;
    for(int i=0;i<L.length;i++)
        printf("%d\t",L.data[i]);
    printf("\n");
    return OK;
}

//求两顺序表交集
//操作：将所有Lb中有但La中没有的元素插入La中
Status unionL(SqList *La,SqList Lb)
{
    int Lalangth,Lblangth;
    ElemType e;
    
    Lalangth=ListLength(*La);
    Lblangth=ListLength(Lb);
    //依次读取Lb中的元素与La比对
    for(int i=1;i<Lblangth;i++)
    {
        GetElem(Lb,i,&e);
        if(!LocateElem(*La,e))
            //将e插入到La表尾，并使Lalangth+1
            ListInsert(La,++Lalangth,e);
    }
    return OK;
}


int main()
{
    SqList L;
    SqList K;
    ElemType e;
    
    //初始化顺序表
    InitList(&L);
    InitList(&K);
    
    //在表L的表尾依次插入1~10
    for(int j=1;j<=10;j++)
    {
        ListInsert(&L,j,j);
    }
    
    //在表K的表头依次插入
    for(int k=30;k>=0;k-=2)
    {
        ListInsert(&K,1,k);
    }
    
    //输出表L的第6个元素
    GetElem(L,6,&e);
    printf("表L的第6个元素=%d\n",e);
    
    //删除表L的第6个元素
    ListDelete(&L,6,&e);
    
    //输出表L元素个数
    printf("表L有%d个元素\n",ListLength(L));
    
    //将所有K中有但L中没有的元素插入L中
    unionL(&L,K);
    
    //遍历输出表L的数据元素
    printf("遍历输出L得：\n");
    ListTraverse(L);
    
    
    
    //将表L置空
    ClearList(&L);
    
    //判定表L是否为空表
    printf("重置后，L是否为空：%d（1：是，2：否）\n",ListEmpty(L));

    return OK;
       
}
