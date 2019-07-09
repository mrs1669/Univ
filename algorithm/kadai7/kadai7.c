//
//  kadai7.c
//  algorithm
//
//  Created by Takumi Muraishi on 2019/05/31.
//  Copyright © 2019 Takumi Muraishi. All rights reserved.
//

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <limits.h>
#define String_Max 81

typedef struct {/*---キューを実現する構造体---*/
    int max;  /* キューの容量*/
    int num;  /* 現在の要素数*/
    int front;/* 先頭要素カーソル*/
    int rear; /* 末尾要素カーソル*/
    char **que; /* キュー本体（の先頭要素へのポインタ）*/
} StringsQueue;

/*---キューの初期化---*/
int Initialize(StringsQueue *q, int max){
    q->num = q->front = q->rear = 0;
    if((q->que = calloc(max, sizeof(int))) == NULL){
        q->max = 0;/* 配列の確保に失敗*/
        return -1;
    }
    q->max = max;
    return 0;
}

/*---キューの後始末---*/
void Terminate(StringsQueue *q){
    if (q->que != NULL){
        free(q->que);/* 配列を解放*/
        q->max = q->num = q->front = q->rear = 0;
    }
}

/*---キューにデータをエンキュー---*/
int Enque(StringsQueue *q, char *x){
    if (q->num >= q->max){
        return -1;/* キューは満杯*/
    }else{
        q->num++;
        if((q->que[q->rear] = calloc(strlen(x)+1, sizeof(char))) == NULL){
        return -1;
        }
        strcpy(q->que[q->rear++], x);
        if(q->rear== q->max){
            q->rear = 0;
        }return 0;
    }
}

/*---キューからデータをデキュー---*/
int Deque(StringsQueue *q, char *x){
    if (q->num <= 0){/* キューは空*/
        return -1;
    }else{
        q->num--;
        strcpy(x, q->que[q->front++]);
        if(q->front == q->max){
            q->front = 0;
        }return 0;
    }
}

/*---キューからデータをピーク---*/
int Peek(const StringsQueue *q, char *x){
    if(q->num <= 0){
        return -1;
    }
    strcpy(x, q->que[q->front]);
    return 0;
}

/*---キューの容量---*/
int Capacity(const StringsQueue *q){
    return (q->max);
}

/*---キューに蓄えられているデータ数---*/
int Size(const StringsQueue *q){
    return (q->num);
}

/*---全データの表示---*/
void Print(const StringsQueue *q){
    int i;

    for(i = 0; i < q->num; i++){
        printf("%s ", q->que[(i + q->front) % q->max]);
    }
    putchar('\n');
}



/*--- Boyer-Moore 法による文字列探索 ---*/
char *bm_match(char *pat , char *txt){
char *pt; /* txt をなぞるカーソル */
char *pp; /* pat をなぞるカーソル */
int txt_len = strlen(txt); /* txt の文字数 */
int pat_len = strlen(pat); /* pat の文字数 */
int skip[UCHAR_MAX + 1]; /* スキップテーブル */
int i;

for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */
skip[i] = pat_len;
for (pp = pat; *pp != '\0'; pp++)
skip[*pp] = strlen(pp) - 1;
skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数 */
pt = txt + pat_len - 1; /* pat の末尾と比較する txt の文字を決定 */
while ( pt < txt + txt_len) { /* txt の比較する文字の位置が txt の末尾を越えるまで */
pp = pat + pat_len - 1; /* pat の最後の文字に着目 */
while (*pt == *pp) {
if (pp == pat) return (pt); /* 一致した文字がパターンの最初の文字になれば終了 */
pp--;
pt--;
}
pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);
}
return (NULL);
}



int Count(StringsQueue *q , char *x){
    int count = 0;
    char *pat, *pt;
    pat = x;
    int i;
    for(i=0;i<q->num;i++){
        pt = q->que[(i + q->front)% q->max];
        while((pt = bm_match(pat, pt))!= NULL) {
            count++;
            pt++;
        }
    }

    return count;
}

int main(void){
    
    StringsQueue  que;
    if (Initialize(&que, 8) == -1){
        puts("キューの生成に失敗しました。");
        return 1;
    }

    while (1){
        int count;
        int  m;
        char x[String_Max];
        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1)エンキュー　(2)デキュー　(3)ピーク　(4)表示　(5)見つかったパターンの数 (0)終了：");
        scanf("%d", &m);
        if (m == 0){
            break;
        }

        switch(m){
            case 1:
                printf("データ：");   scanf("%s", x);
                if (Enque(&que, x) == -1){
                    puts("\aエラー:データのエンキューに失敗しました。");
                }
                break;
            
            case 2:
                if(Deque(&que, x) == -1){
                    puts("\aエラー:デキューに失敗しました。");
                }else{
                    printf("デキューしたデータは%sです。\n", x);
                }
                break;
            
            case 3:/* ピーク*/
                if(Peek(&que, x) == -1){
                    puts("\aエラー：ピークに失敗しました。");
                }else{
                    printf("ピークしたデータは%sです。\n", x);
                }
                break;
            
            case 4:/* 表示*/
                Print(&que);
                break;

            case 5:/* 表示*/
                scanf("%s",x);
                if((count = Count(&que , x)) == 0){ 
                    puts("パターンは存在しません");
                }else{
                    printf("見つかったパターンの数は%dです\n", count);
                }
                break;
        }
    }
    Terminate(&que);
    return 0;
}
