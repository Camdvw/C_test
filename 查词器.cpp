#include<stdio.h>

#define OK 1
#define ERROR 0
#define TURE 1
#define FLAST 0
#define MAXSIZE 255

typedef int Status;
typedef char String[MAXSIZE+1];

//根据用户输入给数组赋值，当读取到#停止
Status ScanfString(String S) {
    int i = 0;
    char c;
    scanf("%c", &c);
    if(c == '\n')
    scanf("%c", &c);
    while(c != '#') {
        S[++i] = c;
        scanf("%c", &c);
    }
    S[0] = i;
    return OK;
}

Status get_next(String S, int *next) {
    int i, j; //j为数组对应位数（数组下标+1），i为计数器
    j = 1;
    i = 0;
    next[1] = 0;
    while(j < S[0]) {
        if(i == 0 || S[j] == S[i]) {
            next[++j]=++i;
        }else
        i = next[i];
    }
    return OK;
}

int Index(String S, String T, int pos)//S为主串，T为子串
{
    int i = pos;
    int j = 1;
    int next[32];
    get_next(T, next);
    while(i <= S[0] && j <= T[0]) {
        if(j == 0 || S[i] == T[j]) {
            i++;
            j++;
        }else
        {
            j = next[j];
        }
    }
    if(j > T[0])
    return i-T[0];
    else
    return 0;
}

int main() {
    int x = -1;
    int i = 0;
    String S;
    String T;
    printf("请输入文本:\n");
    ScanfString(S);
    printf("%d", S[0]);
    printf("请输入待查找单词:\n");
    ScanfString(T);
    while(1) {
        i++;
        x = Index(S, T, x+1);
        if(!x)
        break;
        printf("单词第%d次出现在文本中第%d个到第%d个字符间\n", i, x-1, x+T[0]);
    }

    return OK;
}
