#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(type, x, y) do {type t; t = x; x = y; y = t;} while(0)

/*--- 会員データ ---*/
typedef struct {
    int no; /* 番号 */
    char name[20]; /* 氏名 */
} Member;

/*--- 会員の番号の昇順比較関数 ---*/
int AscendingMemberNoCmp(const Member *x, const Member *y){
    return x->no < y->no ? -1: x->no > y->no ? 1: 0;
}

/*--- 会員の番号の降順比較関数 ---*/
int DescendingMemberNoCmp(const Member *x, const Member *y){
    return x->no < y->no ? 1: x->no > y->no ? -1: 0;
}

/*--- 会員の氏名の昇順比較関数 ---*/
int AscendingMemberNameCmp(const Member *x, const Member *y){
    return strcmp(x->name, y->name);
}

/*--- 会員の氏名の降順比較関数 ---*/
int DescendingMemberNameCmp(const Member *x, const Member *y){
    return strcmp(y->name, x->name);
}

/*--- 会員データ（番号と氏名）の表示（改行あり）---*/
void PrintLnMember(const Member *x){
    printf("%d %s\n", x->no, x->name);
}

/*--- 全データの表示 ---*/
void Print(const Member *data, int n){
    int i;
    for(i=0; i < n; i++){
        PrintLnMember(data+i);
    }
}

/* --- クイックソート --- */
/*
void quick(Member *a, int left, int right, int compare(const Member *y, const Member *z)){
    int pl = left;
    int pr = right;
    Member x = a[(pl+pr)/2];
    do {
        while(compare(&x, a+pl)>0) pl++;
        while(compare(a+pr, &x)>0) pr--;
        if ( pl <= pr ){
        swap(Member , a[pl], a[pr]);
        pl++;
        pr--;
        }
    } while(pl <= pr );
    if ( left < pr ) quick(a, left, pr, compare);
    if ( pl < right) quick(a, pl, right, compare);
}
*/

/* --- 配列の先頭，中央，末尾の位置の三つの配列の値を取り出し，それらの値の中央値をもつ要素を枢軸とするクイックソート --- */ // ボツ1
/*
void medianQuick(Member *a, int left, int right, int compare(const Member *y, const Member *z)){
    int pl = left;
    int pr = right;

    if(((a[(pl+pr)/2])-(a[pl]))*((a[(pl+pr)/2])-(a[pr])) <= 0){
        Member x = a[(pl+pr)/2];
    }else if((a[pl]-a[(pl+pr)/2])*(a[pl]-a[pr]) <= 0){
        Member x = a[(pl)];
    }else{
        Member x = a[(pr)];
    }
    do {
        while(compare(&x, a+pl)>0) pl++;
        while(compare(a+pr, &x)>0) pr--;
        if ( pl <= pr ){
        swap(Member , a[pl], a[pr]);
        pl++;
        pr--;
        }
    } while(pl <= pr );
    if ( left < pr ) medianQuick(a, left, pr, compare);
    if ( pl < right) medianQuick(a, pl, right, compare);
}
*/

/* --- 配列の先頭，中央，末尾の位置の三つの配列の値を取り出し，それらの値の中央値をもつ要素を枢軸とするクイックソート --- */ // ボツ2
/*
void medianQuick(Member *a, int left, int right, int compare(const Member *y, const Member *z)){
    int pl = left;
    int pr = right;

    if(((a->no[(pl+pr)/2])-(a->no[pl]))*((a->no[(pl+pr)/2])-(a->no[pr])) <= 0){
        Member x = a->no[(pl+pr)/2];
    }else if((a->no[pl]-a->no[(pl+pr)/2])*(a->no[pl]-a->no[pr]) <= 0){
        Member x = a->no[(pl)];
    }else{
        Member x = a->no[(pr)];
    }
    do {
        while(compare(&x, a+pl)>0) pl++;
        while(compare(a+pr, &x)>0) pr--;
        if ( pl <= pr ){
        swap(Member , a[pl], a[pr]);
        pl++;
        pr--;
        }
    } while(pl <= pr );
    if ( left < pr ) medianQuick(a, left, pr, compare);
    if ( pl < right) medianQuick(a, pl, right, compare);
}
*/

/* --- 配列の先頭，中央，末尾の位置の三つの配列の値を取り出し，それらの値の中央値をもつ要素を枢軸とするクイックソート --- */ 
void medianQuick(Member *a, int left, int right, int compare(const Member *y, const Member *z)){
    int pl = left;
    int pr = right;
    
        Member x = a[(pl+pr)/2];
    do {
        while(compare(&x, a+pl)>0) pl++;
        while(compare(a+pr, &x)>0) pr--;
        if ( pl <= pr ){
        swap(Member , a[pl], a[pr]);
        pl++;
        pr--;
        }
    } while(pl <= pr );
    if ( left < pr ) medianQuick(a, left, pr, compare);
    if ( pl < right) medianQuick(a, pl, right, compare);
}


/*--- シェルソート（第 2 版: h = ..., 13, 4, 1）---*/ // 11講目資料から引用 要素数3以下の時に適用
void shell(Member *a, int n,int compare(const Member *x, const Member *y)){
    int i, j, h;
    for( h = 1; h < n / 9; h = h * 3 +1);
    for( ; h > 0 ; h /= 3)
    for( i = h ; i < n ; i++){
    Member tmp = a[i];
    for( j = i - h ; j >= 0 && compare( a + j ,&tmp)/**order*/ > 0; j -= h)
    a[j + h] = a[ j ];
    a[j + h] = tmp;
    }
}

/*--- メニュー ---*/
typedef enum {
    TERMINATE, ASCEND_NO, ASCEND_NAME,
    DESCEND_NO, DESCEND_NAME, PRINT_ALL
} Menu;

/*--- メニュー選択 ---*/
Menu SelectMenu(void){
    int i, ch;
    char *mstring[] = {"番号で昇順ソート", "名前で昇順ソート", "番号で降順ソート", "名前で降順ソート", "データを表示"};

    do{
    for (i = TERMINATE; i < PRINT_ALL; i++){
        printf("(%2d) %-18.18s ", i + 1, mstring[i]);
        if ((i % 3) == 2){
            putchar('\n');
        }
    }
    printf("( 0) 終了 ：");
    scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT_ALL);

    return (Menu)ch;
}

/*--- メイン ---*/
int main(void){
    Menu menu;
    Member data[] = {{5, "watanabe"}, {7, "satoshi"}, {6, "noyuri"}, {0, "daisuke"}, {0, "motoko"}, {4, "agemi"}, {9, "ito"}, {2, "ohta"}, {1, "takashi"}, {3, "kouji"}};
    int ndata = sizeof(data)/sizeof(data[0]);


    do {
    switch (menu = SelectMenu()) {
        case ASCEND_NO : /* 番号で昇順にソート */
        if(ndata >= 4){
            medianQuick(data, 0, ndata-1, AscendingMemberNoCmp); // 要素数4以上
        }else{
            shell(data, ndata-1, AscendingMemberNoCmp); // 要素数3以下
        }
        break;
        case ASCEND_NAME : /* 名前で昇順にソート */
        if(ndata >= 4){
            medianQuick(data, 0, ndata-1, AscendingMemberNameCmp); // 要素数4以上
        }else{
            shell(data, ndata-1, AscendingMemberNameCmp); // 要素数3以下
        }
        break;
        case DESCEND_NO : /* 番号で降順にソート */
        if(ndata >= 4){
            medianQuick(data, 0, ndata-1, DescendingMemberNoCmp); // 要素数4以上
        }else{
            shell(data, ndata-1, DescendingMemberNoCmp); // 要素数3以下
        }
        break;
        case DESCEND_NAME : /* 名前で降順にソート */
        if(ndata >= 4){
            medianQuick(data, 0, ndata-1, DescendingMemberNameCmp); // 要素数4以上
        }else{
            shell(data, ndata-1, DescendingMemberNameCmp); // 要素数3以下
        }
        break;
        case PRINT_ALL : /* 全データを表示 */
        Print(data, ndata);
        break;
    }
    } while (menu != TERMINATE);
    return 0;
}
