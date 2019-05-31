//
//  kadai7.c
//  algorithm
//
//  Created by Takumi Muraishi on 2019/05/31.
//  Copyright © 2019 Takumi Muraishi. All rights reserved.
//

#include  <stdio.h>
#include  <stdlib.h>

typedef struct {/*---キューを実現する構造体---*/
    int max;  /* キューの容量*/
    int num;  /* 現在の要素数*/
    int front;/* 先頭要素カーソル*/
    int rear; /* 末尾要素カーソル*/
    char *que; /* キュー本体（の先頭要素へのポインタ）*/
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
int Enque(StringsQueue *q, int x){
    if (q->num >= q->max){
        return -1;/* キューは満杯*/
    }else{
        q->num++;
        q->que[q->rear++] = x;
        if(q->rear== q->max){
            q->rear = 0;
        }return 0;
    }
}

/*---キューからデータをデキュー---*/
int Deque(StringsQueue *q, int *x){
    if (q->num <= 0){/* キューは空*/
        return -1;
    }else{
        q->num--;
        *x = q->que[q->front++];
        if(q->front == q->max){
            q->front = 0;
        }return 0;
    }
}

/*---キューからデータをピーク---*/
int Peek(const StringsQueue *q, int *x){
    if(q->num <= 0){
        return -1;
    }
    *x = q->que[q->front];
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
        printf("%d ", q->que[(i + q->front) % q->max]);
    }
    putchar('\n');
}

int Count(StringsQueue *q , char *x){
    return 0;
}

int main(void){
    StringsQueue  que;
    if (Initialize(&que, 5) == -1){
        puts("キューの生成に失敗しました。");
        return 1;
    }

    while (1){
        int  m, x;
        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1)エンキュー　(2)デキュー　(3)ピーク　(4)表示　(5)パターンの計数　(0)終了：");
        scanf("%d", &m);
        if (m == 0){
            break;
        }

        switch(m){
            case 1:
                printf("データ：");   scanf("%d", &x);
                if (Enque(&que, x) == -1){
                    puts("\aエラー:データのエンキューに失敗しました。");
                }
                break;
            
            case 2:
                if(Deque(&que, &x) == -1){
                    puts("\aエラー:デキューに失敗しました。");
                }else{
                    printf("デキューしたデータは%dです。\n", x);
                }
                break;
            
            case 3:/* ピーク*/
                if(Peek(&que, &x) == -1){
                    puts("\aエラー：ピークに失敗しました。");
                }else{
                    printf("ピークしたデータは%dです。\n", x);
                }
                break;
            
            case 4:/* 表示*/
                Print(&que);
                break;

//            case 5:/* 表示*/
//                if(Count(StringsQueue *q , char *x)) == 0{
//                  puts("\aパターンは存在しません");
//            }else{
//              printf("見つかったパターンの数は%dです\n", x);
//        }
//      break;
        }
    }
    Terminate(&que);
    return 0;
}
