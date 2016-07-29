/*
BUFSIZE：処理系依存（PCのアーキテクチャによる）
メモリに導入するのに最適なサイズが適用される
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define length BUFSIZ
/*
typedef union { //unionの中で最も大きい
  void *p;
  char *s;
  int i;
  char c;
}tuple_u;
typedef tuple_u tuple[2];
*/

typedef struct _TUPLE {
  int key;
  int val;
}TUPLE;

void GenArray(TUPLE tuple[N]){
  for(int i = 0; i < N; i++){
    tuple[i].key = i;
    tuple[i].val = rand() % N;
  }
}

void main(int argc, char *argv[]){
  if(argc != 2) {
    printf("The number of the arguments is incorrect.");
    exit(1);
  }else if((strcmp(argv[1], "fileR.r") != 0)&&(strcmp(argv[1], "fileS.s") != 0)){
    printf("The string you've input is not as expected.");
    exit(1);
  }
  int fd; //file discripter: ファイルと紐付いた数値。OSに渡す
  ssize_t num; //

  TUPLE tuples[length];
  GenArray(tuples);
  
  fd = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
  if(fd == -1){
    printf("There's an error!");
    exit(1);
  }

  num = write(fd, tuples, sizeof(tuples));  

  close(fd);
}
  
