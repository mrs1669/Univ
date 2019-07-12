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
