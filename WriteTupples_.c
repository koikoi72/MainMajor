#include <stdio.h>
#include <stdlib.h>

typedef struct _TUPLE{
  int key;
  int val;
  struct _TUPLE* next;
}TUPLE;

TUPLE* AddToTUPPLE(TUPLE* tuple, int k, int val){
  TUPLE* node = (TUPLE*)malloc(sizeof(TUPLE));
  node->key = k;
  node->val = v;
  node->next = NULL;

  if(tuple == NULL) return node;
  else{
    TUPLE* p = tuple;
    while(p->next != NULL){
      p = p->next;
    }
    p->next = node;
    return tuple;
  }
}
  
TUPLE* GenList(){
  TUPLE* list = (TUPLE*)malloc(sizeof(TUPLE));

  for(int i = 0; i < ; i++) {
    list = AddToTUPLE(list, i, rand()%N);
  }
  return list;
}

int main(int argc, char *argv[]) {

  //no argument
  if(argc != 2){
    char err[] = "Specify the file name\n";
    write(2, err, strlen(err));
    return 1;
  }
  
  FILE *fp;
  fp = fopen("Tuples.dat","w");

  
