#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//#define N
//#define length BUFSIZ

/* 
foreach page RP of R do
 foreach page SP of S do
  foreach tuple r in RP
   foreach tuple s in RP
    match (r,s);
   end 
  end
 end
end
*/

int main(int argc, char *argv[]) {
  int fd; //file discripter

  //no argument
  if(argc != 2) {
    char err[] = "Desizgn the file name\n";
    write(2, err, strlen(err)); //2:stderr, 1:stdout
    return 1;
  }

  //open the file, otherwise there's an error
  fd = open(argv[1], O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC);
  //read only, write only, creat new file, update the file
  if(fd < 0) {
    char err[] = "Unable to open the file\n";
    write(2, err, strlen(err));
    write(2, strerror(errno), strlen(strerror(errno)));
    write(2, "\n", 1);
    return 1;
  } else {
    char message[256];
    sprintf(message,
	    "File %s is opened. File discripter is %d.\n",
	    argv[1], fd);
    write(1, message, strlen(message));
  }

  //read the file by 256 bytes, then output them to the stdout. 
  while(1) {
    char buf[256];
    int read_size;

    read_size = read(fd, buf, sizeof(buf));

    if(read_size > 0) write(fd, buf, read_size);
    else if(read_size == 0) break;
    else {
      char err[] = "There's an error on read(2)\n";
      write(2, err, strlen(err));
      write(2, strerror(errno), strlen(strerror(errno)));
      write(2, "\n", 1);
      return 1;
    }
  }
  close(fd);
  return 0;
}
