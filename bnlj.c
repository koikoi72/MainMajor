//文字列定数を引数として渡すと、コンパイル時に先頭のアドレス（先頭を指すポインタ）に変換される
//buf:TUPLE型の配列。外部ファイルからlength分読み込み、このbufに格納している
/*
AddToRESULT関数・Join関数3種実装済み

「今後の課題」
Page読み込み関数・Join後の書き込み関数未実装
Joinの種類選択はどう実装するか
read関数の返り値・fileDiscripterの扱い要勉強、どうやってPagesのLoopを回すか見当がつかない
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define length 1024
#define N 100

typedef struct tuple{
  int key;
  int val;
}TUPLE;
  
typedef struct page{
  int count;
  TUPLE tuple[N];
}PAGE;

typedef struct result{
  int rkey, skey;
  int rval, sval;
  struct result* next;
}RESULT;

void AddToRESULT(RESULT* result, TUPLE* R, TUPLE* S){
  //RESULT型の新しいTUPLEを生成
  RESULT* node = (RESULT*)malloc(sizeof(RESULT));
  node->rkey = R->key;
  node->skey = S->key;
  node->rval = R->val;
  node->sval = S->val;
  node->next = NULL;

  //元のTUPLE配列の最後尾にnodeを挿入
  RESULT* p = result;
  if(p == NULL) return node;
  else {
    while(p->next != NULL){
      p = p->next;
    }p->next = node;
    return;
  }
}
  
int* LoadPages(PAGE *P, int *fd){ //配列で返す
  int x = 0;
  x = read(*fd, &P->tuple, sizeof(P->tuple));
  P->count = x / (int)sizeof(TUPLE);
  fd += x;
  return &x;
  /*
  TUPLE buf[length];
  int count = read(fd, buf*i, length); //read for 'length' from 'fd' and store the page into 'buf', the domain for temporary save.   
  if(count == -1){
    printf("There is an error in reading the file.\n");
  }
  else{
    //buf[count] = '\0';
    return buf;
    } */   
}

void WritePage(RESULT* result){
  write
}

RESULT* JoinKey(PAGE* R, PAGE* S){
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  result = NULL;
  for(int i = 0; i < length; i++){
    result = AddToRESULT(result, &R, &S);
    return result;
  }
}

RESULT* JoinVal(PAGE* R, PAGE* S){
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  result = NULL;
  for(int i = 0; i < R->count; i++){
    for(int j = 0; j < S->count; j++){
      if(R[i]->tuple.val == S[j]->tuple.val) {
	AddToRESULT(result, &R[i], &S[j]);
      }
    }//Listで生成している場合はSのポインタを先頭に戻すことを忘れずに
  }
  return result;
}

RESULT* Join(PAGE* R, PAGE* S){
  RESULT* result = (RESULT*)malloc(sizeof(RESULT));
  result = NULL;
  for(int i = 0; i < length; i++){
    for(int j = 0; j < length; j++){
      result = AddToRESULT(result, &R, &S);
    }
  }
}

/*
void SelectJoin(PAGE* R, PAGE* S){
}
*/
void GetKeyInput(char *c, char *input){
  fgets(input, BUFSIZ, stdin);
  sscanf(input, "%s", c);
}

int main(int argc, char** argv) { //argc: the number of arguments, argv: the array of the pointers that indexes the string of the arguments 
  int fdR, fdS, fdJ; //file discripter
  ssize_t numR, numS; //store an error or length
  //TUPLE bufR[length], bufS[length];

  char c_file[BUFSIZ] = {'\0'};
  char c_how[BUFSIZ] = {'\0'};
  //char fileName[BUFSIZ] = {'\0'};
  //char HowToJoin[BUFSIZ] = {'\0'};
  printf("Input the file name after joined > ");
  GetKeyInput(fileName, c_file);
  //printf("%s",c_file);
  printf("Select through which to join -key, val, or else-");
  GetKeyInput(HowToJoin, c_how);
  //fgets(readLine, BUFSIZ, stdin);
  //sscanf(readLine, "%s", c);  
 
  fdR = open(argv[1], O_RDONLY);
  fdS = open(argv[2], O_RDONLY);
  fdJ = open(c_file[0], O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
  if(fdR == -1 || fdS == -1){
    printf("The file name you've input must be wrong. Try again.");
    exit(1);
  }
  if(fdJ == -1){
    printf("There's an unexpected error. Try again.");
    exit(1);
  }
  printf("%f\n",argv[2]);

  PAGE R, S; //宣言は実体でする方がよい

  while(LoadPages(&R, fdR) != 0) {
    while(LoadPages(&S, fdS) != 0) {
      JoinVal(&R, &S);
      WritePage(result);
    }
  }
  
  return 0;

}
 
