/* 再帰に対する理解を深めるための真に再帰的な関数 3 */

#include <stdio.h>
#include <string.h>
#define String_Max 81

/*--- 真に再帰的な関数 recur3 ---*/
/*
void recur3(char *st){
    int n = strlen(st);

    if( n > 0 ){
        recur3( st + 1 );
        printf("%c", *st);
        if( n > 1 ){
            recur3( st + 2 );
        }else{
        recur3( st + 1 );
        }
    }
}
*/

/*--- 非再帰的な関数 notRecur3 ---*/
void notRecur3(char *st){
    int n = strlen(st);

    while(n > 0){
        if(n>1){
            printf("%c", *(st+n-1));
            n--;
        }else{
            printf("%c", *(st+n));
            n--;
        }
    }


}


int main(void){
    char  x[String_Max];


    printf("文字列をを入力せよ:"); 
    scanf("%s", x);
    notRecur3(x);
    printf("\n");
    return (0);
}