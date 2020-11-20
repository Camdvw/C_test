#include <stdio.h>
#include <stdlib.h>
#include"LinkList.h"

int main() {
    printf("*************************************************\n");
    printf("1：清空原有链表，跟据输入创建链表\n");
    printf("2：清空原有链表，随机生成一个有n个数据的链表\n");
    printf("3：在指定位置插入一个数据\n");
    printf("4：删除指定位置的一个数据\n");
    printf("5：遍历输出链表内容\n");
    printf("6：最快速度找出链表的中间位序并输出其值\n");
    printf("7：输出链表元素个数\n");
    printf("8：输出第一个与指定数值相同的数据元素的位序\n");
    printf("9：输出指定位置的数据\n");
    printf("0：结束程序\n");
    printf("*************************************************\n\n");

    int x, n, i;
    ElemType e;
    Status y = 1;
    LinkList L;
    InitList(&L);

    while(y) {
        printf("请输入您要执行的选项：");
        scanf("%d", &x);
        switch(x) {
            case 1:
	            y = ClearList(&L);
	            y = CreateList(&L);
	            break;
	        case 2:
	            ClearList(&L);
	            printf("请输入您所需的随机链表长度：");
	            scanf("%d", &n);
	            y = CreateListTail(&L, n);
	            printf("%d", y);
	            break;
	        case 3:
	            printf("请输入您要插入的数据及其插入的位序：");
	            scanf("%d %d", &e, &i);
	            y = ListInsert(&L, i, e);
	            break;
	        case 4:
	            printf("请输入您要删除的数据位序：");
	            scanf("%d", &i);
	            y = ListDelete(&L, i, &e);
	            break;
	        case 5:
	            if(ListEmpty(L) == 1)
	            printf("该链表为空表\n");
	            else
	            ListTraverse(L);
	            break;
	        case 6:
	            if(ListEmpty(L) == 1)
	            printf("该链表为空表\n");
	            else {
	                GetMidElem(L, &i, &e);
	                printf("该链表的中间位序为%d，其值为%d", i, e);
	            }
	            break;
	        case 7:
	            i = ListLength(L);
	            printf("该链表长度为：%d\n", i);
	            break;
	        case 8:
	            if(ListEmpty(L) == 1)
	            printf("该链表为空表\n");
	            else {
	                printf("请输入您要查找的值：");
	                scanf("%d", &e);
	                i = LocateElem(L, e);
	                printf("第一个与指定数值相同的数据元素的位序是(0表示无结果)：%d", i);
	            }
	            break;
	        case 9:
	            if(ListEmpty(L) == 1)
	            printf("该链表为空表\n");
	            else {
	                printf("请输入需要输出的元素位序：");
	                scanf("%d", &i);
	                y = GetElem(L, i, &e);
	                printf("对应位序的数据为：%d", e);
	            }
	        	break;
	        case 0:
	            goto out;
	        default:
	            printf("输入错误\n");
        }
        if(!y)
        printf("出错");
    }
    out:

    return 0;
}
