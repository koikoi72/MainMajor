#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 10
#define length BUFSIZ

typedef struct _TUPLE {
  int key;
  int val;
  struct _TUPLE* next;
}TUPLE;

typedef struct _RESULT {
  int rkey, skey;
  int rval, sval;
  struct _RESULT* next;
}RESULT;

void PrintRESULT(RESULT*);

TUPLE* AddToTUPLE(TUPLE* tuple, int k, int v) {
  TUPLE* node = (TUPLE*)malloc(sizeof(TUPLE));
  node->key = k;
  node->val = v;
  node->next = NULL;

  if(tuple == NULL) return node;
  else {
    TUPLE* p = tuple;
    while(p->next != NULL) {
      p = p->next;
    }
    p->next = node;
    return tuple;
  }
}

RESULT* AddToRESULT(RESULT* result, TUPLE* R, TUPLE* S) {
  RESULT* node = (RESULT*)malloc(sizeof(RESULT));
  node->rkey = R->key;
  node->rval = R->val;
  node->skey = S->key;
  node->sval = S->val;
  node->next = NULL;

  if(result == NULL) return node;
  else {
    RESULT* p = result;
    while(p->next != NULL) {
      p = p->next;
    }
    p->next = node;
    return result;
  }
}

void JoinKey(TUPLE* R, TUPLE* S) {
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  while(R->next != NULL) {
    result = AddToRESULT(result, R, S);
    R = R->next;
    S = S->next;

  }
  PrintRESULT(result);
}

void JoinVal(TUPLE* R, TUPLE* S) {
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  TUPLE* S_ = S;
  while(R->next != NULL) {
    while(S->next != NULL) {
      if(R->val == S->val) result = AddToRESULT(result, R, S);
      // printf("s,%d", S->val);
      S = S->next;
    }
    R = R->next;
    //printf("r,%d", R->val);
    S = S_; //Sを先頭に戻す、ありがちなミス
  }
  PrintRESULT(result);
}

void Join(TUPLE* R, TUPLE* S) {
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  while(R->next != NULL) {
    while(S->next != NULL) {
      S = S->next;
    }
    R = R->next;
  }
  PrintRESULT(result);
}

void PrintTUPLE(TUPLE* t) {
  while(t->next != NULL) {
    printf("key: %d, val: %d\n", t->key, t->val);
    t = t->next;
  }
}

void PrintRESULT(RESULT* r) {
  while(r-> next != NULL) {
    printf("rkey: %d, rval: %d, skey: %d, sval: %d\n", r->rkey, r->rval, r->skey, r->sval);
    r = r->next;
  }
}

TUPLE* GenList() {
  TUPLE* list = (TUPLE*)malloc(sizeof(TUPLE));
  // srand((unsigned)time(NULL));

  for(int i = 0; i < N; i++) {
    list = AddToTUPLE(list, i, rand() % N);
  }

  return list;
}

void PrintData(TUPLE* R, TUPLE* S, char c1[], char c2[]) {
  if(strcmp(c1, "print") == 0) {
    if(strcmp(c2, "R") == 0) PrintTUPLE(R);
    else if(strcmp(c2, "S") == 0) PrintTUPLE(S);
    else printf("WTF! BYE:)\n");
  }
  else if(strcmp(c1, "join") == 0) {
    if(strcmp(c2, "key") == 0) JoinKey(R, S);
    else if(strcmp(c2, "val") == 0) JoinVal(R, S);
    else if(c2[0]  == '\0') Join(R, S);
    else printf("Ur miss! HAHA;)\n");
  }
}
  

int main() {

  TUPLE* R = GenList();
  TUPLE* S = GenList();

  while(1) {
    char c1[length] = {'\0'};
    char c2[length] = {'\0'};
    char readLine[length] = {'\0'};
    printf("CMD > ");
    fgets(readLine, length, stdin);
    sscanf(readLine, "%s %s", c1, c2);
    PrintData(R, S, c1, c2);

  }
}
    
