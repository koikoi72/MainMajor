//AddToRESULTで数値が格納されていない。配列におけるポインタの振る舞いがどうなっているか調べる #note
/*　#NOTE
「*と&、.と->の違いについて」 
TUPLE t; //TUPLE型変数t
TUPLE *p; //TUPLE*型変数p

t; //TUPLE型
p; //TUPLE*型
*p; //TUPLE型

*p.key; == p->key;
*p.val == p->val; //実体の数値を参照するときは「.」、ポインタの数値を参照するときは「->」を使う！

&t; //TUPLE*型
&(*p); //TUPLE*型
*/

/* #NOTE
「resultの先頭について」
mallocで領域を確保したあと、初期化しなければ
自動的にresultの先頭の実体には0が代入される

実行時にrkey=rval=sval=skey=0となっていたのは初期化していなかったため

「PrintRESULT関数について」
whileループにおいてresult->nextがNULLのときはwhile文が実行されず、
最後尾が表示されない。現在のresultの値を参照するように（以下のPrintRESULT関数参照）
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 10 
#define length BUFSIZ

typedef struct _TUPLE {
  int key;
  int val;
  //struct _TUPLE* next;
}TUPLE;


typedef struct _RESULT {
  int rkey, skey;
  int rval, sval;
  struct _RESULT* next;
}RESULT;

RESULT* AddToRESULT(RESULT* result, TUPLE* R, TUPLE* S){
  RESULT* node = (RESULT*)malloc(sizeof(RESULT));
  node->rkey = R->key;
  node->skey = S->key;
  node->rval = R->val;
  node->sval = S->val; //.と->の違いがわからない
  node->next = NULL;

  RESULT* p = result;
  if(p == NULL) {
    return node;
  }
  else {
    while(p->next != NULL) {
      p = p->next;
    } p->next = node;
    return result;
  }
}

void PrintRESULT(RESULT* result) {
  if(result == NULL) return;
  while(result != NULL){
    printf("rkey: %d, rval: %d, skey: %d, sval: %d\n", result->rkey, result->rval, result->skey, result->sval);
    result = result->next;
  }
  
}   

void JoinKey(TUPLE R[N], TUPLE S[N]) {
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  result = NULL;
  for(int i = 0; i < N; i++){
    result = AddToRESULT(result, &R[i], &S[i]);
  }
  PrintRESULT(result);
}
  
void JoinVal(TUPLE R[N], TUPLE S[N]) {
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  result = NULL;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(R[i].val == S[j].val) result = AddToRESULT(result, &R[i], &S[j]);
    }
    //先頭へ戻る。同じ過ちは、繰り返しません
  }
  PrintRESULT(result);
}

void GenArray(TUPLE tuple[N]){
  for(int i = 0; i < N; i++){
    tuple[i].key = i;
    tuple[i].val = rand() % N;
  }
}

void PrintData(TUPLE R[N], TUPLE S[N], char c1[], char c2[]){
  if(strcmp(c1, "join") == 0){
    if(strcmp(c2, "key") == 0) {
      JoinKey(R, S);
    }
    else if(strcmp(c2, "val") == 0) JoinVal(R, S);
    else printf("****!!\n");
  } else printf("****!!\n");
}

int main() {
  TUPLE R[N], S[N];
  GenArray(R); GenArray(S);
  while(1){
    char c1[length] = {'\0'};
    char c2[length] = {'\0'};
    char readLine[length] = {'\0'};
    printf("CMD > ");
    fgets(readLine, length, stdin);
    sscanf(readLine, "%s %s", c1, c2);
    //printf("%s", c2);
    PrintData(R, S, c1, c2);
    //if(argc != 1) {
    // printf("Input the size of the tuples.");
    //continue;
    //}
  }
  
}
