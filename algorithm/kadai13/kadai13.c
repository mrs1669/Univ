#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_NO 1 /* 番号を表す定数値 */
#define MEMBER_NAME 2 /* 氏名を表す定数値 */

/*--- 会員データ ---*/
typedef struct{
    int no; /* 番号 */
    char name[20]; /* 氏名 */
} Member;

/*--- ノード ---*/
typedef struct __bnode{
    Member data; /* データ */
    struct __bnode *left; /* 左子ノードへのポインタ */
    struct __bnode *right;/* 右子ノードへのポインタ */
} BinNode;

/*--- 会員の番号の比較関数 ---*/
int MemberNoCmp(const Member *x, const Member *y){
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

/*--- 会員の氏名の比較関数 ---*/
int MemberNameCmp(const Member *x, const Member *y){
    return strcmp(x->name, y->name);
}

/*--- 会員データ（番号と氏名）の表示（改行あり）---*/
void PrintLnMember(const Member *x){
    printf("%d %s\n", x->no, x->name);
}

/*--- 会員データ（番号と氏名）の読込み ---*/
Member ScanMember(const char *message, int sw){
    Member temp;
    printf("%s するデータを入力してください。\n", message);

    if (sw & MEMBER_NO) { printf("番号："); scanf("%d", &temp.no); }
    if (sw & MEMBER_NAME) { printf("氏名："); scanf("%s", temp.name); }

    return temp;
}

/*--- 一つのノードを動的に確保 ---*/
static BinNode *AllocBinNode(void){
    return calloc(1, sizeof(BinNode));
}

/*--- ノードの各メンバに値を設定 ----*/
static void SetBinNode(BinNode *n, const Member *x,
    const BinNode *left, const BinNode *right){
    n->data = *x; /* データ */
    n->left = (BinNode *)left; /* 左子ノードへのポインタ */
    n->right = (BinNode *)right;/* 右子ノードへのポインタ */
}

/*--- 探索 ---*/
BinNode *Search(BinNode *p, const Member *x){
    int cond;
    if (p == NULL)
    return NULL; /* 探索失敗 */
    else if ((cond = MemberNameCmp(x, &p->data)) == 0)
    return p; /* 探索成功 */
    else if (cond < 0)
    return Search(p->left, x); /* 左部分木から探索 */
    else
 return Search(p->right, x); /* 右部分木から探索 */
}